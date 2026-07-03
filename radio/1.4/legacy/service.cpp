/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.radio@1.4-service.legacy"

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <hidl/HidlTransportSupport.h>

#include "Radio.h"
#include "hidl-utils.h"

#include <unistd.h>

#include <algorithm>
#include <map>
#include <string>

using namespace android::hardware::radio;
using namespace android::hardware::hidl_utils;

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

using android::hardware::radio::implementation::Radio;

using android::OK;
using android::sp;
using android::status_t;

#define MAX_SLOT_ID 4

// Expected SIM slot count. On dsds we must block on slot2 or com.android.phone ANR-loops on
// getService(slot2); persist.radio.multisim.config reads empty early boot, so fall back to RO signals.
static int detectExpectedSlots() {
    // Wait (bounded) before accepting 1: a premature "1" leaves slot2 unregistered and hangs
    // com.android.phone. ro.* signals are set in first-stage init (race-free); persist.* may arrive later.
    for (int attempt = 0; attempt < 15; attempt++) {
        std::string multisim = android::base::GetProperty("persist.radio.multisim.config", "");
        if (multisim.empty()) {
            multisim = android::base::GetProperty("persist.multisim.config", "");
        }
        if (multisim == "tsts") return 3;
        if (multisim == "dsds" || multisim == "dsda") return 2;

        const std::string device = android::base::GetProperty("ro.product.device", "");
        const std::string defaultNetwork =
                android::base::GetProperty("ro.telephony.default_network", "");
        if (device.find("tsts") != std::string::npos) return 3;
        if (device.find("dsds") != std::string::npos ||
            device.find("dsda") != std::string::npos) {
            return 2;
        }
        const int subsFromNetwork =
                defaultNetwork.empty()
                        ? 1
                        : 1 + static_cast<int>(std::count(defaultNetwork.begin(),
                                                          defaultNetwork.end(), ','));
        if (subsFromNetwork >= 3) return 3;
        if (subsFromNetwork >= 2) return 2;
        // A populated non-multi-SIM ro.product.device is a definitive single-SIM answer; accept it at once.
        if (!device.empty()) return 1;
        // Identifying props not populated yet -> wait briefly and retry.
        sleep(1);
    }
    return 1;
}

int main() {
    // Note: Starts from slot 1
    const int expectedSlots = detectExpectedSlots();
    LOG(INFO) << "radio HAL: persist.radio.multisim.config='"
              << android::base::GetProperty("persist.radio.multisim.config", "")
              << "' ro.telephony.default_network='"
              << android::base::GetProperty("ro.telephony.default_network", "")
              << "' ro.product.device='"
              << android::base::GetProperty("ro.product.device", "")
              << "' expectedSlots=" << expectedSlots;

    // Multi-thread binder pool started before any slot is registered, so a blocking getService() for a
    // later slot cannot starve an already-registered slot's transactions (a single thread did).
    configureRpcThreadpool(4, true);

    for (int slotId = 1; slotId <= MAX_SLOT_ID; slotId++) {
        // Sony's libril registers @1.1::IRadio (not @1.0) and A16 hwservicemanager is strict, so look up
        // @1.1 directly; expected slots poll until rild registers, else @1.4/slotN hangs com.android.phone.
        sp<V1_0::IRadio> realRadio;
        const bool expected = slotId <= expectedSlots;
        if (expected) {
            // EXPECTED slot: wait effectively forever for rild to register @1.1::IRadio/slotN; giving up
            // would leave @1.4::IRadio/slotN unregistered and hang com.android.phone (intermittent 0-SIM).
            for (int attempt = 0; realRadio == nullptr; attempt++) {
                realRadio = V1_1::IRadio::tryGetService("slot" + std::to_string(slotId));
                if (realRadio == nullptr) {
                    if (attempt % 30 == 0) {
                        LOG(INFO) << "Waiting for rild to register @1.1::IRadio/slot" << slotId
                                  << " (attempt " << attempt << ")";
                    }
                    sleep(1);
                }
            }
        } else {
            // Extra (non-expected) slot: probe once; absence just means there are no more slots.
            realRadio = V1_1::IRadio::tryGetService("slot" + std::to_string(slotId));
            if (realRadio == nullptr) {
                LOG(INFO) << "No rild for slot " << slotId << " (not expected); done.";
                break;
            }
        }

        // Register each slot as soon as acquired so slot1@1.4 is available without waiting on slot2's daemon.
        // Pass the 0-based physical slot index so the wrapper can tag CardStatus.physicalSlotId per slot.
        sp<V1_4::IRadio> radio = new Radio(realRadio, slotId - 1);
        linkDeathToDeath(realRadio);
        // Retry registration for EXPECTED slots until it succeeds: a transient registerAsService
        // failure must not leave the slot unregistered (same hang as above).
        status_t status = radio->registerAsService("slot" + std::to_string(slotId));
        while (status != OK && expected) {
            LOG(ERROR) << "Cannot register @1.4::IRadio/slot" << slotId << "; retrying";
            sleep(1);
            status = radio->registerAsService("slot" + std::to_string(slotId));
        }
        if (status != OK) {
            LOG(ERROR) << "Cannot register @1.4::IRadio/slot" << slotId << " (not expected); done.";
            break;
        }
        LOG(INFO) << "Registered @1.4::IRadio/slot" << slotId;
    }

    LOG(INFO) << "Radio HAL service ready.";

    joinRpcThreadpool();

    LOG(INFO) << "Radio HAL service failed to join thread pool.";
    return 1;
}

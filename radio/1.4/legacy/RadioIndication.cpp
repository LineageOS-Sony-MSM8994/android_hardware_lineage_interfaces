/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "RadioIndication.h"
#include "Helpers.h"

namespace android::hardware::radio::implementation {

// Methods from ::android::hardware::radio::V1_0::IRadioIndication follow.
Return<void> RadioIndication::radioStateChanged(V1_0::RadioIndicationType type,
                                                V1_0::RadioState radioState) {
    return fwdReturn(mRealRadioIndication->radioStateChanged(type, radioState));
}

Return<void> RadioIndication::callStateChanged(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->callStateChanged(type));
}

Return<void> RadioIndication::networkStateChanged(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->networkStateChanged(type));
}

Return<void> RadioIndication::newSms(V1_0::RadioIndicationType type, const hidl_vec<uint8_t>& pdu) {
    return fwdReturn(mRealRadioIndication->newSms(type, pdu));
}

Return<void> RadioIndication::newSmsStatusReport(V1_0::RadioIndicationType type,
                                                 const hidl_vec<uint8_t>& pdu) {
    return fwdReturn(mRealRadioIndication->newSmsStatusReport(type, pdu));
}

Return<void> RadioIndication::newSmsOnSim(V1_0::RadioIndicationType type, int32_t recordNumber) {
    return fwdReturn(mRealRadioIndication->newSmsOnSim(type, recordNumber));
}

Return<void> RadioIndication::onUssd(V1_0::RadioIndicationType type, V1_0::UssdModeType modeType,
                                     const hidl_string& msg) {
    return fwdReturn(mRealRadioIndication->onUssd(type, modeType, msg));
}

Return<void> RadioIndication::nitzTimeReceived(V1_0::RadioIndicationType type,
                                               const hidl_string& nitzTime, uint64_t receivedTime) {
    return fwdReturn(mRealRadioIndication->nitzTimeReceived(type, nitzTime, receivedTime));
}

Return<void> RadioIndication::currentSignalStrength(V1_0::RadioIndicationType type,
                                                    const V1_0::SignalStrength& signalStrength) {
    return fwdReturn(mRealRadioIndication->currentSignalStrength_1_4(type, Create1_4SignalStrength(signalStrength)));
}

Return<void> RadioIndication::dataCallListChanged(
        V1_0::RadioIndicationType type, const hidl_vec<V1_0::SetupDataCallResult>& dcList) {
    hidl_vec<V1_4::SetupDataCallResult> newDcList;
    newDcList.resize(dcList.size());
    for(int x = 0; x < dcList.size(); ++x)
        newDcList[x] = Create1_4SetupDataCallResult(dcList[x]);
    return fwdReturn(mRealRadioIndication->dataCallListChanged_1_4(type, newDcList));
}

Return<void> RadioIndication::suppSvcNotify(V1_0::RadioIndicationType type,
                                            const V1_0::SuppSvcNotification& suppSvc) {
    return fwdReturn(mRealRadioIndication->suppSvcNotify(type, suppSvc));
}

Return<void> RadioIndication::stkSessionEnd(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->stkSessionEnd(type));
}

Return<void> RadioIndication::stkProactiveCommand(V1_0::RadioIndicationType type,
                                                  const hidl_string& cmd) {
    return fwdReturn(mRealRadioIndication->stkProactiveCommand(type, cmd));
}

Return<void> RadioIndication::stkEventNotify(V1_0::RadioIndicationType type,
                                             const hidl_string& cmd) {
    return fwdReturn(mRealRadioIndication->stkEventNotify(type, cmd));
}

Return<void> RadioIndication::stkCallSetup(V1_0::RadioIndicationType type, int64_t timeout) {
    return fwdReturn(mRealRadioIndication->stkCallSetup(type, timeout));
}

Return<void> RadioIndication::simSmsStorageFull(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->simSmsStorageFull(type));
}

Return<void> RadioIndication::simRefresh(V1_0::RadioIndicationType type,
                                         const V1_0::SimRefreshResult& refreshResult) {
    return fwdReturn(mRealRadioIndication->simRefresh(type, refreshResult));
}

Return<void> RadioIndication::callRing(V1_0::RadioIndicationType type, bool isGsm,
                                       const V1_0::CdmaSignalInfoRecord& record) {
    return fwdReturn(mRealRadioIndication->callRing(type, isGsm, record));
}

Return<void> RadioIndication::simStatusChanged(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->simStatusChanged(type));
}

Return<void> RadioIndication::cdmaNewSms(V1_0::RadioIndicationType type,
                                         const V1_0::CdmaSmsMessage& msg) {
    return fwdReturn(mRealRadioIndication->cdmaNewSms(type, msg));
}

Return<void> RadioIndication::newBroadcastSms(V1_0::RadioIndicationType type,
                                              const hidl_vec<uint8_t>& data) {
    return fwdReturn(mRealRadioIndication->newBroadcastSms(type, data));
}

Return<void> RadioIndication::cdmaRuimSmsStorageFull(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->cdmaRuimSmsStorageFull(type));
}

Return<void> RadioIndication::restrictedStateChanged(V1_0::RadioIndicationType type,
                                                     V1_0::PhoneRestrictedState state) {
    return fwdReturn(mRealRadioIndication->restrictedStateChanged(type, state));
}

Return<void> RadioIndication::enterEmergencyCallbackMode(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->enterEmergencyCallbackMode(type));
}

Return<void> RadioIndication::cdmaCallWaiting(V1_0::RadioIndicationType type,
                                              const V1_0::CdmaCallWaiting& callWaitingRecord) {
    return fwdReturn(mRealRadioIndication->cdmaCallWaiting(type, callWaitingRecord));
}

Return<void> RadioIndication::cdmaOtaProvisionStatus(V1_0::RadioIndicationType type,
                                                     V1_0::CdmaOtaProvisionStatus status) {
    return fwdReturn(mRealRadioIndication->cdmaOtaProvisionStatus(type, status));
}

Return<void> RadioIndication::cdmaInfoRec(V1_0::RadioIndicationType type,
                                          const V1_0::CdmaInformationRecords& records) {
    return fwdReturn(mRealRadioIndication->cdmaInfoRec(type, records));
}

Return<void> RadioIndication::indicateRingbackTone(V1_0::RadioIndicationType type, bool start) {
    return fwdReturn(mRealRadioIndication->indicateRingbackTone(type, start));
}

Return<void> RadioIndication::resendIncallMute(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->resendIncallMute(type));
}

Return<void> RadioIndication::cdmaSubscriptionSourceChanged(
        V1_0::RadioIndicationType type, V1_0::CdmaSubscriptionSource cdmaSource) {
    return fwdReturn(mRealRadioIndication->cdmaSubscriptionSourceChanged(type, cdmaSource));
}

Return<void> RadioIndication::cdmaPrlChanged(V1_0::RadioIndicationType type, int32_t version) {
    return fwdReturn(mRealRadioIndication->cdmaPrlChanged(type, version));
}

Return<void> RadioIndication::exitEmergencyCallbackMode(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->exitEmergencyCallbackMode(type));
}

Return<void> RadioIndication::rilConnected(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->rilConnected(type));
}

Return<void> RadioIndication::voiceRadioTechChanged(V1_0::RadioIndicationType type,
                                                    V1_0::RadioTechnology rat) {
    return fwdReturn(mRealRadioIndication->voiceRadioTechChanged(type, rat));
}

Return<void> RadioIndication::cellInfoList(V1_0::RadioIndicationType type,
                                           const hidl_vec<V1_0::CellInfo>& records) {
    return fwdReturn(mRealRadioIndication->cellInfoList_1_4(type, Create1_4CellInfoList(records)));
}

Return<void> RadioIndication::imsNetworkStateChanged(V1_0::RadioIndicationType type) {
    return fwdReturn(mRealRadioIndication->imsNetworkStateChanged(type));
}

Return<void> RadioIndication::subscriptionStatusChanged(V1_0::RadioIndicationType type,
                                                        bool activate) {
    return fwdReturn(mRealRadioIndication->subscriptionStatusChanged(type, activate));
}

Return<void> RadioIndication::srvccStateNotify(V1_0::RadioIndicationType type,
                                               V1_0::SrvccState state) {
    return fwdReturn(mRealRadioIndication->srvccStateNotify(type, state));
}

Return<void> RadioIndication::hardwareConfigChanged(V1_0::RadioIndicationType type,
                                                    const hidl_vec<V1_0::HardwareConfig>& configs) {
    return fwdReturn(mRealRadioIndication->hardwareConfigChanged(type, configs));
}

Return<void> RadioIndication::radioCapabilityIndication(V1_0::RadioIndicationType type,
                                                        const V1_0::RadioCapability& rc) {
    return fwdReturn(mRealRadioIndication->radioCapabilityIndication(type, rc));
}

Return<void> RadioIndication::onSupplementaryServiceIndication(V1_0::RadioIndicationType type,
                                                               const V1_0::StkCcUnsolSsResult& ss) {
    return fwdReturn(mRealRadioIndication->onSupplementaryServiceIndication(type, ss));
}

Return<void> RadioIndication::stkCallControlAlphaNotify(V1_0::RadioIndicationType type,
                                                        const hidl_string& alpha) {
    return fwdReturn(mRealRadioIndication->stkCallControlAlphaNotify(type, alpha));
}

Return<void> RadioIndication::lceData(V1_0::RadioIndicationType type,
                                      const V1_0::LceDataInfo& lce) {
    return fwdReturn(mRealRadioIndication->lceData(type, lce));
}

Return<void> RadioIndication::pcoData(V1_0::RadioIndicationType type,
                                      const V1_0::PcoDataInfo& pco) {
    return fwdReturn(mRealRadioIndication->pcoData(type, pco));
}

Return<void> RadioIndication::modemReset(V1_0::RadioIndicationType type,
                                         const hidl_string& reason) {
    return fwdReturn(mRealRadioIndication->modemReset(type, reason));
}

// Methods from ::android::hardware::radio::V1_1::IRadioIndication follow.
Return<void> RadioIndication::carrierInfoForImsiEncryption(V1_0::RadioIndicationType info) {
    return fwdReturn(mRealRadioIndication->carrierInfoForImsiEncryption(info));
}

Return<void> RadioIndication::networkScanResult(V1_0::RadioIndicationType type,
                                                const V1_1::NetworkScanResult& result) {
    V1_4::NetworkScanResult newNSR = {};
    newNSR.status = result.status;
    newNSR.error = result.error;
    newNSR.networkInfos = Create1_4CellInfoList(result.networkInfos);
    return fwdReturn(mRealRadioIndication->networkScanResult_1_4(type, newNSR));
}

Return<void> RadioIndication::keepaliveStatus(V1_0::RadioIndicationType type,
                                              const V1_1::KeepaliveStatus& status) {
    return fwdReturn(mRealRadioIndication->keepaliveStatus(type, status));
}

// Methods from ::android::hardware::radio::V1_2::IRadioIndication follow.
Return<void> RadioIndication::networkScanResult_1_2(V1_0::RadioIndicationType type,
                                                    const V1_2::NetworkScanResult& result) {
    V1_4::NetworkScanResult newNSR = {};
    newNSR.status = result.status;
    newNSR.error = result.error;
    newNSR.networkInfos = Create1_4CellInfoList(result.networkInfos);
    return fwdReturn(mRealRadioIndication->networkScanResult_1_4(type, newNSR));
}

Return<void> RadioIndication::cellInfoList_1_2(V1_0::RadioIndicationType type,
                                               const hidl_vec<V1_2::CellInfo>& records) {
    return fwdReturn(mRealRadioIndication->cellInfoList_1_4(type, Create1_4CellInfoList(records)));
}

Return<void> RadioIndication::currentLinkCapacityEstimate(V1_0::RadioIndicationType type,
                                                          const V1_2::LinkCapacityEstimate& lce) {
    return fwdReturn(mRealRadioIndication->currentLinkCapacityEstimate(type, lce));
}

Return<void> RadioIndication::currentPhysicalChannelConfigs(
        V1_0::RadioIndicationType type, const hidl_vec<V1_2::PhysicalChannelConfig>& configs) {
    hidl_vec<V1_4::PhysicalChannelConfig> newConfigs;
    newConfigs.resize(configs.size());
    for(int x = 0; x < configs.size(); ++x){
        newConfigs[x].base = configs[x];
        newConfigs[x].rat = V1_4::RadioTechnology::UNKNOWN;
        newConfigs[x].physicalCellId = -1;
    }
    return fwdReturn(mRealRadioIndication->currentPhysicalChannelConfigs_1_4(type, newConfigs));
}

Return<void> RadioIndication::currentSignalStrength_1_2(
        V1_0::RadioIndicationType type, const V1_2::SignalStrength& signalStrength) {
    return fwdReturn(mRealRadioIndication->currentSignalStrength_1_4(type, Create1_4SignalStrength(signalStrength)));
}

// Methods from ::android::hardware::radio::V1_4::IRadioIndication follow.
Return<void> RadioIndication::currentEmergencyNumberList(
        V1_0::RadioIndicationType type,
        const hidl_vec<V1_4::EmergencyNumber>& emergencyNumberList) {
    return fwdReturn(mRealRadioIndication->currentEmergencyNumberList(type, emergencyNumberList));
}

Return<void> RadioIndication::cellInfoList_1_4(V1_0::RadioIndicationType type,
                                               const hidl_vec<V1_4::CellInfo>& records) {
    return fwdReturn(mRealRadioIndication->cellInfoList_1_4(type, records));
}

Return<void> RadioIndication::networkScanResult_1_4(V1_0::RadioIndicationType type,
                                                    const V1_4::NetworkScanResult& result) {
    return fwdReturn(mRealRadioIndication->networkScanResult_1_4(type, result));
}

Return<void> RadioIndication::currentPhysicalChannelConfigs_1_4(
        V1_0::RadioIndicationType type, const hidl_vec<V1_4::PhysicalChannelConfig>& configs) {
    return fwdReturn(mRealRadioIndication->currentPhysicalChannelConfigs_1_4(type, configs));
}

Return<void> RadioIndication::dataCallListChanged_1_4(
        V1_0::RadioIndicationType type, const hidl_vec<V1_4::SetupDataCallResult>& dcList) {
    return fwdReturn(mRealRadioIndication->dataCallListChanged_1_4(type, dcList));
}

Return<void> RadioIndication::currentSignalStrength_1_4(
        V1_0::RadioIndicationType type, const V1_4::SignalStrength& signalStrength) {
    return fwdReturn(mRealRadioIndication->currentSignalStrength_1_4(type, signalStrength));
}

}  // namespace android::hardware::radio::implementation

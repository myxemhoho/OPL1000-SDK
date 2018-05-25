/******************************************************************************
*  Copyright 2017 - 2018, Opulinks Technology Ltd.
*  ---------------------------------------------------------------------------
*  Statement:
*  ----------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Opulinks Technology Ltd. (C) 2018
******************************************************************************/

#ifndef _WIFI_MAC_STA_PATCH_H_
#define _WIFI_MAC_STA_PATCH_H_

#include "wifi_mac_sta.h"

typedef struct {
    u8      au8Dot11MACAddress[MAC_ADDR_LEN];
    u8      u8Dot11ShortRetryLimit;
    u8      u8Dot11LongRetryLimit;
    u8      u8CwExpMin;
    u8      u8CwExpMax;
    // 11th
    u8      u8SilenceThr;
    u8      u8KeepConnectThr;
    u16     u16TimeUnit;
    u8      u8Sifs;
    u8      u8Difs;
    u16     u16Eifs;
    u8      u8Slot;
    u8      u8MaEnLen;
    // 21st
    u8      u8TrxEnLen;
    u8      u8PhyMode;
    u8      u8ConsSuccThr;      // The threshold to increase data rate when u8ConsSuccCnt of bss_info reaches
    u8      u8ConsFailThr;      // The threshold to decrease data rate when u8ConsFailCnt of bss_info reaches
    u16     u16RtsThr;          // The threshold to exchange RTS/CTS when packet size is larger
    u8      u8RetryThr1;        // The threshold to exchange RTS/CTS when u8RetryCnt of g_DcfInfo reaches
    u8      u8RetryThr2;        // The threshold to decrease current rate when u8RetryCnt of g_DcfInfo is the power of
    // 29th
    u8      u8ListenInv;
    uint8_t     u8Reserved__1;
    // 31st
    uint16_t    u16PrbRsqTimeout;
    uint16_t    u16AuthRsqTimeout;
    uint16_t    u16AssocRsqTimeout;
    uint16_t    u16ScrtConnTimeout;
    uint8_t     u8PrbRsqReTtlCnt;
    uint8_t     u8AuthRsqReTtlCnt;
    // 41st
    uint8_t     u8AssocRsqReTtlCnt;
    uint8_t     u8ScrtConnReTtlCnt;
    uint8_t     u8SkipDtimPeriods;
    // N bytes

    u8      reserved[214];   // 256 - N bytes
} WifiSta_StaInfo_Patch_s;

typedef struct {
//	wifi_device_mode_t device_mode;
//	u8 bssid[MAC_ADDR_LEN];
//#ifdef CHIP_DEMO_WIFI
//	u8 current_ap[MAC_ADDR_LEN];
//#endif
//	s8 ssid[IEEE80211_MAX_SSID_LEN + 1];
//	u8 phy_mode;
//	u8 supported_rates[SUPPORTED_RATES_MAX];
//	mac_sub_state_t mac_sub_state;
//	mac_state_t mac_state;
//	u16 rts_threshold;
//	u16 aid;
//	u32 tx_mgmt_count;
//	u32 tx_data_count;
//	u32 rx_mgmt_count;
//	u32 rx_data_count;
//	u16 tx_sequence;
//	u16 rx_sequence;
//	u32 auth_algorithm;
//	u16 capabilities;
//	u16 listen_interval;
//	u16 beacon_interval;
//	u8  current_channel;    //Current RF Channel. Table 17-9
//	wifi_rate_mode_t wifi_rate_mode;
//	u8  sta_pm_mode;    // Power-saving mode
//	u8  u8DtimCount;    // The value is equal to AP
//	u8  u8DtimPeriod;   // The value is equal to AP
	u8  u8PsPeriod;     // The real power-saving period
	u32 u32WakeupTime;  // The value is related to trx free run timer, unit: 1us
	u32 u32BcnTmStmp;   // Received the last beacon low 32-bit time-stamp
//	u8  silence_count;  // Unit: beacon interval
//	s8  rssi;
//	u8  u8ConsSuccCnt;
//	u8  u8ConsFailCnt;
	u32 u32TimeoutDur;
	u8  u8RetryCnt;
	u8  u8RetryTtlCnt;
//
//    u8 wpa_assoc_ie[100];
//    wpa_ssid_t own_wpa_info;
//    rx_eapol_report eapol_msg;
//    u8  rsna_en;
//	//dl_list_t tx_queue;
//	//dl_list_t rx_queue;
//	//linked_list_t *tx_queue;
//	//linked_list_t *rx_queue;
//    u32 volatile spin_lock;   //Henry test
} bss_info_ext_t;

#endif /* _WIFI_MAC_STA_PATCH_H_ */


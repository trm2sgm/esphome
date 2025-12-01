#pragma once

namespace esphome::espnow {
#define ESP_ERR_WIFI_BASE 0x3000                           /*!< Starting number of WiFi error codes */
#define ESP_ERR_ESPNOW_BASE (ESP_ERR_WIFI_BASE + 100)      /*!< ESPNOW error number base. */
#define ESP_ERR_ESPNOW_NOT_INIT (ESP_ERR_ESPNOW_BASE + 1)  /*!< ESPNOW is not initialized. */
#define ESP_ERR_ESPNOW_ARG (ESP_ERR_ESPNOW_BASE + 2)       /*!< Invalid argument */
#define ESP_ERR_ESPNOW_NO_MEM (ESP_ERR_ESPNOW_BASE + 3)    /*!< Out of memory */
#define ESP_ERR_ESPNOW_FULL (ESP_ERR_ESPNOW_BASE + 4)      /*!< ESPNOW peer list is full */
#define ESP_ERR_ESPNOW_NOT_FOUND (ESP_ERR_ESPNOW_BASE + 5) /*!< ESPNOW peer is not found */
#define ESP_ERR_ESPNOW_INTERNAL (ESP_ERR_ESPNOW_BASE + 6)  /*!< Internal error */
#define ESP_ERR_ESPNOW_EXIST (ESP_ERR_ESPNOW_BASE + 7)     /*!< ESPNOW peer has existed */
#define ESP_ERR_ESPNOW_IF (ESP_ERR_ESPNOW_BASE + 8)        /*!< Interface error */
#define ESP_OK (0)                                         /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL (-1)                                      /*!< Generic esp_err_t code indicating failure */

#define ESP_NOW_ETH_ALEN 6 /*!< Length of ESPNOW peer MAC address */
#define ESP_NOW_MAX_DATA_LEN 250

typedef int esp_err_t;
typedef unsigned char esp_now_send_status_t;
//#define ESP_NOW_SEND_SUCCESS        0         /**< Send ESPNOW data successfully */
#define ESP_NOW_SEND_FAIL 1 /**< Send ESPNOW data fail */

const char *esp_err_to_name(esp_err_t code);

typedef struct {
  esp_err_t code;
  const char *msg;
} esp_err_msg_t;

#define ERR_TBL_IT(err) \
  { err, #err }

typedef struct {
  signed rssi : 8;             /**< signal intensity of packet */
  unsigned rate : 4;           /**< data rate */
  unsigned is_group : 1;       /**< usually not used */
  unsigned : 1;                /**< reserve */
  unsigned sig_mode : 2;       /**< 0:is not 11n packet; 1:is 11n packet */
  unsigned legacy_length : 12; /**< Length of 11bg mode packet */
  unsigned damatch0 : 1;       /**< usually not used */
  unsigned damatch1 : 1;       /**< usually not used */
  unsigned bssidmatch0 : 1;    /**< usually not used */
  unsigned bssidmatch1 : 1;    /**< usually not used */
  unsigned mcs : 7;            /**< if is 11n packet, shows the modulation(range from 0 to 76) */
  unsigned cwb : 1;            /**< if is 11n packet, shows if is HT40 packet or not */
  unsigned HT_length : 16;     /**< Length of 11n mode packet */
  unsigned smoothing : 1;      /**< reserve */
  unsigned not_sounding : 1;   /**< reserve */
  unsigned : 1;                /**< reserve */
  unsigned aggregation : 1;    /**< Aggregation */
  unsigned stbc : 2;           /**< STBC */
  unsigned fec_coding : 1;     /**< Flag is set for 11n packets which are LDPC */
  unsigned sgi : 1;            /**< SGI */
  unsigned rxend_state : 8;    /**< usually not used */
  unsigned ampdu_cnt : 8;      /**< ampdu cnt */
  unsigned channel : 4;        /**< which channel this packet in */
  unsigned : 4;                /**< reserve */
  signed noise_floor : 8;      /**< usually not used */
} wifi_pkt_rx_ctrl_t;

}  // namespace esphome::espnow

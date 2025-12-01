#pragma once

#if defined(USE_ESP32) || defined(USE_ESP8266)

#ifdef USE_ESP32
#include <esp_err.h>
#include <esp_now.h>
#else
#include <espnow.h>
#include "esp8266_dummy_types.h"
#endif
namespace esphome::espnow {
static const esp_err_t ESP_ERR_ESPNOW_CMP_BASE = (ESP_ERR_ESPNOW_BASE + 20);
static const esp_err_t ESP_ERR_ESPNOW_FAILED = (ESP_ERR_ESPNOW_CMP_BASE + 1);
static const esp_err_t ESP_ERR_ESPNOW_OWN_ADDRESS = (ESP_ERR_ESPNOW_CMP_BASE + 2);
static const esp_err_t ESP_ERR_ESPNOW_DATA_SIZE = (ESP_ERR_ESPNOW_CMP_BASE + 3);
static const esp_err_t ESP_ERR_ESPNOW_PEER_NOT_SET = (ESP_ERR_ESPNOW_CMP_BASE + 4);
static const esp_err_t ESP_ERR_ESPNOW_PEER_NOT_PAIRED = (ESP_ERR_ESPNOW_CMP_BASE + 5);
static const esp_err_t ESP_ERR_ESPNOW_INVALID_MAC = (ESP_ERR_ESPNOW_CMP_BASE + 6);
}  // namespace esphome::espnow

#endif  // USE_ESP32

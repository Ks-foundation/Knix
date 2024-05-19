#ifndef WIFI_H
#define WIFI_H

#include <stdint.h>

typedef struct {
    char ssid[32];
    int8_t rssi; // Received Signal Strength Indicator
} wifi_network_t;

int wifi_scan(wifi_network_t *networks, int max_networks);
int wifi_connect(const char *ssid, const char *password);

#endif // WIFI_H

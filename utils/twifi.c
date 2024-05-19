#include "kinxlib.h"
#include "wifi.h"

void main() {
    wifi_network_t networks[10];
    int network_count;
    char ssid[32];
    char password[32];

    // Wi-Fi 스캔
    print_string("Scanning for Wi-Fi networks...\n");
    network_count = wifi_scan(networks, 10);
    if (network_count > 0) {
        print_string("Available Networks:\n");
        for (int i = 0; i < network_count; i++) {
            print_string(networks[i].ssid);
            print_string(" (RSSI: ");
            char rssi_str[4];
            itoa(networks[i].rssi, rssi_str);
            print_string(rssi_str);
            print_string(")\n");
        }

        // 네트워크 선택
        print_string("Enter SSID to connect: ");
        read_input(ssid, sizeof(ssid));

        // 비밀번호 입력
        print_string("Enter password: ");
        read_input(password, sizeof(password));

        // Wi-Fi 연결 시도
        if (wifi_connect(ssid, password) == 0) {
            print_string("Connected to ");
            print_string(ssid);
            print_string(" successfully!\n");
        } else {
            print_string("Failed to connect to ");
            print_string(ssid);
            print_string(".\n");
        }
    } else {
        print_string("No Wi-Fi networks found.\n");
    }

    while (1);
}

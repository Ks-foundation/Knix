#include "ssd_fs.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// 네트워크 카드 초기화 및 데이터 송수신을 위한 정의
#define IO_BASE 0x3000  // 네트워크 카드의 I/O 기본 주소 (예시)

// 네트워크 카드 초기화 함수
void init_network() {
    // 네트워크 카드 초기화 코드 (간단한 예시)
    outb(IO_BASE + 0, 0x01);  // 네트워크 카드 초기화 명령 (예시)
    print_string("Network initialized.\n");
}

// 네트워크 카드에서 데이터 읽기 함수
int network_receive(uint8_t *buffer, uint32_t size) {
    // 네트워크 카드에서 데이터 읽기 (간단한 예시)
    for (uint32_t i = 0; i < size; i++) {
        buffer[i] = inb(IO_BASE + 1);
    }
    return size;
}

// 네트워크 카드로 데이터 보내기 함수
void network_send(const uint8_t *data, uint32_t size) {
    // 네트워크 카드로 데이터 보내기 (간단한 예시)
    for (uint32_t i = 0; i < size; i++) {
        outb(IO_BASE + 1, data[i]);
    }
}

void print_string(const char *str) {
    char *video_memory = (char *) 0xB8000;
    while (*str) {
        *video_memory++ = *str++;
        *video_memory++ = 0x01; // 파란색 텍스트, 검은색 배경
    }
}

char get_char() {
    char c;
    __asm__ __volatile__ (
        "mov $0x00, %%ah\n"
        "int $0x16\n"
        "mov %%al, %0\n"
        : "=r"(c)
        :
        : "%ah", "%al"
    );
    return c;
}

void read_input(char *buffer, int max_length) {
    int i = 0;
    char c;
    while (i < max_length - 1) {
        c = get_char();
        if (c == '\r') { // Enter 키 처리
            break;
        }
        buffer[i++] = c;
        print_string(&c); // 화면에 입력한 문자 출력
    }
    buffer[i] = '\0'; // 문자열 종료
}

void init_mouse() {
    // 마우스 초기화 코드 (기본적인 BIOS 인터럽트 사용 예제)
    __asm__ __volatile__ (
        "mov $0x00, %ax \n"
        "int $0x33      \n"
        :
        :
        : "ax"
    );
}

void kernel_main(void) {
    print_string("KinX Operating System\n");
    print_string("Initializing filesystem...\n");
    init_fs();

    print_string("Initializing mouse...\n");
    init_mouse();

    print_string("Initializing network...\n");
    init_network();

    char command[100];
    while (1) {
        print_string("\n> ");
        read_input(command, sizeof(command));

        if (strncmp(command, "create ", 7) == 0) {
            char *filename = command + 7;
            const uint8_t data[] = "This is a test file.";
            if (create_file(filename, data, sizeof(data)) == 0) {
                print_string("File created successfully.\n");
            } else {
                print_string("Failed to create file.\n");
            }
        } else if (strncmp(command, "read ", 5) == 0) {
            char *filename = command + 5;
            uint8_t buffer[512];
            int size = read_file(filename, buffer, sizeof(buffer));
            if (size > 0) {
                buffer[size] = '\0';
                print_string("File content: ");
                print_string((const char *)buffer);
                print_string("\n");
            } else {
                print_string("Failed to read file.\n");
            }
        } else if (strncmp(command, "delete ", 7) == 0) {
            char *filename = command + 7;
            if (delete_file(filename) == 0) {
                print_string("File deleted successfully.\n");
            } else {
                print_string("Failed to delete file.\n");
            }
        } else if (strncmp(command, "mkdir ", 6) == 0) {
            char *dirname = command + 6;
            if (create_directory(dirname) == 0) {
                print_string("Directory created successfully.\n");
            } else {
                print_string("Failed to create directory.\n");
            }
        } else if (strncmp(command, "rmdir ", 6) == 0) {
            char *dirname = command + 6;
            if (remove_directory(dirname) == 0) {
                print_string("Directory removed successfully.\n");
            } else {
                print_string("Failed to remove directory.\n");
            }
        } else if (strncmp(command, "cd ", 3) == 0) {
            char *dirname = command + 3;
            if (change_directory(dirname) == 0) {
                print_string("Changed directory.\n");
            } else {
                print_string("Failed to change directory.\n");
            }
        } else if (strcmp(command, "list") == 0) {
            list_files();
        } else if (strncmp(command, "exec ", 5) == 0) {
            char *filename = command + 5;
            if (execute_file(filename) == 0) {
                print_string("Executed file successfully.\n");
            } else {
                print_string("Failed to execute file.\n");
            }
        } else if (strncmp(command, "netrecv", 7) == 0) {
            uint8_t buffer[512];
            int size = network_receive(buffer, sizeof(buffer));
            if (size > 0) {
                buffer[size] = '\0';
                print_string("Received data: ");
                print_string((const char *)buffer);
                print_string("\n");
            } else {
                print_string("Failed to receive data.\n");
            }
        } else if (strncmp(command, "netsend ", 8) == 0) {
            char *data = command + 8;
            network_send((const uint8_t *)data, strlen(data));
            print_string("Data sent.\n");
        } else {
            print_string("Unknown command.\n");
        }
    }
}

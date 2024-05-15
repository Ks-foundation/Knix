#include "ssd_fs.h"
#include <stdio.h>
#include <string.h>

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
               


#include "kinxlib.h"
#include "ssd_fs.h"

// 텍스트 출력 함수
void print_string(const char *str) {
    char *video_memory = (char *) 0xB8000;
    while (*str) {
        *video_memory++ = *str++;
        *video_memory++ = 0x01; // 파란색 텍스트, 검은색 배경
    }
}

void print_char(char c) {
    char *video_memory = (char *) 0xB8000;
    *video_memory++ = c;
    *video_memory++ = 0x01; // 파란색 텍스트, 검은색 배경
}

// 입력 함수
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
        print_char(c); // 화면에 입력한 문자 출력
    }
    buffer[i] = '\0'; // 문자열 종료
}

// 파일 시스템 함수
int create_file(const char *filename, const uint8_t *data, uint32_t size) {
    return create_file(filename, data, size);
}

int read_file(const char *filename, uint8_t *buffer, uint32_t size) {
    return read_file(filename, buffer, size);
}

int delete_file(const char *filename) {
    return delete_file(filename);
}

void list_files() {
    list_files();
}

// 네트워크 함수
#define IO_BASE 0x3000 // 네트워크 카드의 I/O 기본 주소 (예시)

void network_send(const uint8_t *data, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        outb(IO_BASE + 1, data[i]);
    }
}

int network_receive(uint8_t *buffer, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        buffer[i] = inb(IO_BASE + 1);
    }
    return size;
}

void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "dN"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

// 문자열을 정수로 변환
int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str) {
        result = result * 10 + (*str++ - '0');
    }
    return sign * result;
}

// 정수를 문자열로 변환
void itoa(int num, char *str) {
    int i = 0;
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    if (is_negative) {
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str);
}

// 문자열을 뒤집기
void reverse(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

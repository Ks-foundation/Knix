#ifndef KNIXLIB_H
#define KNIXLIB_H

#include <stdint.h>

// 텍스트 출력 함수
void print_string(const char *str);
void print_char(char c);

// 입력 함수
char get_char();
void read_input(char *buffer, int max_length);

// 파일 시스템 함수
int create_file(const char *filename, const uint8_t *data, uint32_t size);
int read_file(const char *filename, uint8_t *buffer, uint32_t size);
int delete_file(const char *filename);
void list_files();

// 네트워크 함수
void network_send(const uint8_t *data, uint32_t size);
int network_receive(uint8_t *buffer, uint32_t size);

// 유틸리티 함수
int atoi(const char *str);
void itoa(int num, char *str);
void reverse(char *str);

#endif // KNIXLIB_H

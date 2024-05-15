#ifndef SSD_FS_H
#define SSD_FS_H

#include "ssd_editor.h"
#include <stdint.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 1024
#define MAX_FILES 100
#define FILENAME_LENGTH 32
#define MAX_PATH_LENGTH 256
#define MAX_DIRS 100

// 파일 및 디렉터리 엔트리 구조체 정의
typedef struct {
    char filename[FILENAME_LENGTH];
    uint32_t start_block;
    uint32_t size;
    uint8_t is_directory; // 디렉터리 여부
} file_entry_t;

// 파일 시스템 구조체 정의
typedef struct {
    file_entry_t files[MAX_FILES];
    uint8_t block_bitmap[NUM_BLOCKS / 8]; // 블록 사용 여부를 추적하는 비트맵
    file_entry_t *current_directory; // 현재 디렉터리
} filesystem_t;

extern filesystem_t fs;

// 함수 선언
void init_fs();
int create_file(const char *filename, const uint8_t *data, uint32_t size);
int read_file(const char *filename, uint8_t *buffer, uint32_t size);
int delete_file(const char *filename);
int create_directory(const char *dirname);
int remove_directory(const char *dirname);
int change_directory(const char *dirname);
void list_files();
int execute_file(const char *filename);

#endif // SSD_FS_H


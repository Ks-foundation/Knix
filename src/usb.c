#include "usb.h"

int read_usb_sector(uint32_t lba, uint8_t *buffer) {
    // USB 장치 번호 (0x80은 첫 번째 하드 디스크, USB는 다를 수 있음)
    uint8_t device = 0x80;
    uint8_t sector_count = 1;

    // BIOS 인터럽트 13h를 사용하여 LBA 주소에서 섹터 읽기
    __asm__ __volatile__ (
        "mov $0x42, %%ah\n"       // AH에 0x42 (LBA 읽기) 설정
        "mov %1, %%dl\n"          // DL에 장치 번호 설정
        "mov %2, %%esi\n"         // ESI에 DAP 포인터 설정
        "int $0x13\n"             // BIOS 인터럽트 호출
        :                         // 출력 없음
        : "a" (0x4200), "d" (device), "S" (&lba)
        : "memory"
    );

    // 읽은 데이터가 buffer에 저장됨
    return 0;
}

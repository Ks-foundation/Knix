#ifndef SSD_EDITOR_H
#define SSD_EDITOR_H

#include <stdint.h>
#include <stdio.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

// PCIe 구성 공간에서 레지스터 읽기 함수
static inline uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint32_t tmp = 0;

    // 구성 주소 형성
    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

    // 구성 주소를 IO 포트에 쓰기
    __asm__ __volatile__("outl %0, %1" : : "a"(address), "d" (PCI_CONFIG_ADDRESS));

    // 구성 데이터를 IO 포트에서 읽기
    __asm__ __volatile__("inl %1, %0" : "=a"(tmp) : "d" (PCI_CONFIG_DATA));
    return tmp;
}

// PCIe 구성 공간에서 레지스터 쓰기 함수
static inline void pci_write(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    // 구성 주소 형성
    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

    // 구성 주소를 IO 포트에 쓰기
    __asm__ __volatile__("outl %0, %1" : : "a"(address), "d" (PCI_CONFIG_ADDRESS));

    // 구성 데이터를 IO 포트에 쓰기
    __asm__ __volatile__("outl %0, %1" : : "a"(value), "d" (PCI_CONFIG_DATA));
}

// SSD 데이터 읽기 함수
static inline int read_ssd_data(uint64_t base_address, uint8_t *buffer, uint32_t size) {
    if (buffer == NULL) {
        fprintf(stderr, "Invalid buffer\n");
        return -1;
    }

    // 예제: MMIO를 통해 base_address에서 size만큼 데이터를 읽어 buffer에 저장
    for (uint32_t i = 0; i < size; i++) {
        __asm__ __volatile__("movb (%1, %2), %0"
                             : "=r"(buffer[i])
                             : "r"(base_address), "r"(i));
    }
    return 0;
}

// SSD 데이터 쓰기 함수
static inline int write_ssd_data(uint64_t base_address, const uint8_t *data, uint32_t size) {
    if (data == NULL) {
        fprintf(stderr, "Invalid data\n");
        return -1;
    }

    // 예제: MMIO를 통해 base_address에 data를 size만큼 씁니다.
    for (uint32_t i = 0; i < size; i++) {
        __asm__ __volatile__("movb %0, (%1, %2)"
                             :
                             : "r"(data[i]), "r"(base_address), "r"(i));
    }
    return 0;
}

#endif // SSD_EDITOR_H

void main() {
    char *video_memory = (char *) 0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        *video_memory++ = ' ';
        *video_memory++ = 0x01; // 파란색 텍스트, 검은색 배경
    }
    while (1);
}

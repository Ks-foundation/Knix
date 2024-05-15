void main() {
    char *video_memory = (char *) 0xB8000;
    const char *message = "Echo: Hello, KinX!";
    while (*message) {
        *video_memory++ = *message++;
        *video_memory++ = 0x01; // 파란색 텍스트, 검은색 배경
    }
    while (1);
}

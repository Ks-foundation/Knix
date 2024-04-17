section .text
    ; 부트로더 시작 지점
    global _start
    _start:
        ; 화면을 파란색으로 설정
        mov ah, 0x00 ; 비디오 서비스 호출
        mov al, 0x13 ; 320x200 256색 모드로 설정
        int 0x10     ; 비디오 인터럽트 호출

        ; "knix" 문자열을 출력
        mov si, knix_msg ; knix_msg 주소를 SI 레지스터에 로드
    print_knix:
        lodsb           ; SI가 가리키는 문자를 AL에 로드하고 SI를 다음 문자로 증가
        or al, al       ; AL이 0인지 확인
        jz end_print    ; 만약 AL이 0이라면 문자열의 끝에 도달했으므로 종료
        mov ah, 0x0E    ; 텔레타입 서비스 호출
        mov bh, 0x00    ; 페이지 번호 (0)
        mov bl, 0x1F    ; 색상 (파란색 배경, 흰색 글자)
        int 0x10        ; 비디오 인터럽트 호출
        jmp print_knix  ; 다음 문자 출력을 위해 루프 반복

    end_print:

        ; kernel.elf 파일 로드
        mov si, kernel_name ; kernel_name 주소를 SI 레지스터에 로드
        call load_kernel    ; kernel을 메모리에 로드하는 함수 호출

        ; kernel 로드 후에 실행할 코드 추가 가능

    halt:   ; 부트로더 종료
        jmp halt

    ; kernel.elf 파일을 로드하는 함수
    load_kernel:
        ; 파일을 읽을 디스크 번호를 DL 레지스터에 로드
        mov dl, 0x00 ; 첫 번째 디스크 (보통 부팅 디스크)
        ; 파일 이름과 확장자를 SI에서 로드
        mov ah, 0x03 ; 파일 읽기 서비스 호출
        mov al, 0x00 ; 읽기 모드 (시작)
        mov ch, 0x00 ; 트랙 번호 (0)
        mov cl, 0x02 ; 섹터 번호 (2)
        mov dh, 0x00 ; 헤드 번호 (0)
        mov bx, 0x1000 ; 로드할 주소 (0x1000부터)
        int 0x13      ; 디스크 인터럽트 호출
        ret

    section .data
    ; "knix" 문자열 선언
    knix_msg db 'knix', 0
    ; kernel 파일 이름 선언
    kernel_name db 'KERNEL.ELF', 0

    section .bss
    ; 사용되지 않은 메모리 공간

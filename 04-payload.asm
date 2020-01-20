BITS 64
%define SYS_WRITE 1
%define SYS_EXIT 60
%define STDOUT 1

_start:
    ;; write
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    lea rsi, [rel hello]
    mov rdx, hello_size
    syscall

    ret

hello: db "Hello, World", 10
hello_size: equ $-hello

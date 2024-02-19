log_wrapper(int64_t arg1, int64_t arg2, int64_t arg3);
; arg int64_t arg1 @ rdi
; arg int64_t arg2 @ rsi
; arg int64_t arg3 @ rdx
; var int64_t var_138h @ stack - 0x138
; var int64_t var_130h @ stack - 0x130
; var int64_t var_128h @ stack - 0x128
; var int64_t var_120h @ stack - 0x120
; var int64_t var_118h @ stack - 0x118
; var int64_t var_10h @ stack - 0x10
0x004008c4      push    rbp
0x004008c5      mov     rbp, rsp
0x004008c8      sub     rsp, 0x130
0x004008cf      mov     qword [var_120h], rdi ; arg1
0x004008d6      mov     qword [var_128h], rsi ; arg2
0x004008dd      mov     qword [var_130h], rdx ; arg3
0x004008e4      mov     rax, qword fs:[0x28]
0x004008ed      mov     qword [var_10h], rax
0x004008f1      xor     eax, eax
0x004008f3      mov     rdx, qword [var_128h]
0x004008fa      lea     rax, [var_118h]
0x00400901      mov     rsi, rdx
0x00400904      mov     rdi, rax
0x00400907      call    strcpy     ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
0x0040090c      mov     rsi, qword [var_130h]
0x00400913      lea     rax, [var_118h]
0x0040091a      mov     qword [var_138h], 0xffffffffffffffff
0x00400925      mov     rdx, rax
0x00400928      mov     eax, 0
0x0040092d      mov     rcx, qword [var_138h]
0x00400934      mov     rdi, rdx
0x00400937      repne   scasb al, byte [rdi]
0x00400939      mov     rax, rcx
0x0040093c      not     rax
0x0040093f      lea     rdx, [rax - 1]
0x00400943      mov     eax, 0xfe  ; 254
0x00400948      mov     r8, rax
0x0040094b      sub     r8, rdx
0x0040094e      lea     rax, [var_118h]
0x00400955      mov     qword [var_138h], 0xffffffffffffffff
0x00400960      mov     rdx, rax
0x00400963      mov     eax, 0
0x00400968      mov     rcx, qword [var_138h]
0x0040096f      mov     rdi, rdx
0x00400972      repne   scasb al, byte [rdi]
0x00400974      mov     rax, rcx
0x00400977      not     rax
0x0040097a      lea     rdx, [rax - 1]
0x0040097e      lea     rax, [var_118h]
0x00400985      add     rax, rdx
0x00400988      mov     rdx, rsi
0x0040098b      mov     rsi, r8
0x0040098e      mov     rdi, rax
0x00400991      mov     eax, 0
0x00400996      call    snprintf   ; sym.imp.snprintf ; int snprintf(char *s, size_t size, const char *format, va_list args)
0x0040099b      lea     rax, [var_118h]
0x004009a2      mov     esi, 0x400d4c
0x004009a7      mov     rdi, rax
0x004009aa      call    strcspn    ; sym.imp.strcspn ; size_t strcspn(const char *s1, const char *s2)
0x004009af      mov     byte [rbp + rax - 0x110], 0
0x004009b7      mov     ecx, str.LOG:__s ; 0x400d4e
0x004009bc      lea     rdx, [var_118h]
0x004009c3      mov     rax, qword [var_120h]
0x004009ca      mov     rsi, rcx
0x004009cd      mov     rdi, rax
0x004009d0      mov     eax, 0
0x004009d5      call    fprintf    ; sym.imp.fprintf ; int fprintf(FILE *stream, const char *format, void *va_args)
0x004009da      mov     rax, qword [var_10h]
0x004009de      xor     rax, qword fs:[0x28]
0x004009e7      je      0x4009ee
0x004009e9      call    __stack_chk_fail ; sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
0x004009ee      leave
0x004009ef      ret

int main(int argc, char **argv, char **envp);
; arg int argc @ rdi
; arg char **argv @ rsi
; var int64_t var_b0h @ stack - 0xb0
; var int64_t var_a8h @ stack - 0xa8
; var int64_t var_9ch @ stack - 0x9c
; var int64_t var_90h @ stack - 0x90
; var int64_t var_88h @ stack - 0x88
; var int64_t var_80h @ stack - 0x80
; var int64_t var_79h @ stack - 0x79
; var int64_t var_78h @ stack - 0x78
; var int64_t var_10h @ stack - 0x10
0x004009f0      push    rbp
0x004009f1      mov     rbp, rsp
0x004009f4      sub     rsp, 0xb0
0x004009fb      mov     dword [var_9ch], edi ; argc
0x00400a01      mov     qword [var_a8h], rsi ; argv
0x00400a08      mov     rax, qword fs:[0x28]
0x00400a11      mov     qword [var_10h], rax
0x00400a15      xor     eax, eax
0x00400a17      mov     byte [var_79h], 0xff ; 255
0x00400a1b      mov     dword [var_80h], 0xffffffff ; -1
0x00400a22      cmp     dword [var_9ch], 2
0x00400a29      je      0x400a4a
0x00400a2b      mov     rax, qword [var_a8h]
0x00400a32      mov     rdx, qword [rax]
0x00400a35      mov     eax, str.Usage:__s_filename ; 0x400d57
0x00400a3a      mov     rsi, rdx
0x00400a3d      mov     rdi, rax
0x00400a40      mov     eax, 0
0x00400a45      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400a4a      mov     edx, 0x400d6b
0x00400a4f      mov     eax, str.._backups_.log ; 0x400d6d
0x00400a54      mov     rsi, rdx
0x00400a57      mov     rdi, rax
0x00400a5a      call    fopen      ; sym.imp.fopen ; FILE *fopen(const char *filename, const char *mode)
0x00400a5f      mov     qword [var_90h], rax
0x00400a66      cmp     qword [var_90h], 0
0x00400a6e      jne     0x400a91
0x00400a70      mov     eax, str.ERROR:_Failed_to_open__s ; 0x400d7c
0x00400a75      mov     esi, str.._backups_.log ; 0x400d6d
0x00400a7a      mov     rdi, rax
0x00400a7d      mov     eax, 0
0x00400a82      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400a87      mov     edi, 1
0x00400a8c      call    exit       ; sym.imp.exit ; void exit(int status)
0x00400a91      mov     rax, qword [var_a8h]
0x00400a98      add     rax, 8
0x00400a9c      mov     rdx, qword [rax]
0x00400a9f      mov     rax, qword [var_90h]
0x00400aa6      mov     esi, str.Starting_back_up: ; 0x400d96
0x00400aab      mov     rdi, rax
0x00400aae      call    log_wrapper ; sym.log_wrapper
0x00400ab3      mov     edx, 0x400da9
0x00400ab8      mov     rax, qword [var_a8h]
0x00400abf      add     rax, 8
0x00400ac3      mov     rax, qword [rax]
0x00400ac6      mov     rsi, rdx
0x00400ac9      mov     rdi, rax
0x00400acc      call    fopen      ; sym.imp.fopen ; FILE *fopen(const char *filename, const char *mode)
0x00400ad1      mov     qword [var_88h], rax
0x00400ad5      cmp     qword [var_88h], 0
0x00400ada      jne     0x400b09
0x00400adc      mov     rax, qword [var_a8h]
0x00400ae3      add     rax, 8
0x00400ae7      mov     rdx, qword [rax]
0x00400aea      mov     eax, str.ERROR:_Failed_to_open__s ; 0x400d7c
0x00400aef      mov     rsi, rdx
0x00400af2      mov     rdi, rax
0x00400af5      mov     eax, 0
0x00400afa      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400aff      mov     edi, 1
0x00400b04      call    exit       ; sym.imp.exit ; void exit(int status)
0x00400b09      mov     edx, str.._backups ; 0x400dab
0x00400b0e      lea     rax, [var_78h]
0x00400b12      mov     rcx, qword [rdx]
0x00400b15      mov     qword [rax], rcx
0x00400b18      movzx   ecx, word [rdx + 8]
0x00400b1c      mov     word [rax + 8], cx
0x00400b20      movzx   edx, byte [rdx + 0xa]
0x00400b24      mov     byte [rax + 0xa], dl
0x00400b27      lea     rax, [var_78h]
0x00400b2b      mov     qword [var_b0h], 0xffffffffffffffff
0x00400b36      mov     rdx, rax
0x00400b39      mov     eax, 0
0x00400b3e      mov     rcx, qword [var_b0h]
0x00400b45      mov     rdi, rdx
0x00400b48      repne   scasb al, byte [rdi]
0x00400b4a      mov     rax, rcx
0x00400b4d      not     rax
0x00400b50      lea     rdx, [rax - 1]
0x00400b54      mov     eax, 0x63  ; 'c' ; 99
0x00400b59      mov     rcx, rax
0x00400b5c      sub     rcx, rdx
0x00400b5f      mov     rdx, rcx
0x00400b62      mov     rax, qword [var_a8h]
0x00400b69      add     rax, 8
0x00400b6d      mov     rax, qword [rax]
0x00400b70      mov     rcx, rax
0x00400b73      lea     rax, [var_78h]
0x00400b77      mov     rsi, rcx
0x00400b7a      mov     rdi, rax
0x00400b7d      call    strncat    ; sym.imp.strncat ; char *strncat(char *s1, const char *s2, size_t n)
0x00400b82      lea     rax, [var_78h]
0x00400b86      mov     edx, 0x1b0 ; 432
0x00400b8b      mov     esi, 0xc1  ; 193
0x00400b90      mov     rdi, rax
0x00400b93      mov     eax, 0
0x00400b98      call    open       ; sym.imp.open ; int open(const char *path, int oflag)
0x00400b9d      mov     dword [var_80h], eax
0x00400ba0      cmp     dword [var_80h], 0
0x00400ba4      jns     0x400bed
0x00400ba6      mov     rax, qword [var_a8h]
0x00400bad      add     rax, 8
0x00400bb1      mov     rdx, qword [rax]
0x00400bb4      mov     eax, str.ERROR:_Failed_to_open__s_s ; 0x400db6
0x00400bb9      mov     esi, str.._backups ; 0x400dab
0x00400bbe      mov     rdi, rax
0x00400bc1      mov     eax, 0
0x00400bc6      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400bcb      mov     edi, 1
0x00400bd0      call    exit       ; sym.imp.exit ; void exit(int status)
0x00400bd5      lea     rcx, [var_79h]
0x00400bd9      mov     eax, dword [var_80h]
0x00400bdc      mov     edx, 1
0x00400be1      mov     rsi, rcx
0x00400be4      mov     edi, eax
0x00400be6      call    write      ; sym.imp.write ; ssize_t write(int fd, const char *ptr, size_t nbytes)
0x00400beb      jmp     0x400bee
0x00400bed      nop
0x00400bee      mov     rax, qword [var_88h]
0x00400bf2      mov     rdi, rax
0x00400bf5      call    fgetc      ; sym.imp.fgetc ; int fgetc(FILE *stream)
0x00400bfa      mov     byte [var_79h], al
0x00400bfd      movzx   eax, byte [var_79h]
0x00400c01      cmp     al, 0xff   ; 255
0x00400c03      jne     0x400bd5
0x00400c05      mov     rax, qword [var_a8h]
0x00400c0c      add     rax, 8
0x00400c10      mov     rdx, qword [rax]
0x00400c13      mov     rax, qword [var_90h]
0x00400c1a      mov     esi, str.Finished_back_up ; 0x400dd2
0x00400c1f      mov     rdi, rax
0x00400c22      call    log_wrapper ; sym.log_wrapper
0x00400c27      mov     rax, qword [var_88h]
0x00400c2b      mov     rdi, rax
0x00400c2e      call    fclose     ; sym.imp.fclose ; int fclose(FILE *stream)
0x00400c33      mov     eax, dword [var_80h]
0x00400c36      mov     edi, eax
0x00400c38      call    close      ; sym.imp.close ; int close(int fildes)
0x00400c3d      mov     eax, 0
0x00400c42      mov     rdi, qword [var_10h]
0x00400c46      xor     rdi, qword fs:[0x28]
0x00400c4f      je      0x400c56
0x00400c51      call    __stack_chk_fail ; sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
0x00400c56      leave
0x00400c57      ret
0x00400c58      nop
0x00400c59      nop
0x00400c5a      nop
0x00400c5b      nop
0x00400c5c      nop
0x00400c5d      nop
0x00400c5e      nop
0x00400c5f      nop
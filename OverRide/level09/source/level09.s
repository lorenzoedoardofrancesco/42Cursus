secret_backdoor();
; var int64_t var_88h @ stack - 0x88
0x0000088c      push    rbp
0x0000088d      mov     rbp, rsp
0x00000890      add     rsp, 0xffffffffffffff80
0x00000894      mov     rax, qword [stdin] ; 0x201fb8
0x0000089b      mov     rax, qword [rax]
0x0000089e      mov     rdx, rax
0x000008a1      lea     rax, [var_88h]
0x000008a5      mov     esi, 0x80
0x000008aa      mov     rdi, rax
0x000008ad      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x000008b2      lea     rax, [var_88h]
0x000008b6      mov     rdi, rax
0x000008b9      call    system     ; sym.imp.system ; int system(const char *string)
0x000008be      leave
0x000008bf      ret

handle_msg();
; var int64_t var_c8h @ stack - 0xc8
; var int64_t var_14h @ stack - 0x14
0x000008c0      push    rbp
0x000008c1      mov     rbp, rsp
0x000008c4      sub     rsp, 0xc0
0x000008cb      lea     rax, [var_c8h]
0x000008d2      add     rax, 0x8c
0x000008d8      mov     qword [rax], 0
0x000008df      mov     qword [rax + 8], 0
0x000008e7      mov     qword [rax + 0x10], 0
0x000008ef      mov     qword [rax + 0x18], 0
0x000008f7      mov     qword [rax + 0x20], 0
0x000008ff      mov     dword [var_14h], 0x8c
0x00000906      lea     rax, [var_c8h]
0x0000090d      mov     rdi, rax
0x00000910      call    set_username ; sym.set_username
0x00000915      lea     rax, [var_c8h]
0x0000091c      mov     rdi, rax
0x0000091f      call    set_msg    ; sym.set_msg
0x00000924      lea     rdi, str.:_Msg_sent ; 0xbc0
0x0000092b      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x00000930      leave
0x00000931      ret

set_msg(int64_t arg1);
; arg int64_t arg1 @ rdi
; var int64_t var_410h @ stack - 0x410
; var int64_t var_408h @ stack - 0x408
0x00000932      push    rbp
0x00000933      mov     rbp, rsp
0x00000936      sub     rsp, 0x410
0x0000093d      mov     qword [var_410h], rdi ; arg1
0x00000944      lea     rax, [var_408h]
0x0000094b      mov     rsi, rax
0x0000094e      mov     eax, 0
0x00000953      mov     edx, 0x80
0x00000958      mov     rdi, rsi
0x0000095b      mov     rcx, rdx
0x0000095e      rep     stosq qword [rdi], rax
0x00000961      lea     rdi, str.:_Msg__Unix_Dude ; 0xbcd
0x00000968      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x0000096d      lea     rax, str.: ; 0xbdf
0x00000974      mov     rdi, rax
0x00000977      mov     eax, 0
0x0000097c      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00000981      mov     rax, qword [stdin] ; 0x201fb8
0x00000988      mov     rax, qword [rax]
0x0000098b      mov     rdx, rax
0x0000098e      lea     rax, [var_408h]
0x00000995      mov     esi, 0x400
0x0000099a      mov     rdi, rax
0x0000099d      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x000009a2      mov     rax, qword [var_410h]
0x000009a9      mov     eax, dword [rax + 0xb4]
0x000009af      movsxd  rdx, eax
0x000009b2      lea     rcx, [var_408h]
0x000009b9      mov     rax, qword [var_410h]
0x000009c0      mov     rsi, rcx
0x000009c3      mov     rdi, rax
0x000009c6      call    strncpy    ; sym.imp.strncpy ; char *strncpy(char *dest, const char *src, size_t  n)
0x000009cb      leave
0x000009cc      ret

set_username(int64_t arg1);
; arg int64_t arg1 @ rdi
; var int64_t var_a0h @ stack - 0xa0
; var int64_t var_98h @ stack - 0x98
; var int64_t var_ch @ stack - 0xc
0x000009cd      push    rbp
0x000009ce      mov     rbp, rsp
0x000009d1      sub     rsp, 0xa0
0x000009d8      mov     qword [var_a0h], rdi ; arg1
0x000009df      lea     rax, [var_98h]
0x000009e6      mov     rsi, rax
0x000009e9      mov     eax, 0
0x000009ee      mov     edx, 0x10
0x000009f3      mov     rdi, rsi
0x000009f6      mov     rcx, rdx
0x000009f9      rep     stosq qword [rdi], rax
0x000009fc      lea     rdi, str.:_Enter_your_username ; 0xbe4
0x00000a03      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x00000a08      lea     rax, str.: ; 0xbdf
0x00000a0f      mov     rdi, rax
0x00000a12      mov     eax, 0
0x00000a17      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00000a1c      mov     rax, qword [stdin] ; 0x201fb8
0x00000a23      mov     rax, qword [rax]
0x00000a26      mov     rdx, rax
0x00000a29      lea     rax, [var_98h]
0x00000a30      mov     esi, 0x80
0x00000a35      mov     rdi, rax
0x00000a38      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x00000a3d      mov     dword [var_ch], 0
0x00000a44      jmp     0xa6a
0x00000a46      mov     eax, dword [var_ch]
0x00000a49      cdqe
0x00000a4b      movzx   ecx, byte [rbp + rax - 0x90]
0x00000a53      mov     rdx, qword [var_a0h]
0x00000a5a      mov     eax, dword [var_ch]
0x00000a5d      cdqe
0x00000a5f      mov     byte [rdx + rax + 0x8c], cl
0x00000a66      add     dword [var_ch], 1
0x00000a6a      cmp     dword [var_ch], 0x28
0x00000a6e      jg      0xa81
0x00000a70      mov     eax, dword [var_ch]
0x00000a73      cdqe
0x00000a75      movzx   eax, byte [rbp + rax - 0x90]
0x00000a7d      test    al, al
0x00000a7f      jne     0xa46
0x00000a81      mov     rax, qword [var_a0h]
0x00000a88      lea     rdx, [rax + 0x8c]
0x00000a8f      lea     rax, str.:_Welcome___s ; 0xbfb
0x00000a96      mov     rsi, rdx
0x00000a99      mov     rdi, rax
0x00000a9c      mov     eax, 0
0x00000aa1      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00000aa6      leave
0x00000aa7      ret
int main(int argc, char **argv, char **envp);
0x00000aa8      push    rbp
0x00000aa9      mov     rbp, rsp
0x00000aac      lea     rdi, str.Welcome_to_l33t_m_n______v1337 ; 0xc10
0x00000ab3      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x00000ab8      call    handle_msg ; sym.handle_msg
0x00000abd      mov     eax, 0
0x00000ac2      pop     rbp
0x00000ac3      ret
0x00000ac4      nop
0x00000ac5      nop
0x00000ac6      nop
0x00000ac7      nop
0x00000ac8      nop
0x00000ac9      nop
0x00000aca      nop
0x00000acb      nop
0x00000acc      nop
0x00000acd      nop
0x00000ace      nop
0x00000acf      nop
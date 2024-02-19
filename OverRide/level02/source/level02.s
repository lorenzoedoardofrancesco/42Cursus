int main(int argc, char **argv, char **envp);
; arg int argc @ rdi
; arg char **argv @ rsi
; var int64_t var_128h @ stack - 0x128
; var int64_t var_11ch @ stack - 0x11c
; var int64_t var_118h @ stack - 0x118
; var int64_t var_a8h @ stack - 0xa8
; var int64_t var_78h @ stack - 0x78
; var int64_t var_14h @ stack - 0x14
; var int64_t var_10h @ stack - 0x10
0x00400814      push    rbp
0x00400815      mov     rbp, rsp
0x00400818      sub     rsp, 0x120
0x0040081f      mov     dword [var_11ch], edi ; argc
0x00400825      mov     qword [var_128h], rsi ; argv
0x0040082c      lea     rdx, [var_78h]
0x00400830      mov     eax, 0
0x00400835      mov     ecx, 0xc   ; 12
0x0040083a      mov     rdi, rdx
0x0040083d      rep     stosq qword [rdi], rax
0x00400840      mov     rdx, rdi
0x00400843      mov     dword [rdx], eax
0x00400845      add     rdx, 4
0x00400849      lea     rdx, [var_a8h]
0x00400850      mov     eax, 0
0x00400855      mov     ecx, 5
0x0040085a      mov     rdi, rdx
0x0040085d      rep     stosq qword [rdi], rax
0x00400860      mov     rdx, rdi
0x00400863      mov     byte [rdx], al
0x00400865      add     rdx, 1
0x00400869      lea     rdx, [var_118h]
0x00400870      mov     eax, 0
0x00400875      mov     ecx, 0xc   ; 12
0x0040087a      mov     rdi, rdx
0x0040087d      rep     stosq qword [rdi], rax
0x00400880      mov     rdx, rdi
0x00400883      mov     dword [rdx], eax
0x00400885      add     rdx, 4
0x00400889      mov     qword [var_10h], 0
0x00400891      mov     dword [var_14h], 0
0x00400898      mov     edx, 0x400bb0
0x0040089d      mov     eax, str.home_users_level03_.pass ; 0x400bb2
0x004008a2      mov     rsi, rdx
0x004008a5      mov     rdi, rax
0x004008a8      call    fopen      ; sym.imp.fopen ; FILE *fopen(const char *filename, const char *mode)
0x004008ad      mov     qword [var_10h], rax
0x004008b1      cmp     qword [var_10h], 0
0x004008b6      jne     0x4008e6
0x004008b8      mov     rax, qword stderr ; obj.stderr__GLIBC_2.2.5
                                   ; 0x601250
0x004008bf      mov     rdx, rax
0x004008c2      mov     eax, str.ERROR:_failed_to_open_password_file ; 0x400bd0
0x004008c7      mov     rcx, rdx
0x004008ca      mov     edx, 0x24  ; '$' ; 36
0x004008cf      mov     esi, 1
0x004008d4      mov     rdi, rax
0x004008d7      call    fwrite     ; sym.imp.fwrite ; size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
0x004008dc      mov     edi, 1
0x004008e1      call    exit       ; sym.imp.exit ; void exit(int status)
0x004008e6      lea     rax, [var_a8h]
0x004008ed      mov     rdx, qword [var_10h]
0x004008f1      mov     rcx, rdx
0x004008f4      mov     edx, 0x29  ; ')' ; 41
0x004008f9      mov     esi, 1
0x004008fe      mov     rdi, rax
0x00400901      call    fread      ; sym.imp.fread ; size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
0x00400906      mov     dword [var_14h], eax
0x00400909      lea     rax, [var_a8h]
0x00400910      mov     esi, 0x400bf5
0x00400915      mov     rdi, rax
0x00400918      call    strcspn    ; sym.imp.strcspn ; size_t strcspn(const char *s1, const char *s2)
0x0040091d      mov     byte [rbp + rax - 0xa0], 0
0x00400925      cmp     dword [var_14h], 0x29
0x00400929      je      0x40097d
0x0040092b      mov     rax, qword stderr ; obj.stderr__GLIBC_2.2.5
                                   ; 0x601250
0x00400932      mov     rdx, rax
0x00400935      mov     eax, str.ERROR:_failed_to_read_password_file ; 0x400bf8
0x0040093a      mov     rcx, rdx
0x0040093d      mov     edx, 0x24  ; '$' ; 36
0x00400942      mov     esi, 1
0x00400947      mov     rdi, rax
0x0040094a      call    fwrite     ; sym.imp.fwrite ; size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
0x0040094f      mov     rax, qword stderr ; obj.stderr__GLIBC_2.2.5
                                   ; 0x601250
0x00400956      mov     rdx, rax
0x00400959      mov     eax, str.ERROR:_failed_to_read_password_file ; 0x400bf8
0x0040095e      mov     rcx, rdx
0x00400961      mov     edx, 0x24  ; '$' ; 36
0x00400966      mov     esi, 1
0x0040096b      mov     rdi, rax
0x0040096e      call    fwrite     ; sym.imp.fwrite ; size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
0x00400973      mov     edi, 1
0x00400978      call    exit       ; sym.imp.exit ; void exit(int status)
0x0040097d      mov     rax, qword [var_10h]
0x00400981      mov     rdi, rax
0x00400984      call    fclose     ; sym.imp.fclose ; int fclose(FILE *stream)
0x00400989      mov     edi, str.Secure_Access_System_v1.0 ; 0x400c20
0x0040098e      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x00400993      mov     edi, 0x400c50
0x00400998      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x0040099d      mov     edi, str.You_must_login_to_access_this_system. ; 0x400c80
0x004009a2      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x004009a7      mov     edi, 0x400cb0
0x004009ac      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x004009b1      mov     eax, str.Username: ; 0x400cd9
0x004009b6      mov     rdi, rax
0x004009b9      mov     eax, 0
0x004009be      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x004009c3      mov     rax, qword stdin ; loc.__bss_start
                                   ; 0x601248
0x004009ca      mov     rdx, rax
0x004009cd      lea     rax, [var_78h]
0x004009d1      mov     esi, 0x64  ; 'd' ; 100
0x004009d6      mov     rdi, rax
0x004009d9      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x004009de      lea     rax, [var_78h]
0x004009e2      mov     esi, 0x400bf5
0x004009e7      mov     rdi, rax
0x004009ea      call    strcspn    ; sym.imp.strcspn ; size_t strcspn(const char *s1, const char *s2)
0x004009ef      mov     byte [rbp + rax - 0x70], 0
0x004009f4      mov     eax, str.Password: ; 0x400ce8
0x004009f9      mov     rdi, rax
0x004009fc      mov     eax, 0
0x00400a01      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400a06      mov     rax, qword stdin ; loc.__bss_start
                                   ; 0x601248
0x00400a0d      mov     rdx, rax
0x00400a10      lea     rax, [var_118h]
0x00400a17      mov     esi, 0x64  ; 'd' ; 100
0x00400a1c      mov     rdi, rax
0x00400a1f      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x00400a24      lea     rax, [var_118h]
0x00400a2b      mov     esi, 0x400bf5
0x00400a30      mov     rdi, rax
0x00400a33      call    strcspn    ; sym.imp.strcspn ; size_t strcspn(const char *s1, const char *s2)
0x00400a38      mov     byte [rbp + rax - 0x110], 0
0x00400a40      mov     edi, str.  ; 0x400cf8
0x00400a45      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x00400a4a      lea     rcx, [var_118h]
0x00400a51      lea     rax, [var_a8h]
0x00400a58      mov     edx, 0x29  ; ')' ; 41
0x00400a5d      mov     rsi, rcx
0x00400a60      mov     rdi, rax
0x00400a63      call    strncmp    ; sym.imp.strncmp ; int strncmp(const char *s1, const char *s2, size_t n)
0x00400a68      test    eax, eax
0x00400a6a      jne     0x400a96
0x00400a6c      mov     eax, str.Greetings___s ; 0x400d22
0x00400a71      lea     rdx, [var_78h]
0x00400a75      mov     rsi, rdx
0x00400a78      mov     rdi, rax
0x00400a7b      mov     eax, 0
0x00400a80      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400a85      mov     edi, str.bin_sh ; 0x400d32
0x00400a8a      call    system     ; sym.imp.system ; int system(const char *string)
0x00400a8f      mov     eax, 0
0x00400a94      leave
0x00400a95      ret
0x00400a96      lea     rax, [var_78h]
0x00400a9a      mov     rdi, rax
0x00400a9d      mov     eax, 0
0x00400aa2      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x00400aa7      mov     edi, str.does_not_have_access ; 0x400d3a
0x00400aac      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x00400ab1      mov     edi, 1
0x00400ab6      call    exit       ; sym.imp.exit ; void exit(int status)
0x00400abb      nop
0x00400abc      nop
0x00400abd      nop
0x00400abe      nop
0x00400abf      nop
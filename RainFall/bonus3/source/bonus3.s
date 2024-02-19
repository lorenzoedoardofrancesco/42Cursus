int main(int argc, char **argv, char **envp);
; var const char *size @ stack - 0xa8
; var size_t nmemb @ stack - 0xa4
; var FILE *stream @ stack - 0xa0
; var const char *ptr @ stack - 0x94
; var int32_t var_53h @ stack - 0x53
; var FILE *var_10h @ stack - 0x10
; var int32_t var_ch @ stack - 0xc
; arg char **argv @ stack + 0x4
; arg char **envp @ stack + 0x8
0x080484f4      push    ebp
0x080484f5      mov     ebp, esp
0x080484f7      push    edi
0x080484f8      push    ebx
0x080484f9      and     esp, 0xfffffff0
0x080484fc      sub     esp, 0xa0
0x08048502      mov     edx, data.080486f0 ; 0x80486f0
0x08048507      mov     eax, str.home_user_end_.pass ; 0x80486f2
0x0804850c      mov     dword [size], edx ; const char *mode
0x08048510      mov     dword [esp], eax ; const char *filename
0x08048513      call    fopen      ; sym.imp.fopen ; FILE *fopen(const char *filename, const char *mode)
0x08048518      mov     dword [var_10h], eax
0x0804851f      lea     ebx, [ptr]
0x08048523      mov     eax, 0
0x08048528      mov     edx, 0x21  ; '!' ; 33
0x0804852d      mov     edi, ebx
0x0804852f      mov     ecx, edx
0x08048531      rep     stosd dword es:[edi], eax
0x08048533      cmp     dword [var_10h], 0
0x0804853b      je      0x8048543
0x0804853d      cmp     dword [argv], 2
0x08048541      je      0x804854d
0x08048543      mov     eax, 0xffffffff ; -1
0x08048548      jmp     0x8048615
0x0804854d      lea     eax, [ptr]
0x08048551      mov     edx, dword [var_10h]
0x08048558      mov     dword [stream], edx ; FILE *stream
0x0804855c      mov     dword [nmemb], 0x42 ; 'B' ; 66 ; size_t nmemb
0x08048564      mov     dword [size], 1 ; size_t size
0x0804856c      mov     dword [esp], eax ; void *ptr
0x0804856f      call    fread      ; sym.imp.fread ; size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
0x08048574      mov     byte [var_53h], 0
0x08048579      mov     eax, dword [envp]
0x0804857c      add     eax, 4
0x0804857f      mov     eax, dword [eax]
0x08048581      mov     dword [esp], eax ; const char *str
0x08048584      call    atoi       ; sym.imp.atoi ; int atoi(const char *str)
0x08048589      mov     byte [esp + eax + 0x18], 0
0x0804858e      lea     eax, [ptr]
0x08048592      lea     edx, [eax + 0x42]
0x08048595      mov     eax, dword [var_10h]
0x0804859c      mov     dword [stream], eax ; FILE *stream
0x080485a0      mov     dword [nmemb], 0x41 ; 'A' ; 65 ; size_t nmemb
0x080485a8      mov     dword [size], 1 ; size_t size
0x080485b0      mov     dword [esp], edx ; void *ptr
0x080485b3      call    fread      ; sym.imp.fread ; size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
0x080485b8      mov     eax, dword [var_10h]
0x080485bf      mov     dword [esp], eax ; FILE *stream
0x080485c2      call    fclose     ; sym.imp.fclose ; int fclose(FILE *stream)
0x080485c7      mov     eax, dword [envp]
0x080485ca      add     eax, 4
0x080485cd      mov     eax, dword [eax]
0x080485cf      mov     dword [size], eax ; const char *s2
0x080485d3      lea     eax, [ptr]
0x080485d7      mov     dword [esp], eax ; const char *s1
0x080485da      call    strcmp     ; sym.imp.strcmp ; int strcmp(const char *s1, const char *s2)
0x080485df      test    eax, eax
0x080485e1      jne     0x8048601
0x080485e3      mov     dword [ptr], 0
0x080485eb      mov     dword [size], data.08048707 ; 0x8048707
0x080485f3      mov     dword [esp], str.bin_sh ; 0x804870a
0x080485fa      call    execl      ; sym.imp.execl
0x080485ff      jmp     0x8048610
0x08048601      lea     eax, [ptr]
0x08048605      add     eax, 0x42  ; 66
0x08048608      mov     dword [esp], eax ; const char *s
0x0804860b      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x08048610      mov     eax, 0
0x08048615      lea     esp, [var_ch]
0x08048618      pop     ebx
0x08048619      pop     edi
0x0804861a      pop     ebp
0x0804861b      ret
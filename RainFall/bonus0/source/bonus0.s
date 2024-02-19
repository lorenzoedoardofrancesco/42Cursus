p(char *dest, const char *s);
; var const char *src @ stack - 0x1018
; var size_t nbyte @ stack - 0x1014
; var const char *var_100ch @ stack - 0x100c
; arg char *dest @ stack + 0x4
; arg const char *s @ stack + 0x8
0x080484b4      push    ebp
0x080484b5      mov     ebp, esp
0x080484b7      sub     esp, 0x1018
0x080484bd      mov     eax, dword [s]
0x080484c0      mov     dword [esp], eax ; const char *s
0x080484c3      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080484c8      mov     dword [nbyte], 0x1000 ; size_t nbyte
0x080484d0      lea     eax, [var_100ch]
0x080484d6      mov     dword [src], eax ; void *buf
0x080484da      mov     dword [esp], 0 ; int fildes
0x080484e1      call    read       ; sym.imp.read ; ssize_t read(int fildes, void *buf, size_t nbyte)
0x080484e6      mov     dword [src], 0xa ; int c
0x080484ee      lea     eax, [var_100ch]
0x080484f4      mov     dword [esp], eax ; const char *s
0x080484f7      call    strchr     ; sym.imp.strchr ; char *strchr(const char *s, int c)
0x080484fc      mov     byte [eax], 0
0x080484ff      lea     eax, [var_100ch]
0x08048505      mov     dword [nbyte], 0x14 ; 20 ; size_t  n
0x0804850d      mov     dword [src], eax ; const char *src
0x08048511      mov     eax, dword [dest]
0x08048514      mov     dword [esp], eax ; char *dest
0x08048517      call    strncpy    ; sym.imp.strncpy ; char *strncpy(char *dest, const char *src, size_t  n)
0x0804851c      leave
0x0804851d      ret
pp(char *dest);
; var const char *src @ stack - 0x58
; var int32_t var_40h @ stack - 0x40
; var int32_t var_34h @ stack - 0x34
; var int32_t var_20h @ stack - 0x20
; arg char *dest @ stack + 0x4
0x0804851e      push    ebp
0x0804851f      mov     ebp, esp
0x08048521      push    edi
0x08048522      push    ebx
0x08048523      sub     esp, 0x50
0x08048526      mov     dword [src], data.080486a0 ; 0x80486a0 ; int32_t arg_4h
0x0804852e      lea     eax, [var_34h]
0x08048531      mov     dword [esp], eax ; int32_t arg_8h
0x08048534      call    p          ; sym.p
0x08048539      mov     dword [src], data.080486a0 ; 0x80486a0 ; int32_t arg_4h
0x08048541      lea     eax, [var_20h]
0x08048544      mov     dword [esp], eax ; int32_t arg_8h
0x08048547      call    p          ; sym.p
0x0804854c      lea     eax, [var_34h]
0x0804854f      mov     dword [src], eax ; const char *src
0x08048553      mov     eax, dword [dest]
0x08048556      mov     dword [esp], eax ; char *dest
0x08048559      call    strcpy     ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
0x0804855e      mov     ebx, data.080486a4 ; 0x80486a4
0x08048563      mov     eax, dword [dest]
0x08048566      mov     dword [var_40h], 0xffffffff ; -1
0x0804856d      mov     edx, eax
0x0804856f      mov     eax, 0
0x08048574      mov     ecx, dword [var_40h]
0x08048577      mov     edi, edx
0x08048579      repne   scasb al, byte es:[edi]
0x0804857b      mov     eax, ecx
0x0804857d      not     eax
0x0804857f      sub     eax, 1
0x08048582      add     eax, dword [dest]
0x08048585      movzx   edx, word [ebx]
0x08048588      mov     word [eax], dx
0x0804858b      lea     eax, [var_20h]
0x0804858e      mov     dword [src], eax ; const char *s2
0x08048592      mov     eax, dword [dest]
0x08048595      mov     dword [esp], eax ; char *s1
0x08048598      call    strcat     ; sym.imp.strcat ; char *strcat(char *s1, const char *s2)
0x0804859d      add     esp, 0x50
0x080485a0      pop     ebx
0x080485a1      pop     edi
0x080485a2      pop     ebp
0x080485a3      ret
int main(int argc, char **argv, char **envp);
; var const char *s @ stack - 0x2e
0x080485a4      push    ebp
0x080485a5      mov     ebp, esp
0x080485a7      and     esp, 0xfffffff0
0x080485aa      sub     esp, 0x40
0x080485ad      lea     eax, [s]
0x080485b1      mov     dword [esp], eax ; int32_t arg_4h
0x080485b4      call    pp         ; sym.pp
0x080485b9      lea     eax, [s]
0x080485bd      mov     dword [esp], eax ; const char *s
0x080485c0      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080485c5      mov     eax, 0
0x080485ca      leave
0x080485cb      ret
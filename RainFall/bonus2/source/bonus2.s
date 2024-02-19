int main(int argc, char **argv, char **envp);
; var const char *src @ stack - 0xac
; var size_t var_a8h @ stack - 0xa8
; var size_t n @ stack - 0x94
; var char *dest @ stack - 0x60
; var char *s1 @ stack - 0x14
; var int32_t var_10h @ stack - 0x10
; arg char **argv @ stack + 0x4
; arg char **envp @ stack + 0x8
0x08048529      push    ebp
0x0804852a      mov     ebp, esp
0x0804852c      push    edi
0x0804852d      push    esi
0x0804852e      push    ebx
0x0804852f      and     esp, 0xfffffff0
0x08048532      sub     esp, 0xa0
0x08048538      cmp     dword [argv], 3
0x0804853c      je      0x8048548
0x0804853e      mov     eax, 1
0x08048543      jmp     0x8048630
0x08048548      lea     ebx, [dest]
0x0804854c      mov     eax, 0
0x08048551      mov     edx, 0x13  ; 19
0x08048556      mov     edi, ebx
0x08048558      mov     ecx, edx
0x0804855a      rep     stosd dword es:[edi], eax
0x0804855c      mov     eax, dword [envp]
0x0804855f      add     eax, 4
0x08048562      mov     eax, dword [eax]
0x08048564      mov     dword [var_a8h], 0x28 ; '(' ; 40 ; size_t  n
0x0804856c      mov     dword [src], eax ; const char *src
0x08048570      lea     eax, [dest]
0x08048574      mov     dword [esp], eax ; char *dest
0x08048577      call    strncpy    ; sym.imp.strncpy ; char *strncpy(char *dest, const char *src, size_t  n)
0x0804857c      mov     eax, dword [envp]
0x0804857f      add     eax, 8
0x08048582      mov     eax, dword [eax]
0x08048584      mov     dword [var_a8h], 0x20 ; 32 ; size_t  n
0x0804858c      mov     dword [src], eax ; const char *src
0x08048590      lea     eax, [dest]
0x08048594      add     eax, 0x28  ; 40
0x08048597      mov     dword [esp], eax ; char *dest
0x0804859a      call    strncpy    ; sym.imp.strncpy ; char *strncpy(char *dest, const char *src, size_t  n)
0x0804859f      mov     dword [esp], str.LANG ; 0x8048738 ; const char *name
0x080485a6      call    getenv     ; sym.imp.getenv ; char *getenv(const char *name)
0x080485ab      mov     dword [s1], eax
0x080485b2      cmp     dword [s1], 0
0x080485ba      je      0x8048618
0x080485bc      mov     dword [n], 2 ; size_t n
0x080485c4      mov     dword [src], data.0804873d ; 0x804873d ; const void *s2
0x080485cc      mov     eax, dword [s1]
0x080485d3      mov     dword [esp], eax ; const void *s1
0x080485d6      call    memcmp     ; sym.imp.memcmp ; int memcmp(const void *s1, const void *s2, size_t n)
0x080485db      test    eax, eax
0x080485dd      jne     0x80485eb
0x080485df      mov     dword language, 1 ; 0x8049988
0x080485e9      jmp     0x8048618
0x080485eb      mov     dword [var_a8h], 2 ; size_t n
0x080485f3      mov     dword [src], data.08048740 ; 0x8048740 ; const void *s2
0x080485fb      mov     eax, dword [s1]
0x08048602      mov     dword [esp], eax ; const void *s1
0x08048605      call    memcmp     ; sym.imp.memcmp ; int memcmp(const void *s1, const void *s2, size_t n)
0x0804860a      test    eax, eax
0x0804860c      jne     0x8048618
0x0804860e      mov     dword language, 2 ; 0x8049988
0x08048618      mov     edx, esp
0x0804861a      lea     ebx, [dest]
0x0804861e      mov     eax, 0x13  ; 19
0x08048623      mov     edi, edx
0x08048625      mov     esi, ebx
0x08048627      mov     ecx, eax
0x08048629      rep     movsd dword es:[edi], dword ptr [esi] ; int32_t arg_4h
0x0804862b      call    greetuser  ; sym.greetuser
0x08048630      lea     esp, [var_10h]
0x08048633      pop     ebx
0x08048634      pop     esi
0x08048635      pop     edi
0x08048636      pop     ebp
0x08048637      ret
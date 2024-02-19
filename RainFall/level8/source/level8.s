int main(int argc, char **argv, char **envp);
; var const char *size @ stack - 0xa8
; var FILE *nitems @ stack - 0xa4
; var FILE *stream @ stack - 0xa0
; var int32_t var_90h @ stack - 0x90
; var char *src @ stack - 0x8c
; var int32_t var_7ch @ stack - 0x7c
; var int32_t var_ch @ stack - 0xc
0x08048564      push    ebp
0x08048565      mov     ebp, esp
0x08048567      push    edi
0x08048568      push    esi
0x08048569      and     esp, 0xfffffff0
0x0804856c      sub     esp, 0xa0
0x08048572      jmp     0x8048575
0x08048574      nop
0x08048575      mov     ecx, dword service ; 0x8049ab0
0x0804857b      mov     edx, dword auth ; 0x8049aac
0x08048581      mov     eax, str.p___p ; 0x8048810
0x08048586      mov     dword [nitems], ecx
0x0804858a      mov     dword [size], edx
0x0804858e      mov     dword [esp], eax ; const char *format
0x08048591      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x08048596      mov     eax, dword stdin ; obj.stdin__GLIBC_2.0
                                   ; 0x8049a80
0x0804859b      mov     dword [nitems], eax ; FILE *stream
0x0804859f      mov     dword [size], 0x80 ; 128 ; int size
0x080485a7      lea     eax, [src]
0x080485ab      mov     dword [esp], eax ; char *s
0x080485ae      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x080485b3      test    eax, eax
0x080485b5      je      0x804872c
0x080485bb      lea     eax, [var_7ch]
0x080485bf      mov     edx, eax
0x080485c1      mov     eax, str.auth ; 0x8048819
0x080485c6      mov     ecx, 5
0x080485cb      mov     esi, edx
0x080485cd      mov     edi, eax
0x080485cf      repe    cmpsb byte [esi], byte ptr es:[edi]
0x080485d1      seta    dl
0x080485d4      setb    al
0x080485d7      mov     ecx, edx
0x080485d9      sub     cl, al
0x080485db      mov     eax, ecx
0x080485dd      movsx   eax, al
0x080485e0      test    eax, eax
0x080485e2      jne     0x8048642
0x080485e4      mov     dword [esp], 4 ; size_t size
0x080485eb      call    malloc     ; sym.imp.malloc ; void *malloc(size_t size)
0x080485f0      mov     dword auth, eax ; 0x8049aac
0x080485f5      mov     eax, dword auth ; 0x8049aac
0x080485fa      mov     dword [eax], 0
0x08048600      lea     eax, [src]
0x08048604      add     eax, 5
0x08048607      mov     dword [var_90h], 0xffffffff ; -1
0x0804860f      mov     edx, eax
0x08048611      mov     eax, 0
0x08048616      mov     ecx, dword [var_90h]
0x0804861a      mov     edi, edx
0x0804861c      repne   scasb al, byte es:[edi]
0x0804861e      mov     eax, ecx
0x08048620      not     eax
0x08048622      sub     eax, 1
0x08048625      cmp     eax, 0x1e  ; 30
0x08048628      ja      0x8048642
0x0804862a      lea     eax, [src]
0x0804862e      lea     edx, [eax + 5]
0x08048631      mov     eax, dword auth ; 0x8049aac
0x08048636      mov     dword [size], edx ; const char *src
0x0804863a      mov     dword [esp], eax ; char *dest
0x0804863d      call    strcpy     ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
0x08048642      lea     eax, [src]
0x08048646      mov     edx, eax
0x08048648      mov     eax, str.reset ; 0x804881f
0x0804864d      mov     ecx, 5
0x08048652      mov     esi, edx
0x08048654      mov     edi, eax
0x08048656      repe    cmpsb byte [esi], byte ptr es:[edi]
0x08048658      seta    dl
0x0804865b      setb    al
0x0804865e      mov     ecx, edx
0x08048660      sub     cl, al
0x08048662      mov     eax, ecx
0x08048664      movsx   eax, al
0x08048667      test    eax, eax
0x08048669      jne     0x8048678
0x0804866b      mov     eax, dword auth ; 0x8049aac
0x08048670      mov     dword [esp], eax ; void *ptr
0x08048673      call    free       ; sym.imp.free ; void free(void *ptr)
0x08048678      lea     eax, [src]
0x0804867c      mov     edx, eax
0x0804867e      mov     eax, str.service ; 0x8048825
0x08048683      mov     ecx, 6
0x08048688      mov     esi, edx
0x0804868a      mov     edi, eax
0x0804868c      repe    cmpsb byte [esi], byte ptr es:[edi]
0x0804868e      seta    dl
0x08048691      setb    al
0x08048694      mov     ecx, edx
0x08048696      sub     cl, al
0x08048698      mov     eax, ecx
0x0804869a      movsx   eax, al
0x0804869d      test    eax, eax
0x0804869f      jne     0x80486b5
0x080486a1      lea     eax, [src]
0x080486a5      add     eax, 7
0x080486a8      mov     dword [esp], eax ; const char *src
0x080486ab      call    strdup     ; sym.imp.strdup ; char *strdup(const char *src)
0x080486b0      mov     dword service, eax ; 0x8049ab0
0x080486b5      lea     eax, [src]
0x080486b9      mov     edx, eax
0x080486bb      mov     eax, str.login ; 0x804882d
0x080486c0      mov     ecx, 5
0x080486c5      mov     esi, edx
0x080486c7      mov     edi, eax
0x080486c9      repe    cmpsb byte [esi], byte ptr es:[edi]
0x080486cb      seta    dl
0x080486ce      setb    al
0x080486d1      mov     ecx, edx
0x080486d3      sub     cl, al
0x080486d5      mov     eax, ecx
0x080486d7      movsx   eax, al
0x080486da      test    eax, eax
0x080486dc      jne     0x8048574
0x080486e2      mov     eax, dword auth ; 0x8049aac
0x080486e7      mov     eax, dword [eax + 0x20]
0x080486ea      test    eax, eax
0x080486ec      je      0x80486ff
0x080486ee      mov     dword [esp], str.bin_sh ; 0x8048833 ; const char *string
0x080486f5      call    system     ; sym.imp.system ; int system(const char *string)
0x080486fa      jmp     0x8048574
0x080486ff      mov     eax, dword stdout ; obj.stdout__GLIBC_2.0
                                   ; 0x8049aa0
                                   0x08048704      mov     edx, eax
0x08048706      mov     eax, str.Password: ; 0x804883b
0x0804870b      mov     dword [stream], edx ; FILE *stream
0x0804870f      mov     dword [nitems], 0xa ; size_t nitems
0x08048717      mov     dword [size], 1 ; size_t size
0x0804871f      mov     dword [esp], eax ; const void *ptr
0x08048722      call    fwrite     ; sym.imp.fwrite ; size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
0x08048727      jmp     0x8048574
0x0804872c      nop
0x0804872d      mov     eax, 0
0x08048732      lea     esp, [var_ch]
0x08048735      pop     esi
0x08048736      pop     edi
0x08048737      pop     ebp
0x08048738      ret
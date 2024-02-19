m();
; var int32_t var_18h @ stack - 0x18
; var time_t var_14h @ stack - 0x14
0x080484f4      push    ebp
0x080484f5      mov     ebp, esp
0x080484f7      sub     esp, 0x18
0x080484fa      mov     dword [esp], 0 ; time_t *timer
0x08048501      call    time       ; sym.imp.time ; time_t time(time_t *timer)
0x08048506      mov     edx, str.s____d ; 0x80486e0
0x0804850b      mov     dword [var_14h], eax
0x0804850f      mov     dword [var_18h], 0x8049960 ; obj.c
0x08048517      mov     dword [esp], edx ; const char *format
0x0804851a      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x0804851f      leave
0x08048520      ret

int main(int argc, char **argv, char **envp);
; var const char *size @ stack - 0x20
; var FILE *stream @ stack - 0x1c
; var void **var_ch @ stack - 0xc
; var void **var_8h @ stack - 0x8
; arg char **envp @ stack + 0x8
0x08048521      push    ebp
0x08048522      mov     ebp, esp
0x08048524      and     esp, 0xfffffff0
0x08048527      sub     esp, 0x20
0x0804852a      mov     dword [esp], 8 ; size_t size
0x08048531      call    malloc     ; sym.imp.malloc ; void *malloc(size_t size)
0x08048536      mov     dword [var_8h], eax
0x0804853a      mov     eax, dword [var_8h]
0x0804853e      mov     dword [eax], 1
0x08048544      mov     dword [esp], 8 ; size_t size
0x0804854b      call    malloc     ; sym.imp.malloc ; void *malloc(size_t size)
0x08048550      mov     edx, eax
0x08048552      mov     eax, dword [var_8h]
0x08048556      mov     dword [eax + 4], edx
0x08048559      mov     dword [esp], 8 ; size_t size
0x08048560      call    malloc     ; sym.imp.malloc ; void *malloc(size_t size)
0x08048565      mov     dword [var_ch], eax
0x08048569      mov     eax, dword [var_ch]
0x0804856d      mov     dword [eax], 2
0x08048573      mov     dword [esp], 8 ; size_t size
0x0804857a      call    malloc     ; sym.imp.malloc ; void *malloc(size_t size)
0x0804857f      mov     edx, eax
0x08048581      mov     eax, dword [var_ch]
0x08048585      mov     dword [eax + 4], edxm();
; var int32_t var_18h @ stack - 0x18
; var time_t var_14h @ stack - 0x14
0x080484f4      push    ebp
0x080484f5      mov     ebp, esp
0x080484f7      sub     esp, 0x18
0x080484fa      mov     dword [esp], 0 ; time_t *timer
0x08048501      call    time       ; sym.imp.time ; time_t time(time_t *timer)
0x08048506      mov     edx, str.s____d ; 0x80486e0
0x0804850b      mov     dword [var_14h], eax
0x0804850f      mov     dword [var_18h], 0x8049960 ; obj.c
0x08048517      mov     dword [esp], edx ; const char *format
0x0804851a      call    printf     ; sym.imp.printf ; int printf(const char *format)
0x0804851f      leave
0x08048520      ret
0x08048596      mov     eax, dword [eax + 4]
0x08048599      mov     dword [size], edx ; const char *src
0x0804859d      mov     dword [esp], eax ; char *dest
0x080485a0      call    strcpy     ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
0x080485a5      mov     eax, dword [envp]
0x080485a8      add     eax, 8
0x080485ab      mov     eax, dword [eax]
0x080485ad      mov     edx, eax
0x080485af      mov     eax, dword [var_ch]
0x080485b3      mov     eax, dword [eax + 4]
0x080485b6      mov     dword [size], edx ; const char *src
0x080485ba      mov     dword [esp], eax ; char *dest
0x080485bd      call    strcpy     ; sym.imp.strcpy ; char *strcpy(char *dest, const char *src)
0x080485c2      mov     edx, data.080486e9 ; 0x80486e9
0x080485c7      mov     eax, str.home_user_level8_.pass ; 0x80486eb
0x080485cc      mov     dword [size], edx ; const char *mode
0x080485d0      mov     dword [esp], eax ; const char *filename
0x080485d3      call    fopen      ; sym.imp.fopen ; FILE *fopen(const char *filename, const char *mode)
0x080485d8      mov     dword [stream], eax ; FILE *stream
0x080485dc      mov     dword [size], 0x44 ; 'D' ; 68 ; int size
0x080485e4      mov     dword [esp], c ; 0x8049960 ; char *s
0x080485eb      call    fgets      ; sym.imp.fgets ; char *fgets(char *s, int size, FILE *stream)
0x080485f0      mov     dword [esp], data.08048703 ; 0x8048703 ; const char *s
0x080485f7      call    puts       ; sym.imp.puts ; int puts(const char *s)
0x080485fc      mov     eax, 0
0x08048601      leave
0x08048602      ret

;-- _GLOBAL_OFFSET_TABLE_:
0x08049908      cmp     al, 0x98   ; 152 ; [22] -rw- section size 48 named .got.plt
0x0804990a      add     al, 8
0x0804990c      add     byte [eax], al
0x0804990e      add     byte [eax], al
0x08049910      add     byte [eax], al
0x08049912      add     byte [eax], al
;-- printf:
0x08049914      .dword 0x080483b6  ; RELOC 32 printf
;-- fgets:
0x08049918      .dword 0x080483c6  ; RELOC 32 fgets
;-- time:
0x0804991c      .dword 0x080483d6  ; RELOC 32 time
;-- strcpy:
0x08049920      .dword 0x080483e6  ; RELOC 32 strcpy
;-- malloc:
0x08049924      .dword 0x080483f6  ; RELOC 32 malloc
;-- puts:
0x08049928      .dword 0x08048406  ; RELOC 32 puts
;-- __gmon_start__:
0x0804992c      .dword 0x08048416  ; RELOC 32 __gmon_start__
;-- __libc_start_main:
0x08049930      .dword 0x08048426  ; RELOC 32 __libc_start_main
;-- fopen:
0x08049934      .dword 0x08048436  ; RELOC 32 fopen
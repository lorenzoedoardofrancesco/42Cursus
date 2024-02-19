int main(int argc, char **argv, char **envp);
; var int32_t var_24h @ stack - 0x24
; var int32_t var_18h @ stack - 0x18
; var int32_t var_14h @ stack - 0x14
; var int32_t var_10h @ stack - 0x10
; var int32_t var_ch @ stack - 0xc
; var int32_t var_8h @ stack - 0x8
; arg char **argv @ stack + 0x4
; arg char **envp @ stack + 0x8
0x080485f4      push    ebp
0x080485f5      mov     ebp, esp
0x080485f7      push    ebx
0x080485f8      and     esp, 0xfffffff0
0x080485fb      sub     esp, 0x20
0x080485fe      cmp     dword [argv], 1
0x08048602      jg      0x8048610
0x08048604      mov     dword [esp], 1 ; int status
0x0804860b      call    _exit      ; sym.imp._exit ; void _exit(int status)
0x08048610      mov     dword [esp], 0x6c ; 'l' ; 108
0x08048617      call    imp.operator new(unsigned int) ; sym.imp.operator_new_unsigned_int
0x0804861c      mov     ebx, eax
0x0804861e      mov     dword [var_24h], 5 ; int32_t arg_8h
0x08048626      mov     dword [esp], ebx ; int32_t arg_4h
0x08048629      call    N::N(int)  ; method.N.N_int ;  method.N.N_int(int32_t arg_4h, int32_t arg_8h)
0x0804862e      mov     dword [var_ch], ebx
0x08048632      mov     dword [esp], 0x6c ; 'l' ; 108
0x08048639      call    imp.operator new(unsigned int) ; sym.imp.operator_new_unsigned_int
0x0804863e      mov     ebx, eax
0x08048640      mov     dword [var_24h], 6 ; int32_t arg_8h
0x08048648      mov     dword [esp], ebx ; int32_t arg_4h
0x0804864b      call    N::N(int)  ; method.N.N_int ;  method.N.N_int(int32_t arg_4h, int32_t arg_8h)
0x08048650      mov     dword [var_10h], ebx
0x08048654      mov     eax, dword [var_ch]
0x08048658      mov     dword [var_14h], eax
0x0804865c      mov     eax, dword [var_10h]
0x08048660      mov     dword [var_18h], eax
0x08048664      mov     eax, dword [envp]
0x08048667      add     eax, 4
0x0804866a      mov     eax, dword [eax]
0x0804866c      mov     dword [var_24h], eax ; int32_t arg_4h
0x08048670      mov     eax, dword [var_14h]
0x08048674      mov     dword [esp], eax ; int32_t arg_8h
0x08048677      call    N::setAnnotation(char*) ; method.N.setAnnotation_char ;  method.N.setAnnotation_char(const char *s, void *s1)
0x0804867c      mov     eax, dword [var_18h]
0x08048680      mov     eax, dword [eax]
0x08048682      mov     edx, dword [eax]
0x08048684      mov     eax, dword [var_14h]
0x08048688      mov     dword [var_24h], eax
0x0804868c      mov     eax, dword [var_18h]
0x08048690      mov     dword [esp], eax
0x08048693      call    edx
0x08048695      mov     ebx, dword [var_8h]
0x08048698      leave
0x08048699      ret
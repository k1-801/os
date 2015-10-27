; OS365 System Call Interface.
; Do not copy.
global int_0x80_handler
extern syscall_handler
int_0x80_handler:
pushad
push eax ; syscall number
; 0 - abort
; 1 - read
; 2 - write
; 3 - get current date element - ebx - 0 - year, 1 - month, 2 - day.
; 4 - get current time element - ebx - 0 - hour, 1 - minute, 2 - second.
popad
iretd

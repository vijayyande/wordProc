     #include <iostream.h>


void main()
{

/*  PUBLIC _displayicon
  {

PROC  _displayicon      */

asm
{
      push bp
      mov bp,sp
      push es
      push di
      push si
      mov ax,0b8000h
      mov es,ax
      mov si,[bp + 4]
      mov al,[bp + 6]
      shr al,l
      mov dl,80
      mul dl
      mov al,[bp + 6]
      test al,l
      jz displayicon0
      or dx,2000h

    displayicon0 :
      shl word ptr [bp + 8],l
      mov ax,[bp +8]
      shr ax,l
      shr ax,l
      shr ax,l
      add ax,dx
      mov di,ax
      mov cx,[bp +8]
      nd cx,7
      ov bx,8
      ub bx,cx
      shl word ptr [bp + 10],l
      mov dx,[bp + 10]
      and word ptr [bp + 6],l

    displayicon1:
      cmp word ptr [bp +12],0
      jz displayiconexit
      dec word ptr [bp + 12]
      push dx
      push di
      mov al,[si]
      shr al,cl
      mov ah,offh
      xchg cx,bx
      shl ah,cl
      xchg cx,bx
      and ah,es:[di]
      or al,ah
      stosb
      sub dx,bx

    displayicon2:
      cmp dx,8
      jl displayicon3
      lodsb
      mov ah,[si]
      xchg al,ah
      shr ax,cl
      stosb
      sub dx,8
      jmp displayicon2

    displayicon3:
      or dx,dx
      jz displayicon3
      lodsb
      mov ah,[si]
      xchg al,ah
      shr ax,cl
      push cx
      mov cx,8
      sub cx,dx
      mov ah,dx
      mov ah,0xffh
      shl ah,cl
      pop cx
      and al,ah
      not ah
      and ah,es:[di]
      or al,ah
      mov es:[di],al

    displayicon4:
       mov ax,[bp + 10]
       push cx
       mov cx,8
       div cl
       pop cx
       cmp ah,0
       jz displayicon5
       cmp cx,6
       jz displayicon6
       inc si
       jmp displayicon6

    displayicon5:
       or cx,cx
       jnz displayicon6
       inc si

    displayicon6:
       pop di
       pop dx
       xor di,2000h
       xor word ptr [bp + 6],l
       jnz displayicon1
       add di,80
       jmp displayicon1

    displayiconexit:
       pop si
       pop di
       pop es
       pop bp

 }
 } /*

       ret
_displayicon ENDP
}      */

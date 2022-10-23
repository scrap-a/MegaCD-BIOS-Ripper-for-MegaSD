#include "genesis.h"

int rip(unsigned char *src, unsigned char *dst, int bank){
    int i;
    for(i=0x00000; i<0x08000; i++){
        dst[i*2+0] = src[i+0x08000*bank];
        dst[i*2+1] = src[i+0x08000*bank];
    }
    
    return 0;
}

int main(bool hardReset)
{
    unsigned char *src, *dst;
    int bank=0;     //bank select [0-3]
    u16 *hint_register;
    
    VDP_drawText("Mega-CD BIOS ripping program", 6, 2);
    
    src = (unsigned char *)0x00400000;
    dst = (unsigned char *)0x00200000;
    hint_register = (u16 *)0x00A12006;
    
    *hint_register = (u16)0xFD0C;        //reset H-INT register to BIOS original value
    
    rip(src,dst,bank);
    
    VDP_drawText("Ripping finished", 13, 15);
    
    while(TRUE)
    {
        SYS_doVBlankProcess();
    }

    return 0;
}

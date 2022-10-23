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
    int select=0;
    unsigned char *src, *dst;
    int bank=0;     //bank select [0-3]
    u8 value, pre_value;
    
    VDP_drawText("Mega-CD BIOS ripping program", 6, 2);
    
    src = (unsigned char *)0x00400000;
    dst = (unsigned char *)0x00200000;
    
    if(bank==0){
        VDP_drawText("BIOS ripping(raw)", 5, 9);
        VDP_drawText("BIOS ripping(overlapped HINT)", 5, 10);
        
        while(TRUE){
            if(select==0){
                VDP_drawText("->", 3,  9);
                VDP_drawText("  ", 3, 10);
            }else{
                VDP_drawText("  ", 3,  9);
                VDP_drawText("->", 3, 10);
            }
            
            value = JOY_readJoypad(JOY_1);
            
            if( value& BUTTON_A || value& BUTTON_C || value& BUTTON_START){
                rip(src,dst,bank);
                if(select !=0){
                    dst[0x72*2+0] = 0xFD;
                    dst[0x72*2+1] = 0xFD;
                    dst[0x73*2+0] = 0x0C;
                    dst[0x73*2+1] = 0x0C;
                }
                
                break;
            }
            if( (value& BUTTON_UP) & ~(pre_value & BUTTON_UP) || (value& BUTTON_DOWN) & ~(pre_value& BUTTON_DOWN)){
                select ^= 1;
            }
            
            pre_value = value;
            
            SYS_doVBlankProcess();
        }
    }else{
        rip(src,dst,bank);
    }
    
    VDP_drawText("Ripping finished", 13, 15);
    
    while(TRUE)
    {
        SYS_doVBlankProcess();
    }

    return 0;
}

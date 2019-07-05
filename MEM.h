//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_MEM_H
#define RISCV_MEM_H

#include"init.h"

namespace MEM {
    unsigned int ext(int pos,int len,int tag)
    {
        unsigned int val=0,base=0;
        for(int i=len;i;i-=8)
        {
            val+=st[pos]<<(base<<3);
            ++base;
            pos++;
        }
        if(!tag)return val;
        if(val&(1<<(len-1)))
            val|=fw1(31,len-1);
        return val;
    }
    void savedata(int pos,int val,int len)
    {
        unsigned int base = (1<<8)-1;
        int cnt=0;
        for(int i=0;i<len>>3;i++)
        {
//			printf("\n\n%d\n\n",(val&base)>>(cnt<<3));
            st[pos+i]=(val&base);
            val>>=8;
        }
    }
    void pro() {
        s[4].cl();
        if(!s[3].exist)return;
        unsigned int rs1=s[3].rs1,rs2=s[3].rs2,rd=s[3].rd;
        unsigned int im=s[3].im,exim=s[3].exim;
        unsigned int funct7=s[3].funct7,funct3=s[3].funct3,opcode=s[3].opcode;
        if(opcode==0x3)
        {
            switch(funct3)
            {
                case 0:
                    s[3].ans=ext(s[3].rs1,8,1);
                    break;
                case 1:
                    s[3].ans=ext(s[3].rs1,16,1);
                    break;
                case 2:
                    s[3].ans=ext(s[3].rs1,32,1);
                    break;
                case 4:
                    s[3].ans=ext(s[3].rs1,8,0);
                    break;
                case 5:
                    s[3].ans=ext(s[3].rs1,16,0);
                    break;
                default:
                    break;
            }
        }// dark red part;
        if(opcode==0x23)
        {
            switch(funct3)
            {
                case 0:
                    savedata(s[3].rd,s[3].ans,8);
                    break;
                case 1:
                    savedata(s[3].rd,s[3].ans,16);
                    break;
                case 2:
                    savedata(s[3].rd,s[3].ans,32);
                    break;
                default:
                    break;
            }
        }//light red part;
        if(opcode==0x63)
        {
            if(s[3].npc!=pc)
                pc=s[3].npc,jump=1;
        }
        if(opcode==0x6f)
        {
            if(s[3].npc!=pc)
                pc=s[3].npc,jump=1;
        }
        if(opcode==0x67)
        {
            if(s[3].npc!=pc)
                pc=s[3].npc,jump=1;
        }
        s[4]=s[3];
    }
}

#endif //RISCV_MEM_H

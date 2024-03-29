//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_MEM_H
#define RISCV_MEM_H

#include"init.h"
#include"WB.h"
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
        if(cnt4!=0)
        {
            cnt4--;
            return;
        }
        if(s[4].exist)return;
        if(!s[3].exist)return;
        if(jump)return;
        if (s[3].exe == fintag){
            s[4]=s[3];
            s[3].cl();
            return;
        }
        cnt4=3;
        unsigned int rs1=s[3].rs1,rs2=s[3].rs2,rd=s[3].rd;
        unsigned int im=s[3].im,exim=s[3].exim;
        unsigned int funct7=s[3].funct7,funct3=s[3].funct3,opcode=s[3].opcode;
        int npc=s[3].pc;
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
        if(opcode==0x63) {
            if (s[3].jumptag == 1 && s[3].jumpacqui == 0)
                pc = s[3].npc, jump = 1;
            if (s[3].jumptag == 0 && s[3].jumpacqui == 1)
                pc = s[3].pc + 4, jump = 1;
            if (s[3].jumptag) {
                if(tag[s[3].pc]!=3)
                    tag[s[3].pc]++;
            }
            if (!s[3].jumptag) {
                if(tag[s[3].pc]!=0)
                    tag[s[3].pc]--;
            }
        }
        if(opcode==0x6f||opcode==0x67)
        {
            pc = s[3].npc, jump = 1;
        }
        s[4]=s[3];
        s[3].cl();
        if(opcode==0x6f||opcode==0x67){
            WB::pro(1);
        }
    }
}

#endif //RISCV_MEM_H

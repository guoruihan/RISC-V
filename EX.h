//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_EX_H
#define RISCV_EX_H

#include"init.h"

namespace EX{
    void pro()
    {
        if(s[3].exist)return;
        if(!s[2].exist) return;
        if(jump)return;
        if (s[2].exe == fintag){
            s[3]=s[2];
            s[2].cl();
            return;
        }
        unsigned int rs1=s[2].rs1,rs2=s[2].rs2,rd=s[2].rd;
        unsigned int im=s[2].im,exim=s[2].exim;
        unsigned int funct7=s[2].funct7,funct3=s[2].funct3,opcode=s[2].opcode;
        unsigned int pc=s[2].pc;
        if(opcode==0x33)
        {
            beused1[rd]++;
            switch(funct3)
            {
                case 0:
                    if(!funct7)
                        s[2].ans=x[rs1]+x[rs2];
                    else
                        s[2].ans=x[rs1]-x[rs2];
                    break;
                case 1:
                    s[2].ans=x[rs1]<<(x[rs2]&31);
                    break;
                case 2:
                    s[2].ans=((int)x[rs1]<(int)x[rs2]);
                    break;
                case 3:
                    s[2].ans=(x[rs1]<x[rs2]);
                    break;
                case 4:
                    s[2].ans=x[rs1]^x[rs2];
                    break;
                case 5:
                    if(!funct7)
                        s[2].ans=x[rs1]>>(x[rs2]&31);
                    else
                    {
                        int tag=x[rs1]&(1<<31);
                        s[2].ans=x[rs1]>>(x[rs2]&31);
                        if(tag)
                            s[2].ans|=fw1(31,31-(x[rs2]&31));
                    }
                    break;
                case 6:
                    s[2].ans=x[rs1]|x[rs2];
                    break;
                case 7:
                    s[2].ans=x[rs1]&x[rs2];
                    break;
                default:
                    break;
            }
    } // green part;
        if(opcode==0x13)
        {
            beused1[rd]++;
            switch(funct3)
            {
                case 0:
                    s[2].ans=x[rs1]+exim;
                    break;
                case 1:
                    s[2].ans=x[rs1]<<rs2;
                    break;
                case 2:
                    s[2].ans=(int)x[rs1]<(int)exim;
                    break;
                case 3:
                    s[2].ans=x[rs1]<exim;
                    break;
                case 4:
                    s[2].ans=x[rs1]^exim;
                    break;
                case 5:
                    if(!funct7)
                    {
                        s[2].ans=x[rs1]>>rs2;
                    }
                    else
                    {
                        int tag=x[rs1]&(1<<31);
                        s[2].ans=x[rs1]>>rs2;
                        if(tag)
                            s[2].ans|=fw1(31,31-(x[rs2]&31));
                    }
                    break;
                case 6:
                    s[2].ans=x[rs1]|exim;
                    break;
                case 7:
                    s[2].ans=x[rs1]&exim;
                    break;
                default:
                    break;
            }
        } // yellow part;
        if(opcode==0x3)
        {
            beused1[rd]++;
            s[2].rs1=x[rs1]+exim;
        }// dark red part;
        if(opcode==0x23)
        {
            s[2].rd=x[rs1]+exim;
            s[2].ans=x[rs2];
        }//light red part;
        if(opcode==0x63)
        {
            switch(funct3)
            {
                case 0:
                    if(x[rs1]==x[rs2])
                        s[2].npc=pc+exim,s[2].jumptag=1;
                    break;
                case 1:
                    if(x[rs1]!=x[rs2])
                        s[2].npc=pc+exim,s[2].jumptag=1;
                    break;
                case 4:
                    if((int)x[rs1]<(int)x[rs2])
                        s[2].npc=pc+exim,s[2].jumptag=1;
                    break;
                case 5:
                    if((int)x[rs1]>=(int)x[rs2])
                        s[2].npc=pc+exim,s[2].jumptag=1;
                    break;
                case 6:
                    if(x[rs1]<x[rs2])
                        s[2].npc=pc+exim,s[2].jumptag=1;
                    break;
                case 7:
                    if(x[rs1]>=x[rs2])
                        s[2].npc=pc+exim,s[2].jumptag=1;
                    break;
                default:
                    break;
            }
        }// blue part;
        if(opcode==0x37)
        {
            beused1[rd]++;
            s[2].ans=exim<<12;
        }
        if(opcode==0x17)
        {
            beused1[rd]++;
            s[2].ans=(exim<<12)+pc;
        }
        if(opcode==0x6f)
        {
            beused1[rd]++;
            s[2].ans=pc+4;
            s[2].npc=pc+exim;
        }
        if(opcode==0x67)
        {
            beused1[rd]++;
            s[2].ans=pc+4;
            s[2].npc=x[rs1]+exim;
        }
        s[3]=s[2];
        s[2].cl();
    }
}

#endif //RISCV_EX_H

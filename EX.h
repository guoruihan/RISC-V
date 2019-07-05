//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_EX_H
#define RISCV_EX_H

#include"init.h"

namespace EX{
    void pro()
    {
        s[3].cl();
        if(!s[2].exist) return;
        unsigned int rs1=s[2].rs1,rs2=s[2].rs2,rd=s[2].rd;
        unsigned int im=s[2].im,exim=s[2].exim;
        unsigned int funct7=s[2].funct7,funct3=s[2].funct3,opcode=s[2].opcode;
        if(opcode==0x33)
        {
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
            switch(funct3)
            {
                case 0:
                    s[2].rs1=x[rs1]+exim;
                    break;
                case 1:
                    s[2].rs1=x[rs1]+exim;
                    break;
                case 2:
                    s[2].rs1=x[rs1]+exim;
                    break;
                case 4:
                    s[2].rs1=x[rs1]+exim;
                    break;
                case 5:
                    s[2].rs1=x[rs1]+exim;
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
                    s[2].rd=x[rs1]+exim;
                    s[2].ans=x[rs2];
                    break;
                case 1:
                    s[2].rd=x[rs1]+exim;
                    s[2].ans=x[rs2];
                    break;
                case 2:
                    s[2].rd=x[rs1]+exim;
                    s[2].ans=x[rs2];
                    break;
                default:
                    break;
            }
        }//light red part;
        if(opcode==0x63)
        {
            switch(funct3)
            {
                case 0:
                    if(x[rs1]==x[rs2])
                        s[2].npc=pc+exim-4;
                    else
                        s[2].npc=pc;
                    break;
                case 1:
                    if(x[rs1]!=x[rs2])
                        s[2].npc=pc+exim-4;
                    else
                        s[2].npc=pc;
                    break;
                case 4:
                    if((int)x[rs1]<(int)x[rs2])
                        s[2].npc=pc+exim-4;
                    else
                        s[2].npc=pc;
                    break;
                case 5:
                    if((int)x[rs1]>=(int)x[rs2])
                        s[2].npc=pc+exim-4;
                    else
                        s[2].npc=pc;
                    break;
                case 6:
                    if(x[rs1]<x[rs2])
                        s[2].npc=pc+exim-4;
                    else
                        s[2].npc=pc;
                    break;
                case 7:
                    if(x[rs1]>=x[rs2])
                        s[2].npc=pc+exim-4;
                    else
                        s[2].npc=pc;
                    break;
                default:
                    break;
            }
        }// blue part;
        if(opcode==0x37)
        {
            s[2].ans=exim<<12;
        }
        if(opcode==0x17)
        {
            s[2].ans=(exim<<12)+pc-4;
        }
        if(opcode==0x6f)
        {
            s[2].ans=pc;
            s[2].npc=pc+exim-4;
        }
        if(opcode==0x67)
        {
            s[2].ans=pc;
            s[2].npc=x[rs1]+exim;
        }
        s[3]=s[2];
    }
}

#endif //RISCV_EX_H

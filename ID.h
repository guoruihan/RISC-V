//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_ID_H
#define RISCV_ID_H
#include"init.h"
namespace ID{
    unsigned int getval_D(unsigned int &val,int p1,int p2)//p1 is greater than p2
    {
        unsigned int base=((1<<(p1-p2+1))-1)<<p2;
        return (val&base)>>p2;
    }
    void makeex(int pos,int len)
    {
        s[pos].exim=s[pos].im;
        if((s[pos].im&(1<<(len-1)))!=0)
            s[pos].exim+=((1<<(32-len))-1)<<len;
    }
    void calc(int pos,unsigned int val)
    {
        s[pos].opcode=getval_D(val,6,0);
        s[pos].funct3=getval_D(val,14,12);
        s[pos].funct7=getval_D(val,31,25);
        s[pos].rd=getval_D(val,11,7);
        s[pos].rs2=getval_D(val,24,20);
        s[pos].rs1=getval_D(val,19,15);

        if(s[pos].opcode==19||
           s[pos].opcode==3||
           s[pos].opcode==103)
        {
            s[pos].im=getval_D(val,31,20);
            makeex(pos,12);
        } else
        if(s[pos].opcode==35)
        {
            s[pos].im=
                    (getval_D(val,31,25)<<5)+
                    (getval_D(val,11,7));
            makeex(pos,12);
        } else
        if(s[pos].opcode==99)
        {
            s[pos].im=
                    (getval_D(val,31,31)<<11)+
                    (getval_D(val,7,7)<<10)+
                    (getval_D(val,30,25)<<4)+
                    (getval_D(val,11,8));
            makeex(pos,12);
            s[pos].im<<=1;
            s[pos].exim<<=1;
        } else
        if(s[pos].opcode==111)
        {
            s[pos].im=
                    (getval_D(val,31,31)<<19)+
                    (getval_D(val,19,12)<<11)+
                    (getval_D(val,20,20)<<10)+
                    (getval_D(val,30,21));
            makeex(pos,20);
            s[pos].im<<=1;
            s[pos].exim<<=1;
        }
        else
        {
            s[pos].im=
                    getval_D(val,31,12);
            makeex(pos,20);
        }
    }
    void pro()
    {
        s[2].cl();
        if(!s[1].exist) return;
        calc(2,s[1].exe);
        s[2].exist=1;
 //s[2].prt();
}
}
#endif //RISCV_ID_H

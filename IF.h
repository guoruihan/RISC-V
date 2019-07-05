//
// Created by Administrator on 2019/7/4.
//


#ifndef RISCV_IF_H
#define RISCV_IF_H

#include"init.h"
namespace IF {
    unsigned int ext(int pos)
    {
        int len=32;
        unsigned int val=0,base=0;
        for(int i=len;i;i-=8)
        {
            val+=st[pos]<<(base<<3);
            ++base;
            pos++;
        }
        return val;
    }
    void pro() {
        s[1].cl();
        s[1].exe = ext(pc);
        s[1].exist = 1;
        pc += 4;
        if (jump) {
            jump=0;
            for(int i=2;i<=4;i++)
                s[i].exist=0;
        }
    }
}


#endif //RISCV_IF_H

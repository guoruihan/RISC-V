//
// Created by Administrator on 2019/7/4.
//


#ifndef RISCV_IF_H
#define RISCV_IF_H

#include"init.h"
namespace IF {
    unsigned int ext(int pos) {
        int len = 32;
        unsigned int val = 0, base = 0;
        for (int i = len; i; i -= 8) {
            val += st[pos] << (base << 3);
            ++base;
            pos++;
        }
        return val;
    }

    void clbeused() {
        int opcode;
        if(s[3].exist){
            opcode=s[3].opcode;
            if(opcode==0x23) {
                beused2[s[3].rd]--;
            }
            if(opcode!=0x23&&opcode!=0x63){
                beused1[s[3].rd]--;
            }
        }
    }
    void pro() {
        if (jump) {
            jump=0;
            clbeused();
            for(int i=1;i<=3;i++)
                s[i].exist=0;
        }
        if(s[1].exist)return;
        s[1].exe = ext(pc);
        s[1].exist = 1;
        s[1].pc=pc;
        pc += 4;
    }
}


#endif //RISCV_IF_H

//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_WB_H
#define RISCV_WB_H

#include"init.h"

namespace WB{
    void pro(){
        int opcode=s[4].opcode;
        if(!s[4].exist)return;
        if(opcode==0x23) return;
        if(opcode==0x63) return;
        x[s[4].rd]=s[4].ans;
    }
}

#endif //RISCV_WB_H

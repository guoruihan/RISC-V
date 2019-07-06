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
        if(jump==2)jump--;
        if (s[4].exe == fintag){
            s[4].cl();
            return;
        }
        if(opcode==0x23){
            s[4].cl();
            return;
        }
        if(opcode==0x63){
            s[4].cl();
            return;
        }
        x[s[4].rd]=s[4].ans;
        beused1[s[4].rd]--;
        s[4].cl();
    }
}

#endif //RISCV_WB_H

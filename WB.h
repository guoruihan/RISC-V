//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_WB_H
#define RISCV_WB_H

#include"init.h"

namespace WB{
    void pro(){
        if(!s[4].exist)return;
        x[s[4].rd]=s[4].ans;
    }
}

#endif //RISCV_WB_H

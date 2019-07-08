//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_ID_H
#define RISCV_ID_H
#include"init.h"
namespace ID {
    unsigned int getval_D(unsigned int &val, int p1, int p2)//p1 is greater than p2
    {
        unsigned int base = ((1 << (p1 - p2 + 1)) - 1) << p2;
        return (val & base) >> p2;
    }

    void makeex(int pos, int len) {
        s[pos].exim = s[pos].im;
        if ((s[pos].im & (1 << (len - 1))) != 0)
            s[pos].exim += ((1 << (32 - len)) - 1) << len;
    }

    void calc(int pos, unsigned int val) {
        s[pos].opcode = getval_D(val, 6, 0);
        s[pos].funct3 = getval_D(val, 14, 12);
        s[pos].funct7 = getval_D(val, 31, 25);
        s[pos].rd = getval_D(val, 11, 7);
        s[pos].rs2 = getval_D(val, 24, 20);
        s[pos].rs1 = getval_D(val, 19, 15);

        if (s[pos].opcode == 19 ||
            s[pos].opcode == 3 ||
            s[pos].opcode == 103) {
            s[pos].im = getval_D(val, 31, 20);
            makeex(pos, 12);
        } else if (s[pos].opcode == 35) {
            s[pos].im =
                    (getval_D(val, 31, 25) << 5) +
                    (getval_D(val, 11, 7));
            makeex(pos, 12);
        } else if (s[pos].opcode == 99) {
            s[pos].im =
                    (getval_D(val, 31, 31) << 11) +
                    (getval_D(val, 7, 7) << 10) +
                    (getval_D(val, 30, 25) << 4) +
                    (getval_D(val, 11, 8));
            makeex(pos, 12);
            s[pos].im <<= 1;
            s[pos].exim <<= 1;
        } else if (s[pos].opcode == 111) {
            s[pos].im =
                    (getval_D(val, 31, 31) << 19) +
                    (getval_D(val, 19, 12) << 11) +
                    (getval_D(val, 20, 20) << 10) +
                    (getval_D(val, 30, 21));
            makeex(pos, 20);
            s[pos].im <<= 1;
            s[pos].exim <<= 1;
        } else {
            s[pos].im =
                    getval_D(val, 31, 12);
            makeex(pos, 20);
        }
    }

    bool chk() {
        unsigned int rs1 = s[1].rs1, rs2 = s[1].rs2, rd = s[1].rd;
        unsigned int im = s[1].im, exim = s[1].exim;
        unsigned int funct7 = s[1].funct7, funct3 = s[1].funct3, opcode = s[1].opcode;
        if (opcode == 0x33) {
            if (beused1[rs1] || beused1[rs2])
                return 1;
        } // green part;
        if (opcode == 0x13) {
            if (beused1[rs1])
                return 1;
        } // yellow part;
        if (opcode == 0x3) {
     //       printf("%d guagua",x[rs1] + exim);
            if(beused1[rs1])
                return 1;
            if (beused2[x[rs1] + exim])
                return 1;
        }// dark red part;
        if (opcode == 0x23) {
            if (beused1[rs1]||beused1[rs2])
                return 1;
        }//light red part;
        if (opcode == 0x63) {
            if (beused1[rs1] || beused1[rs2])
                return 1;
        }// blue part;
        if (opcode == 0x67) {
            if (beused1[rs1])
                return 1;
        }
        return 0;
    }
    void pro() {
        if (s[2].exist)return;
        if (!s[1].exist) return;
        if(jump)return;
        if(mayjump)return;
        if (s[1].exe == fintag){
            s[2]=s[1];
            s[1].cl();
            return;
        }
        calc(1,s[1].exe);
        if(chk())//1:hazard 0 no hazard
            return;
        if(s[1].opcode==0x67||s[1].opcode==0x6f||s[1].opcode==0x63)
            mayjump++;
        s[2]=s[1];
        s[1].cl();
        if(s[2].opcode==0x63)
            s[2].jumpacqui=0;
     //s[2].prt();
    }
}
#endif //RISCV_ID_H

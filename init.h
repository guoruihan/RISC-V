//
// Created by Administrator on 2019/7/4.
//

#ifndef RISCV_INIT_H
#define RISCV_INIT_H
int jump;
int mayjump;
int beused1[35];
void prt_H(unsigned int val)
{
    bool tag=0;
    for(unsigned int B=(1<<28);B;B>>=4)
    {
        if(val>=B)
        {
            tag=1;
            int nv=val/B;val%=B;
            if(nv<=9)printf("%d",nv);
            else printf("%c",nv+'a'-10);
        }
        else
        {
            if(tag)
                printf("0");
        }
    }
    if(!tag)printf("0");
    printf(" ");
}
struct RE {
    unsigned int rs1,rs2,exim,im;
    unsigned int ans;
    unsigned int exe;
    int rd;
    unsigned int funct7,funct3,opcode;
    bool exist;
    bool jumptag;
    bool jumpacqui;
    unsigned int npc;
    int pc;
    void cl() {
        jumpacqui=jumptag=im=exim=pc=exist=npc=rs1=rs2=funct7=funct3=opcode=ans=exe=rd=0;
    }
    void prt()
    {
        prt_H(rs1);
        prt_H(rs2);
        prt_H(rd);
        prt_H(im);
        prt_H(exim);
        prt_H(funct7);
        prt_H(funct3);
        prt_H(opcode);
        prt_H(exe);
        printf("%d %d %d %d ",exist,pc,ans,npc);
        printf("\n");
    }
}s[15],stmp;
unsigned int x[33],pc;
const unsigned int fintag = 13009443;
unsigned int fw1(int p1,int p2)
{
    return ((1<<(p1-p2+1))-1)<<p2;
}
unsigned int st[400005];
namespace Init{
    char str[105];
    unsigned int getval_H(char c)
    {
        if(c>='0'&&c<='9')
            return c-'0';
        if(c>='a'&&c<='f')
            return c-'a'+10;
        return c-'A'+10;
    }
    unsigned int trans_HD(char *str)
    {
        int l=(int)strlen(str);
        unsigned int nv=0;
        for(int i=0;i<l;i++)
        {
            nv=(nv<<4)+getval_H(str[i]);
        }
        return nv;
    }
    void pro()
    {
        mayjump=0;
        memset(beused1,0,sizeof(beused1));
        for(int i=0;i<200000;i++)
            st[i]=0;
        int np=0;
        while(scanf("%s",str)!=EOF)
        {
            if(str[0]=='@')
            {
                np = trans_HD(str+1);
            }
            else
            {
                unsigned int val=trans_HD(str),base=1;
                st[np]=(val&((1<<8)-1));
                for(int i=1;i<=3;i++)
                {
                    scanf("%s",str);
                    base<<=8;
                    val += trans_HD(str)*base;
                    st[np+i]=(trans_HD(str)&((1<<8)-1));
                }
                //			prt_H(np),prt_H(val);s[np].prt();
                np+=4;
            }
        }
    }
}

#endif //RISCV_INIT_H

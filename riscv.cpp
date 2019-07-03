#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
unsigned int x[32],pc;
const unsigned int fintag = 13009443;
// when val equal fintag, print x[10] and finish
unsigned int fw1(int p1,int p2)
{
	return ((1<<(p1-p2+1))-1)<<p2;
}
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
struct Exe{
	unsigned int val;
	unsigned int rs1,rs2,rd;
	unsigned int im,exim;
	unsigned int funct7,funct3,opcode;
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
		printf("\n");
	}
}s[200005];
unsigned int st[200005];
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
	unsigned int getval_D(unsigned int &val,int p1,int p2)//p1 is greater than p2
	{
		unsigned int base=((1<<(p1-p2+1))-1)<<p2;
		return (val&base)>>p2;
	}
	void makeex(int pos,int len)
	{
		if(len==12)
		{
			s[pos].exim=s[pos].im;
			if((s[pos].im&(1<<11))!=0)
				s[pos].exim+=((1<<20)-1)<<12;
		}
		else
		{
			s[pos].exim=s[pos].im;
			if((s[pos].im&(1<<19))!=0)
				s[pos].exim+=((1<<12)-1)<<20;
		}
	}
	void calc(int pos,unsigned int val)
	{
		s[pos].val=val;
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
				calc(np,val);
	//			prt_H(np),prt_H(val);s[np].prt();
				np+=4;
			}
		}
	}
}
namespace Simu{
	void init()
	{	
		for(int i=0;i<32;i++)x[i]=0;
		pc=0;
	}
	unsigned int ext(int pos,int len,int tag)
	{
		unsigned int val=0,base=0;
		for(int i=len;i;i-=8)
		{
			val+=st[pos]<<(base<<3);
			++base;
			pos++;
		}
		if(!tag)return val;
		if(val&(1<<(len-1)))
			val|=fw1(31,len-1);
		return val;
	}
	void savedata(int pos,int val,int len)
	{
		unsigned int base = (1<<8)-1;
		int cnt=0;
		for(int i=0;i<len>>3;i++)
		{
//			printf("\n\n%d\n\n",(val&base)>>(cnt<<3));
			st[pos+i]=(val&base);
			val>>=8;
		}
	}
	void debug()
	{
		unsigned int rs1=s[pc].rs1,rs2=s[pc].rs2,rd=s[pc].rd;
		unsigned int im=s[pc].im,exim=s[pc].exim;
		unsigned int funct7=s[pc].funct7,funct3=s[pc].funct3,opcode=s[pc].opcode;
		if(opcode==0x33)
		{
			switch(funct3)
			{
				case 0:
					if(!funct7)
						printf("ADD %d %d %d\n",rs1,rs2,rd);
					else
						printf("SUB %d %d %d\n",rs1,rs2,rd);					
					break;
				case 1:
					printf("SLL %d %d\n",rs1,rs2);
					break;
				case 2:
					printf("SLT %d %d %d\n",rs1,rs2,rd);
					break;
				case 3:
					printf("SLTU %d %d %d\n",rs1,rs2,rd);
					break;
				case 4:
					printf("XOR %d %d %d\n",rs1,rs2,rd);
					break;
				case 5:
					if(!funct7)
						printf("SRL %d %d %d\n",rs1,rs2,rd);
					else
						printf("SLA %d %d %d\n",rs1,rs2,rd);
					break;
				case 6:
					printf("OR %d %d %d\n",rs1,rs2,rd);
					break;
				case 7:
					printf("AND %d %d %d\n",rs1,rs2,rd);
					break;
				default:
					break;
			}
			return;
		} // green part;
		if(opcode==0x13)
		{
			switch(funct3)
			{
				case 0:
					printf("ADDI %d %d %d\n",rs1,(int)exim,rd);
					break;
				case 1:
					printf("SLLI %d %d %d\n",rs1,rs2,rd);
					break;
				case 2:
					printf("SLTI %d %d %d\n",rs1,(int)exim,rd);
					break;
				case 3:
					printf("SLTIU %d %d %d\n",rs1,(int)exim,rd);
					break;
				case 4:
					printf("XORI %d %d %d\n",rs1,(int)exim,rd);
					break;
				case 5:
					if(!funct7)
						printf("SRLI %d %d %d\n",rs1,rs2,rd);
					else
						printf("SRAI %d %d %d\n",rs1,rs2,rd);
					break;
				case 6:
					printf("ORI %d %d %d\n",rs1,(int)exim,rd);
					break;
				case 7:
					printf("ANDI %d %d %d\n",rs1,(int)exim,rd);
					break;
				default:
					break;
			}
			return;
		} // yellow part;		
		if(opcode==0x3)
		{
			switch(funct3)
			{
				case 0:
					printf("LB %d %d %d ra %d\n",rs1,exim,rd,x[rs1]+exim);
					break;
				case 1:
					printf("LH %d %d %d ra %d\n",rs1,exim,rd,x[rs1]+exim);
					break;
				case 2:
					printf("LW %d %d %d ra %d\n",rs1,exim,rd,x[rs1]+exim);
					break;
				case 4:
					printf("LBU %d %d %d ra %d\n",rs1,exim,rd,x[rs1]+exim);
					break;
				case 5:
					printf("LHU %d %d %d ra %d\n",rs1,exim,rd,x[rs1]+exim);
					break;
				default:
					break;
			}
			return;
		}// dark red part;
		if(opcode==0x23)
		{
			switch(funct3)
			{
				case 0:
					printf("SB %d %d %d wa %d\n",rs1,exim,rs2,x[rs1]+exim);
					break;
				case 1:
					printf("SH %d %d %d wa %d\n",rs1,exim,rs2,x[rs1]+exim);
					break;
				case 2:
					printf("SW %d %d %d wa %d\n",rs1,exim,rs2,x[rs1]+exim);
					break;
				default:
					break;
			}
			return;
		}//light red part;
		if(opcode==0x63)
		{
			switch(funct3)
			{
				case 0:
					printf("BEQ %d %d %d\n",rs1,rs2,exim);
					break;
				case 1:
					printf("BNE %d %d %d\n",rs1,rs2,exim);
					break;
				case 4:
					printf("BLT %d %d %d\n",rs1,rs2,exim);
					break;
				case 5:
					printf("BGE %d %d %d\n",rs1,rs2,exim);
					break;
				case 6:
					printf("BLTU %d %d %d\n",rs1,rs2,exim);
					break;
				case 7:
					printf("BGEU %d %d %d\n",rs1,rs2,exim);
					break;
				default:
					break;
			}
			return;
		}// blue part;
		if(opcode==0x37)
		{
			printf("LUI %d %d\n",exim,rd);
			return;
		}
		if(opcode==0x17)
		{
			printf("AUIPC %d %d\n",exim,rd);
			return;
		}
		if(opcode==0x6f)
		{
			printf("JAL %d %d\n",exim,rd);
			return;
		}		
		if(opcode==0x67)
		{	
			printf("JALR %d %d %d\n",rs1,exim,rd);
			return;
		}
	}
	void nextstep()
	{
		unsigned int rs1=s[pc].rs1,rs2=s[pc].rs2,rd=s[pc].rd;
		unsigned int im=s[pc].im,exim=s[pc].exim;
		unsigned int funct7=s[pc].funct7,funct3=s[pc].funct3,opcode=s[pc].opcode;
		if(opcode==0x33)
		{
			switch(funct3)
			{
				case 0:
					if(!funct7)
						x[rd]=x[rs1]+x[rs2];
					else
						x[rd]=x[rs1]-x[rs2];
					break;
				case 1:
					x[rd]=x[rs1]<<(x[rs2]&31);
					break;
				case 2:
					x[rd]=((int)x[rs1]<(int)x[rs2]);
					break;
				case 3:
					x[rd]=(x[rs1]<x[rs2]);
					break;
				case 4:
					x[rd]=x[rs1]^x[rs2];
					break;
				case 5:
					if(!funct7)
						x[rd]=x[rs1]>>(x[rs2]&31);
					else
					{
						int tag=x[rs1]&(1<<31);
						x[rd]=x[rs1]>>(x[rs2]&31);
						if(tag)
							x[rd]|=fw1(31,31-(x[rs2]&31));
					}
					break;
				case 6:
					x[rd]=x[rs1]|x[rs2];
					break;
				case 7:
					x[rd]=x[rs1]&x[rs2];
					break;
				default:
					break;
			}
			pc+=4;
			return;
		} // green part;
		if(opcode==0x13)
		{
			switch(funct3)
			{
				case 0:
					x[rd]=x[rs1]+exim;
					break;
				case 1:
					x[rd]=x[rs1]<<rs2;
					break;
				case 2:
					x[rd]=(int)x[rs1]<(int)exim;
					break;
				case 3:
					x[rd]=x[rs1]<exim;
					break;
				case 4:
					x[rd]=x[rs1]^exim;
					break;
				case 5:
					if(!funct7)
					{
						x[rd]=x[rs1]>>rs2;
					}
					else
					{
						int tag=x[rs1]&(1<<31);
						x[rd]=x[rs1]>>rs2;
						if(tag)
							x[rd]|=fw1(31,31-(x[rs2]&31));
					}
					break;
				case 6:
					x[rd]=x[rs1]|exim;
					break;
				case 7:
					x[rd]=x[rs1]&exim;
					break;
				default:
					break;
			}
			pc+=4;
			return;
		} // yellow part;		
		if(opcode==0x3)
		{
			switch(funct3)
			{
				case 0:
					x[rd]=ext(x[rs1]+exim,8,1);
					break;
				case 1:
					x[rd]=ext(x[rs1]+exim,16,1);
					break;
				case 2:
					x[rd]=ext(x[rs1]+exim,32,1);
					break;
				case 4:
					x[rd]=ext(x[rs1]+exim,8,0);
					break;
				case 5:
					x[rd]=ext(x[rs1]+exim,16,0);
					break;
				default:
					break;
			}
			pc+=4;
			return;
		}// dark red part;
		if(opcode==0x23)
		{
			switch(funct3)
			{
				case 0:
					savedata(x[rs1]+exim,x[rs2],8);
					break;
				case 1:
					savedata(x[rs1]+exim,x[rs2],16);
					break;
				case 2:
					savedata(x[rs1]+exim,x[rs2],32);
					break;
				default:
					break;
			}
			pc+=4;
			return;
		}//light red part;
		if(opcode==0x63)
		{
			switch(funct3)
			{
				case 0:
					if(x[rs1]==x[rs2])
						pc+=exim;
					else
						pc+=4;
					break;
				case 1:
					if(x[rs1]!=x[rs2])
						pc+=exim;
					else
						pc+=4;
					break;
				case 4:
					if((int)x[rs1]<(int)x[rs2])
						pc+=exim;
					else
						pc+=4;
					break;
				case 5:
					if((int)x[rs1]>=(int)x[rs2])
						pc+=exim;
					else
						pc+=4;
					break;
				case 6:
					if(x[rs1]<x[rs2])
						pc+=exim;
					else
						pc+=4;
					break;
				case 7:
					if(x[rs1]>=x[rs2])
						pc+=exim;
					else
						pc+=4;
					break;
				default:
					break;
			}
			return;
		}// blue part;
		if(opcode==0x37)
		{
			x[rd]=exim<<12;
			pc+=4;
			return;
		}
		if(opcode==0x17)
		{
			x[rd]=(exim<<12)+pc;
			pc+=4;
			return;
		}
		if(opcode==0x6f)
		{
			x[rd]=pc+4;
			pc+=exim;
			return;
		}		
		if(opcode==0x67)
		{	
			x[rd]=pc+4;
			pc=x[rs1]+exim;
			return;
		}
	}
	void pro()
	{
//		int tmp=0;
		while(1)
		{
//			printf("%d ",pc);
//			for(int i=0;i<32;i++)
//				printf("%d ",x[i]);printf("\n");
			if(s[pc].val==fintag)
			{
				printf("%u\n",x[10]&255u);
				return;
			}
//			debug();
			nextstep();
			x[0]=0;
		}
	}
}
int main()
{
	Init::pro();
	Simu::init();
	Simu::pro();
}

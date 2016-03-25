// Des.cpp : Defines the entry point for the console application.
//

#include "stdlib.h"
#include "stdio.h"
#include <memory.h>
#include "des.h"
#define CRYPTO_CHECKSUM_LENGTH 4
const unsigned char Shift[16]=
{
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
const unsigned char PC_1[56]=
{
    56, 48, 40, 32, 24, 16,  8,  0, 57, 49, 41, 33, 25, 17,
     9,  1, 58, 50, 42, 34, 26, 18, 10,  2, 59, 51, 43, 35,
    62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37, 29, 21,
    13,  5, 60, 52, 44, 36, 28, 20, 12,  4, 27, 19, 11,  3
};
const unsigned char PC_2[48]=
{
    13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9,
    22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
    40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
    43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
};
const unsigned char IIP[64]=
{
    57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7,
    56, 48, 40, 32, 24, 16,  8,  0, 58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4, 62, 54, 46, 38, 30, 22, 14,  6
};
const unsigned char IIP_1[64]=
{
    39,  7, 47, 15, 55, 23, 63, 31, 38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29, 36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27, 34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25, 32,  0, 40,  8, 48, 16, 56, 24
};
const unsigned char E[48]=
{
     63, 32, 33, 34, 35, 36, 35, 36, 37, 38, 39, 40,
     39, 40, 41, 42, 43, 44, 43, 44, 45, 46, 47, 48,
     47, 48, 49, 50, 51, 52, 51, 52, 53, 54, 55, 56,
     55, 56, 57, 58, 59, 60, 59, 60, 61, 62, 63, 32
};
const unsigned char P[32]=
{
     15,  6, 19, 20, 28, 11, 27, 16,
      0, 14, 22, 25,  4, 17, 30,  9,
      1,  7, 23, 13, 31, 26,  2,  8,
     18, 12, 29,  5, 21, 10,  3, 24
};
const unsigned char S[8][64]=
{
    {
	 14,  4,  3, 15,  2, 13,  5,  3, 13, 14,  6,  9, 11,  2,  0,  5,
	  4,  1, 10, 12, 15,  6,  9, 10,  1,  8, 12,  7,  8, 11,  7,  0,
	  0, 15, 10,  5, 14,  4,  9, 10,  7,  8, 12,  3, 13,  1,  3,  6,
	 15, 12,  6, 11,  2,  9,  5,  0,  4,  2, 11, 14,  1,  7,  8, 13
    },
    {
	 15,  0,  9,  5,  6, 10, 12,  9,  8,  7,  2, 12,  3, 13,  5,  2,
	  1, 14,  7,  8, 11,  4,  0,  3, 14, 11, 13,  6,  4,  1, 10, 15,
	  3, 13, 12, 11, 15,  3,  6,  0,  4, 10,  1,  7,  8,  4, 11, 14,
	 13,  8,  0,  6,  2, 15,  9,  5,  7,  1, 10, 12, 14,  2,  5,  9
    },
    {
	 10, 13,  1, 11,  6,  8, 11,  5,  9,  4, 12,  2, 15,  3,  2, 14,
	  0,  6, 13,  1,  3, 15,  4, 10, 14,  9,  7, 12,  5,  0,  8,  7,
	 13,  1,  2,  4,  3,  6, 12, 11,  0, 13,  5, 14,  6,  8, 15,  2,
	  7, 10,  8, 15,  4,  9, 11,  5,  9,  0, 14,  3, 10,  7,  1, 12
    },
    {
	  7, 10,  1, 15,  0, 12, 11,  5, 14,  9,  8,  3,  9,  7,  4,  8,
	 13,  6,  2,  1,  6, 11, 12,  2,  3,  0,  5, 14, 10, 13, 15,  4,
	 13,  3,  4,  9,  6, 10,  1, 12, 11,  0,  2,  5,  0, 13, 14,  2,
	  8, 15,  7,  4, 15,  1, 10,  7,  5,  6, 12, 11,  3,  8,  9, 14
    },
    {
	  2,  4,  8, 15,  7, 10, 13,  6,  4,  1,  3, 12, 11,  7, 14,  0,
	 12,  2,  5,  9, 10, 13,  0,  3,  1, 11, 15,  5,  6,  8,  9, 14,
	 14, 11,  5,  6,  4,  1,  3, 10,  2, 12, 15,  0, 13,  2,  8,  5,
	 11,  8,  0, 15,  7, 14,  9,  4, 12,  7, 10,  9,  1, 13,  6,  3
    },
    {
	 12,  9,  0,  7,  9,  2, 14,  1, 10, 15,  3,  4,  6, 12,  5, 11,
	  1, 14, 13,  0,  2,  8,  7, 13, 15,  5,  4, 10,  8,  3, 11,  6,
	 10,  4,  6, 11,  7,  9,  0,  6,  4,  2, 13,  1,  9, 15,  3,  8,
	 15,  3,  1, 14, 12,  5, 11,  0,  2, 12, 14,  7,  5, 10,  8, 13
    },
    {
	  4,  1,  3, 10, 15, 12,  5,  0,  2, 11,  9,  6,  8,  7,  6,  9,
	 11,  4, 12, 15,  0,  3, 10,  5, 14, 13,  7,  8, 13, 14,  1,  2,
	 13,  6, 14,  9,  4,  1,  2, 14, 11, 13,  5,  0,  1, 10,  8,  3,
	  0, 11,  3,  5,  9,  4, 15,  2,  7,  8, 12, 15, 10,  7,  6, 12
    },
    {
	 13,  7, 10,  0,  6,  9,  5, 15,  8,  4,  3, 10, 11, 14, 12,  5,
	  2, 11,  9,  6, 15, 12,  0,  3,  4,  1, 14, 13,  1,  2,  7,  8,
	  1,  2, 12, 15, 10,  4,  0,  3, 13, 14,  6,  9,  7,  8,  9,  6,
	 15,  1,  5, 12,  3, 10, 14,  5,  8,  7, 11,  0,  4, 13,  2, 11
    }
};
const unsigned char bitmask[]={ 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
class CDes
{
public:
	unsigned char KEY[64];
	unsigned char CDD[56]; 
	unsigned char LR0[64],LR1[64];
	unsigned char SUBKEY[16][48];
	unsigned char bit48[48];
	unsigned char bit32[32];
	unsigned char deskey[9];
    int getbit(unsigned char *buf,int i);
	void setbit(unsigned char *buf,int i);
	void getsubkey();
	void DES_setkey(unsigned char *key);
	void des(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op);
};
int CDes::getbit(unsigned char *buf,int i)
{
	return ((*(unsigned char*)((unsigned char*)buf+(i>>3))) & bitmask[i&0x07])!=0;
}

void CDes::setbit(unsigned char *buf,int i)
{
    *((unsigned char *)buf+(i>>3)) |= bitmask[i&0x07];
}

void CDes::getsubkey()
{
    int i,j,s1,s2;
    for (i=0; i<56; i++)
	CDD[i]=KEY[PC_1[i]];
    for (i=0; i<16; i++)   
	{
		s1=CDD[0]; s2=CDD[1];
		for (j=0; j<28-Shift[i]; j++)
			CDD[j]=CDD[j+Shift[i]];
		if (Shift[i]==2)	
		{
			CDD[26]=s1;
			CDD[27]=s2;
		}
		else
			CDD[27]=s1;
		s1=CDD[28]; s2=CDD[29];
		for (j=28; j<56-Shift[i]; j++)
			CDD[j]=CDD[j+Shift[i]];
		if (Shift[i]==2)        
		{
			CDD[54]=s1;
			CDD[55]=s2;
		}
		else
			CDD[55]=s1;
		for (j=0; j<48; j++)
			SUBKEY[i][j]=CDD[PC_2[j]];
	}
}

void CDes::DES_setkey(unsigned char *key)
{
    int i;
    for (i=0; i<64; i++)
	KEY[i]=getbit(key,i);
    getsubkey();
}

void CDes::des(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op)
{
    int i,j,k,r;
    unsigned char v4,v6;

    for (i=0;i<8;i++) deskey[i]=des_key[i];
    DES_setkey(deskey);
    if (op==1) r=0;
    else r=15;

    for (i=0; i<64; i++)
	LR0[i]=getbit(src,IIP[i]);

    for (i=0; i<16; i++)    
	{
		memcpy(LR1,LR0+32,32);
		memset(LR1+32,0,32);

		for (j=0; j<48; j++)
			bit48[j]=(SUBKEY[r][j]!=LR0[E[j]]);

		for (j=0; j<8; j++)     
		{                          /* S box */
			v6=0; v4=(j<<2)+(j<<1);
			for (k=5; k>=0; k--)
			v6=(v6<<1)+bit48[v4+k];
			v4=S[j][v6];
			v6=(j<<2)+3;
			for (k=0; k<4; k++)
			bit32[v6-k]=v4&1,v4>>=1;
		}
		for (j=0; j<32; j++)
			LR1[j+32]=(LR0[j]!=bit32[P[j]]);
		memcpy(LR0,LR1,64);
		r+=op;
	}
    memcpy(LR1,LR0+32,32);
    memcpy(LR1+32,LR0,32);
    memset(dst,0,8);
    for (i=0; i<64; i++)
	if (LR1[IIP_1[i]]) setbit(dst,i);
}
static void fndes(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op)
{
	CDes *pDes=new CDes();
	if(pDes==NULL) 
		return;
	pDes->des(src,dst,des_key,op);
	delete pDes;
}
static void fndes3(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op) 
{
	unsigned char temp[8];
	if(op==1)
	{
		fndes(src,dst,des_key,1);
		fndes(dst,temp,des_key+8,-1);
		fndes(temp,dst,des_key+16,1);
	}
	else
	{
		fndes(src,dst,des_key+16,-1);
		fndes(dst,temp,des_key+8,1);
		fndes(temp,dst,des_key,-1);
	}
}
void BitXor(BYTE *Data1, BYTE *Data2, int Len, BYTE *Dest)
{
	int i;
	for (i = 0; i < Len; i++)	
		Dest[i] = Data1[i] ^ Data2[i];
}

void MAC16(BYTE *Key,BYTE *Init,int Len, BYTE *Data,BYTE *Dst)
{ 
	BYTE	pbySrcTemp[8];
	BYTE	pbyInitData[8];
	BYTE	pbyDeaSrc[8];
	BYTE	KeyA[8];
	BYTE	KeyB[8];
	int	i, j, n, iAppend;
	n = Len / 8 + 1;
	iAppend = 8 - ( n * 8 - Len);
	memcpy (pbyInitData,Init,8);
	memcpy (KeyA,Key,8);
	memcpy (KeyB,&Key[8],8);
	for(i = 0; i < n; i++)
	{
		memset(pbySrcTemp, 0x00, 8);
		if(i==(n-1))
		{
			memcpy(pbySrcTemp, &Data[i*8], iAppend); 
			pbySrcTemp[iAppend] = 0x80;
			for (j = iAppend + 1; j < 8; j++) pbySrcTemp[j] = 0x00;
		}
		else memcpy(pbySrcTemp, &Data[i*8], 8); 
		BitXor(pbySrcTemp, pbyInitData, 8, pbyDeaSrc);
		memset(pbyInitData, 0x00, 8);
		//DES(1,KeyA, pbyDeaSrc, pbyInitData);
		DES(pbyDeaSrc, pbyInitData,KeyA,1);
	
	}

	//DES(-1,KeyB, pbyInitData, pbyDeaSrc);
	DES(pbyInitData, pbyDeaSrc,KeyB,-1);
	//DES(1,KeyA, pbyDeaSrc, pbyInitData);
	DES(pbyDeaSrc, pbyInitData,KeyA,1);
	memcpy(Dst, pbyInitData, 8);
}
/*src 明文,dst 密文, op -1 解密, 1 加密  */
void DES(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op) 
{
	fndes(src,dst,des_key,op);
}

/* 采用CBC模式进行计算加密校验和。并且进行填充
 参数：	inital为进行计算加密校验和的初始值，为8个字节。
		slen为计算加密校验和数据src长度
		src待计算加密校验和数据
		[out] dst加密校验和。dst 空间由调用函数负责管理(不小于8)。
返回值：0 正确，其他错误
 */
int DesChecksum(unsigned char *inital,int slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	unsigned char buf[8];
	unsigned char dstbuf[8];
	int nleft;
	int i;
	memcpy(dstbuf,inital,8);	
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=dstbuf[i]^src[slen-nleft+i];
		fndes(buf,dstbuf,key,1) ;	//加密
		nleft-=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=dstbuf[i]^src[slen-nleft+i];
	//填充
	buf[i++]=dstbuf[i]^0x80;
	for(;i<8;i++)
		buf[i]=dstbuf[i]^0x0;
	fndes(buf,dstbuf,key,1) ;
	memcpy(dst,dstbuf,CRYPTO_CHECKSUM_LENGTH);
	return 0;
}
/***********************  以下定义 3DES 算法的实现   ******************************
3DES加解密和密码校验和采用《金融IC卡规范》。
************************************************************************************/
/* 3DES 组加解密
参数：src 输入，长度为8 字节
	  dst 输出，长度为8 字节
	  des_key为密钥，长度为24字节
	  op 选项，-1 解密, 1 加密
*/
void TripleDES(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op) 
{
	fndes3(src,dst,des_key,op);
}
/* 3DES采用计算Cryptogram。自动进行填充(符合PBOC2个人化规范)
 参数：	inital 为进行计算Cryptogram的初始值，为8个字节。
		slen为计算Cryptogram数据src长度
		src待计算Cryptogram的数据
		[out] dst计算Cryptogram的结果。dst 空间由调用函数负责管理。
		key为密钥(16字节)
返回值：0 正确，其他错误
 */
int TripleDESCryptogram(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	unsigned char buf[8];
	unsigned char dstbuf[8];
	int nleft;
	int i;
	memcpy(dstbuf,inital,8);	
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=dstbuf[i]^src[slen-nleft+i];
		fndes(buf,dstbuf,key,1) ;	//加密
		nleft-=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=dstbuf[i]^src[slen-nleft+i];
	//填充
	buf[i++]=dstbuf[i]^0x80;
	for(;i<8;i++)
		buf[i]=dstbuf[i]^0x0;
	fndes3(buf,dstbuf,key,1) ;  //仅在最后一组采用3DES
	memcpy(dst,dstbuf,8);	//长度为8字节
	return 0;
}
int TripleDESCryptogram2(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	unsigned char buf[8];
	unsigned char dstbuf[8];
	int nleft;
	int i;
	memcpy(dstbuf,inital,8);	
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=dstbuf[i]^src[slen-nleft+i];
		fndes3(buf,dstbuf,key,1) ;	//加密
		nleft-=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=dstbuf[i]^src[slen-nleft+i];
	//填充
	buf[i++]=dstbuf[i]^0x80;
	for(;i<8;i++)
		buf[i]=dstbuf[i]^0x0;
	fndes3(buf,dstbuf,key,1) ;  //仅在最后一组采用3DES
	memcpy(dst,dstbuf,8);	//长度为8字节
	return 0;
}
/* 3DES采用计算加密校验和。并且进行填充(符合金融规范)
 参数：	inital 为进行计算加密校验和的初始值，为8个字节。
		slen为计算加密校验和数据src长度
		src待计算加密校验和数据
		[out] dst加密校验和。dst 空间由调用函数负责管理。
		key为密钥(16字节)
返回值：0 正确，其他错误
 */
int TripleDESChecksum(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	unsigned char buf[8];
	unsigned char dstbuf[8];
	int nleft;
	int i;
	memcpy(dstbuf,inital,8);	
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=dstbuf[i]^src[slen-nleft+i];
		fndes(buf,dstbuf,key,1) ;	//加密
		nleft-=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=dstbuf[i]^src[slen-nleft+i];
	//填充
	buf[i++]=dstbuf[i]^0x80;
	for(;i<8;i++)
		buf[i]=dstbuf[i]^0x0;
	fndes3(buf,dstbuf,key,1) ;  //仅在最后一组采用3DES
	memcpy(dst,dstbuf,CRYPTO_CHECKSUM_LENGTH);
	return 0;
}
/**************************************************************
* 函数名: TripleDESEncipher(int *datalen, unsigned char *src,unsigned char *dst,unsigned char *key)
* 功  能: 3DES 加密计算（每一数据块均使用3DES）
* 输  入:	datalen 输入为待加密数据src长度
*			src		待加密数据
*			key		16字节密钥
* 输  出:	dst		计算结果
*			datalen 加密后数据 dst长度
* 返  回:   无
**************************************************************/
void TripleDESEncipher(BYTE *datalen, BYTE *src,BYTE *dst,BYTE *key)
{
	BYTE tempbuf[8];
	BYTE nleft;
	BYTE i;

	nleft=*datalen;
	while(nleft>=8)
	{
		memcpy(tempbuf,src+*datalen-nleft,8);
		TripleDES(tempbuf,tempbuf,key,1) ;	//加密
		memcpy(dst+*datalen-nleft,tempbuf,8);
		nleft-=8;
	}
	if(nleft>0)		// 注意：最后一帧不为8字节时才填充
	{
		//最后分组
		for(i=0;i<nleft;i++)
			tempbuf[i]=src[*datalen-nleft+i];
		//填充
		tempbuf[i++]=0x80;
		for(;i<8;i++)
			tempbuf[i]=0x0;
		TripleDES(tempbuf,tempbuf,key,1) ;
		memcpy(dst+*datalen-nleft,tempbuf,8);
		*datalen=*datalen+8-nleft;
	}

}
int TripleDesCBC(unsigned char *initial,unsigned char &slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	int i,len=0;
	int nleft;
	unsigned char buf[8];
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=initial[i]^src[slen-nleft+i];
		TripleDES(buf,initial,key,1) ;	//加密
		memcpy(dst,initial,8);
		dst+=8;
		nleft-=8;
		len+=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=initial[i]^src[slen-nleft+i];
	//填充
	buf[i++]=initial[i]^0x80;
	for(;i<8;i++)
		buf[i]=initial[i]^0x0;
	TripleDES(buf,dst,key,1) ;
	len+=8;
	slen=len;
	return 0;
}

int TripleDESCryptogram_Des(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	unsigned char buf[8];
	unsigned char dstbuf[8];
	int nleft;
	int i;
	memcpy(dstbuf,inital,8);	
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=dstbuf[i]^src[slen-nleft+i];
		fndes(buf,dstbuf,key,1) ;	//加密
		nleft-=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=dstbuf[i]^src[slen-nleft+i];
	//填充
	buf[i++]=dstbuf[i]^0x80;
	for(;i<8;i++)
		buf[i]=dstbuf[i]^0x0;
	//fndes3(buf,dstbuf,key,1) ;  //仅在最后一组采用3DES
	fndes(buf,dstbuf,key,1) ;  //仅在最后一组采用3DES
	memcpy(dst,dstbuf,8);	//长度为8字节
	return 0;
}
int TripleDESCryptogram2_HuDa(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key)
{
	unsigned char buf[8];
	unsigned char dstbuf[8];
	int nleft;
	int i;
	memcpy(dstbuf,inital,8);	
	nleft=slen;
	while(nleft>=8)
	{
		for(i=0;i<8;i++)
			buf[i]=dstbuf[i]^src[slen-nleft+i];
		fndes(buf,dstbuf,key,1) ;	//加密
		nleft-=8;
	}
	//最后分组
	for(i=0;i<nleft;i++)
		buf[i]=dstbuf[i]^src[slen-nleft+i];
	//填充
	buf[i++]=dstbuf[i]^0x80;
	for(;i<8;i++)
		buf[i]=dstbuf[i]^0x0;

	fndes(buf,dstbuf,key+8,-1) ;  //仅在最后一组采用3DES

	unsigned char temp[9];
	memset(temp,0x00,sizeof(temp));
	fndes(dstbuf,temp,key,1) ;  //仅在最后一组采用3DES
	memcpy(dst,temp,8);	//长度为8字节
	return 0;
}

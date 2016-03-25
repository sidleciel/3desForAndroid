/*  定义DES的实现函数
	编写：
	版权所有  2001.5
  */

#ifndef _DES_H_2001_05_12
#define _DES_H_2001_05_12

typedef unsigned char BYTE;

/* DES算法实现
参数：src 输入，长度为8 字节
	  dst 输出，长度为8 字节
	  des_key为密钥，长度为8字节
	  op 选项，-1 解密, 1 加密
*/
void DES(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op) ;

/* 采用CBC模式进行计算加密校验和。并且进行填充
 参数：	inital为进行计算加密校验和的初始值，为8个字节。
		slen为计算加密校验和数据src长度
		src待计算加密校验和数据
		[out] dst加密校验和。dst 空间由调用函数负责管理(不小于8)。
返回值：0 正确，其他错误
 */
int DesChecksum(unsigned char *inital,int slen, unsigned char *src,unsigned char *dst,unsigned char *key);

/***********************  以下定义 3DES 算法的实现   ******************************
3DES加解密和密码校验和，其中密码校验和采用《金融IC卡规范》。
************************************************************************************/
/* 3DES 组加解密
参数：src 输入，长度为8 字节
	  dst 输出，长度为8 字节
	  des_key 为密钥，长度为16字节
	  op 选项，-1 解密, 1 加密
*/
void TripleDES(unsigned char *src,unsigned char *dst,unsigned char *des_key,int op);

/* 3DES采用计算Cryptogram。自动进行填充(符合PBOC2个人化规范)
 参数：	inital 为进行计算Cryptogram的初始值，为8个字节。
		slen为计算Cryptogram数据src长度
		src待计算Cryptogram的数据
		[out] dst计算Cryptogram的结果。dst 空间由调用函数负责管理。
		key为密钥(16字节)
返回值：0 正确，其他错误
 */
int TripleDESCryptogram(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key);
int TripleDESCryptogram2(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key);
/* 3DES采用计算加密校验和。并且进行填充(符合金融规范)
/* 3DES采用计算加密校验和。并且进行填充(符合金融规范)
 参数：	inital 为进行计算加密校验和的初始值，为8个字节。
		slen为计算加密校验和数据src长度
		src待计算加密校验和数据
		[out] dst加密校验和。dst 空间由调用函数负责管理。
		key为密钥(16字节)
返回值：0 正确，其他错误
 */
int TripleDESChecksum(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key);
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
void TripleDESEncipher(BYTE *datalen, BYTE *src,BYTE *dst,BYTE *key);
int TripleDesCBC(unsigned char *inital,unsigned char &slen, unsigned char *src,unsigned char *dst,unsigned char *key);

int TripleDESCryptogram_Des(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key);
int TripleDESCryptogram2_HuDa(unsigned char *inital, int slen, unsigned char *src,unsigned char *dst,unsigned char *key);
//void _stdcall MAC16(BYTE *Key,BYTE *Init,int Len, BYTE *Data,BYTE *Dst);
void MAC16(BYTE *Key,BYTE *Init,int Len, BYTE *Data,BYTE *Dst);
void BitXor(BYTE *Data1, BYTE *Data2, int Len, BYTE *Dest);


#endif

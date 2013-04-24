
#ifndef __CONFIG_H 
#define __CONFIG_H


#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char  uint8;                  /* 	�޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* �з���8λ���ͱ���  */
typedef unsigned short uint16;             /* �޷���16λ���ͱ��� */
typedef signed   short int16;                /* �з���16λ���ͱ��� */
typedef unsigned int   uint32;              /* �޷���32λ���ͱ��� */
typedef signed   int   int32;                 /* �з���32λ���ͱ��� */
typedef float          fp32;                     /*�����ȸ�������32λ���ȣ� */
typedef double         fp64;                /*˫���ȸ�������64λ���ȣ� */



#include  "LPC2124.h"
#include  "stdio.h"
#include  "math.h"
#include  "keyboard.h"
  

/* ϵͳ����, Fosc��Fcclk��Fcco��Fpclk���붨��*/
#define Fosc            11059200                 //Ӧ����ʵ��һ������Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define Fcclk           (Fosc * 4)                  //ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define Fcco            (Fcclk * 4)                //CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1          //VPBʱ��Ƶ�ʣ�ֻ��Ϊ(Fcclk / 4)��1��2��4��

#include    "target.h"              //��һ�䲻��ɾ��

#endif

#include  "config.h"
#define rs (1<<8)
#define rw (1<<9)
#define en (1<<10)
#define busy (1<<7)

#define MIN_PULSES  6
#define MAX_PULSES  1785
#define MAX_PWM  16000
#define MIN_PWM  1
#define CKTIME   100                      /*100ms*/ 


#define P_ref  1
#define I_ref  2


int32 P_val=0;
int32 I_val=0;
int32 D_val=0;
int32 T_val=0;
int32  changeref=1;
uint8 dir[4]={'+','\0','-','\0'};
uint8 rpm[]={"rpm"};
uint8 current[]={"Current:"};
uint8 seted[]={"  Seted:"};
uint8 curse[4]={'>','\0',' ','\0'};
uint8 enternum[]={"Please set the rpm:"};
uint8 strcrt[5];
uint8 strset[5];
uint8 flag=1;
uint8 shutdown=0;
uint8 key=16;
uint8 keyhit=16;
uint8 dirhit=0;
uint8 keydown=0;
uint8 downindex=0;
uint8 dircrt=0;
int32 varcrt=0;
int32 varset=(int32)0;
int32 keysum=(int32)0;

uint32 rtcounts=0;


int32 setcounts=0;
int32 deltacounts=0;
int32 pwmdata=0;



/****************************************************************************
* ���ܣ���ʱ
****************************************************************************/
void delay(int ms)                                                         
{                                                                          
   int i;                                                                  
   while(ms--)                                                             
   {                                                                       
     for(i = 0;i<250;i++){}                                                                     
   }                                                                       
}      
/****************************************************************************                                                                          
* ���ƣ�WrOp()
* ���ܣ�д����
****************************************************************************/
void WrOp(uint8 dat)
{
	
	IO0CLR=rs;		//ȫ������
	IO0CLR=rw;
	IO0CLR=0xff;		//������
	IO0SET=dat;		//������
	IO0SET=en;
	IO0CLR=en;
}
/****************************************************************************
* ���ƣ�WrDat()
* ���ܣ�д���ݺ���
****************************************************************************/
void WrDat(uint8 dat)	
{
	
	IO0SET=rs;
	IO0CLR=rw;
	IO0CLR=0xff;		//������
	IO0SET=dat;		//������
	IO0SET=en;
	IO0CLR=en;
	
}
               
/****************************************************************************
* ���ƣ�lcd_init()
* ���ܣ�lcd��ʼ������
****************************************************************************/
void lcd_init(void)
{
	WrOp(0x38);			//16*2��ʾ,5*7����,8λ����        
	WrOp(0x06);			//����1
	WrOp(0x0c);			//����ʾ,�ع��
	IO0DIR |=0x000007ff;		//����Ϊ���
	IO0CLR=0x7ff;
}
/****************************************************************************
* ���ƣ�DisText()
* ���ܣ���ʾ�ı�����
****************************************************************************/
void DisText(uint8 addr,uint8 *p)
{
	WrOp(addr);
	while(*p !='\0')WrDat(*(p++));
}

/****************************************************************************
* ���ܣ���������ʾ��,�������ִ��ѭ����
****************************************************************************/
void DisCurse(uint8 addr)
{
	
	DisText(addr,curse);
	DisText((addr+1),(curse+2));
	DisText((addr+2),(curse+2));
	delay(300);
	DisText(addr,curse);
	DisText((addr+1),curse);
	DisText((addr+2),(curse+2));
	delay(300);
	DisText(addr,curse);
	DisText((addr+1),curse);
	DisText((addr+2),curse);
	delay(300);
	DisText(addr,(curse+2));
	DisText((addr+1),(curse+2));
	DisText((addr+2),(curse+2));
	delay(200);
	
}


   
/****************************************************************************
 ���ܣ�������ֵת��Ϊ�ַ���������5.2��ʽ
****************************************************************************/

void Int2Str(unsigned char str[],int32 var)
{
	
		
		int32 t=(int32)(var*100);
		int32 i,k;

		
		for(i=5;i>=3;i--)
  		 {
       		 k=(int32)pow(10,i);
       		 str[5-i]=(unsigned char)((int32)((t/k)%10)+48);
		 t=(t%k);
			 
		 }
		str[3]=(unsigned char)((((int32)(var))%10)+48);
		
		str[4]='\0';
    
}

/****************************************************************************
* ���ƣ�Key_Process()
****************************************************************************/
void Key_Process(uint8 num)
{
 switch(num)
	 {
		case 0:keyhit=7;break;
		case 1:keyhit=8;break;
		case 2:keyhit=9;break;
		case 3:keyhit=10;dirhit=!dirhit;break;//ת������
		case 4:keyhit=4;break;
		case 5:keyhit=5;break;
		case 6:keyhit=6;break;
		case 7:keyhit=11;if(!flag)varset=(int32)(varset+1);//�ڼ���״̬��ֱ��΢����ת��
						else keysum=(int32)(keysum+1);break;//������״̬����keysum
		case 8:keyhit=1;break;
		case 9:keyhit=2;break;
		case 10:keyhit=3;break;
		case 11:keyhit=12;if(!flag)varset=(int32)(varset-1);//�ڼ���״ֱ̬��΢����ת��
						 else keysum=(int32)(keysum-1);break;//������״̬����keysum
		case 12:keyhit=13;shutdown=!shutdown;
					if(shutdown) {flag=0;varset=0;}
					else {flag=1;keysum=(int32)0;downindex=0;WrOp(0x01);}
					break;// ǿ�ƽ��������Ϊ��ʼֵ
		case 13:keyhit=0;break;
		case 14:keyhit=14;flag=1;keysum=(int32)0;downindex=0;WrOp(0x01);break;//  ��������ģʽ
		case 15:keyhit=15;flag=0; varset=keysum;WrOp(0x01);break;//ȷ�����룬���ؼ���ģʽ
		default:break;
	 }
	if((keysum<0))keysum=0;
	if((varset<0))varset=0;
	 if(varset>350)varset=350;// ���ת������
}

void __irq catch_pulses(void)

{
	rtcounts++;
		
	
	T0IR=0x20;                        //����жϱ�־,��λCR1�ж�
	VICVectAddr=0x00;                 //֪ͨVIC�жϴ������

}
void __irq PI_porcess(void)// ÿ CKTIME ms����һ��ռ�ձ� 
{
    
	deltacounts=(rtcounts*1000)/CKTIME;//���������ʲ���
	setcounts=varset*5;//���趨��ת��ת��Ϊ��������
    	
	P_val=setcounts*P_ref*changeref;

	
	if((setcounts-deltacounts)>0)
	if(I_val<MAX_PULSES)I_val++;
	if((setcounts-deltacounts)<0)
	if(I_val>(-MAX_PULSES))I_val--;

	T_val=(I_val*I_ref*changeref*1000)/CKTIME;//ƽ�������ۻ���
	
	T_val=(int32)(T_val/10);//��ԭchangeref�ķŴ���

	if(T_val<MIN_PWM)T_val=MIN_PWM;
	if(T_val>MAX_PWM)T_val=MAX_PWM;
	pwmdata=(int32)T_val;
	
	varcrt=deltacounts/5;//�Ѳ�������������ת��Ϊת��
	pwmdata=(int32)(P_val/10);
	rtcounts=0;
   
	
	T1IR=0x01;                        //����жϱ�־����λMR0�ж�
	VICVectAddr=0x00;                 //֪ͨVIC�жϴ������
}
void capinit(void)
{
T0PR=5;                         //2����Ƶ��TC��1
T0CCR=(1<<3)|(1<<5);          //����CAP0.1�����ز��񣬲����TC��ֵ����T0CR1,�������ж�
T0TC=0;
T0TCR=0x01;                           //������ʱ��
}

void time1init(void)
{

  T1PR=99;                 //���ö�ʱ����ƵΪ25��Ƶ,��147450Hz
  T1MCR=0x03;              //ƥ��ͨ��0ƥ���жϲ���λT1TC
  T1MR0=702;          //�Ƚ�ֵ,��ĸΪFosc������/2Ϊ0.5���Դ����ƣ��˴�Ϊ0.01��,27648/10

  T1TCR=0x03;  //��������λT1TC            
  T1TCR=0x01;
  
}
void pwminit(void)
{
 	PWMPR=0x00;                      //����Ƶ,����Ƶ��ΪFpclk
	PWMMCR=0x02;                     //����PWMMR0ƥ��ʱ��λPWMTC
	PWMMR0=MAX_PWM;                     //����PWM����
	PWMMR5=1;                     //����PWMռ�ձ�
	PWMLER=0x21;                     //PWMMR0,PWMMR5����
	PWMPCR=1<<13;                   //����PWM5���,����PWM
	PWMTCR=0x09;                     //������ʱ��,PWMʹ��
}
/****************************************************************************
* ���ƣ�main()
* ���ܣ���ʾ�ı�
****************************************************************************/

int  main(void)
{   
  	 PINSEL1=0x00800400;//���Ź���ѡ��
	IO0DIR =0x020007ff;//��GPIO�ķ������ã�0��1����
	
	changeref=(10*MAX_PWM )/ MAX_PULSES;//changeref���Ŵ�;

	lcd_init();//LCD�ĳ�ʼ��
	Keyboard_Initialize();
	pwminit(); //PWM��ʼ��
	
	capinit();
 	time1init();
 	
 	VICIntSelect=0x00;     
 	
	VICVectCntl0=0x24;
	VICVectAddr0=(uint32)catch_pulses;  
	
	VICVectCntl1=0x25;     
	VICVectAddr1=(uint32)PI_porcess; 
	
	VICIntEnable=0x00000030;            
	IO0CLR =(1<<25);  //���ó�ʼ�����λ  
	pwmdata=MIN_PWM;
	while(1)
	{
	
	key=Keyboard_Scan();
	if((key!=255))keydown=1;//���񰴼����µ���Ӧ
	else keydown=0;
	Key_Process(key);//��ֵ��Ӧ�Ĳ������޸�flag,keysum,varset,dirhit,keyhit.
	

	PWMMR0=MAX_PWM;
	PWMMR5=pwmdata;
	PWMLER=0x21;
	
	 if(!flag)
	{
	if(IO0PIN&(1<<23))dircrt=0;//ת����
	else dircrt=1;
	if(dirhit)IO0SET =(1<<25);//ת�򿪹�
	else IO0CLR =(1<<25); 
	

	DisText(0x80,current);
	DisText(0x91,rpm);
	DisText(0xc0,seted);
	DisText(0xd1,rpm);
	if(dircrt)DisText(0x88,dir);//���ӵ�ת����ʾ
	else DisText(0x88,(dir+2));
	if(dirhit)DisText(0xc8,dir);//���õ�ת����ʾ
	else DisText(0xc8,(dir+2));
	Int2Str(strcrt,varcrt);//���ӵ�ת����ʾ
	Int2Str(strset,varset);//���õ�ת����ʾ
	DisText(0x89,strcrt);
	DisText(0xc9,strset);
	delay(100);
	}
	else
	{
		if((keydown)&&(keyhit<=9)&&(downindex<4))
		{	
		keysum=(int32)(keysum*10+keyhit);//������ֵ
		downindex++;
		}
	DisText(0x80,enternum);
	DisCurse(0xc0);	
	Int2Str(strset,keysum);//�û�����ļ�ֵ��ʾ
	DisText(0xc6,strset);
	if(dirhit)DisText(0xc4,dir);//���õĵ�ת����ʾ
	else DisText(0xc4,(dir+2));
	delay(100);
	}
	
	}
	
}


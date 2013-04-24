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
* 功能：延时
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
* 名称：WrOp()
* 功能：写函数
****************************************************************************/
void WrOp(uint8 dat)
{
	
	IO0CLR=rs;		//全部清零
	IO0CLR=rw;
	IO0CLR=0xff;		//先清零
	IO0SET=dat;		//再送数
	IO0SET=en;
	IO0CLR=en;
}
/****************************************************************************
* 名称：WrDat()
* 功能：写数据函数
****************************************************************************/
void WrDat(uint8 dat)	
{
	
	IO0SET=rs;
	IO0CLR=rw;
	IO0CLR=0xff;		//先清零
	IO0SET=dat;		//再送数
	IO0SET=en;
	IO0CLR=en;
	
}
               
/****************************************************************************
* 名称：lcd_init()
* 功能：lcd初始化函数
****************************************************************************/
void lcd_init(void)
{
	WrOp(0x38);			//16*2显示,5*7点阵,8位数据        
	WrOp(0x06);			//光标加1
	WrOp(0x0c);			//开显示,关光标
	IO0DIR |=0x000007ff;		//设置为输出
	IO0CLR=0x7ff;
}
/****************************************************************************
* 名称：DisText()
* 功能：显示文本函数
****************************************************************************/
void DisText(uint8 addr,uint8 *p)
{
	WrOp(addr);
	while(*p !='\0')WrDat(*(p++));
}

/****************************************************************************
* 功能：闪动的提示符,必须放入执行循环中
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
 功能：浮点数值转换为字符串函数，5.2格式
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
* 名称：Key_Process()
****************************************************************************/
void Key_Process(uint8 num)
{
 switch(num)
	 {
		case 0:keyhit=7;break;
		case 1:keyhit=8;break;
		case 2:keyhit=9;break;
		case 3:keyhit=10;dirhit=!dirhit;break;//转向设置
		case 4:keyhit=4;break;
		case 5:keyhit=5;break;
		case 6:keyhit=6;break;
		case 7:keyhit=11;if(!flag)varset=(int32)(varset+1);//在监视状态置直接微调整转数
						else keysum=(int32)(keysum+1);break;//在设置状态调整keysum
		case 8:keyhit=1;break;
		case 9:keyhit=2;break;
		case 10:keyhit=3;break;
		case 11:keyhit=12;if(!flag)varset=(int32)(varset-1);//在监视状态直接微调整转数
						 else keysum=(int32)(keysum-1);break;//在设置状态调整keysum
		case 12:keyhit=13;shutdown=!shutdown;
					if(shutdown) {flag=0;varset=0;}
					else {flag=1;keysum=(int32)0;downindex=0;WrOp(0x01);}
					break;// 强制将电机重启为初始值
		case 13:keyhit=0;break;
		case 14:keyhit=14;flag=1;keysum=(int32)0;downindex=0;WrOp(0x01);break;//  进入设置模式
		case 15:keyhit=15;flag=0; varset=keysum;WrOp(0x01);break;//确定输入，返回监视模式
		default:break;
	 }
	if((keysum<0))keysum=0;
	if((varset<0))varset=0;
	 if(varset>350)varset=350;// 最大转数限制
}

void __irq catch_pulses(void)

{
	rtcounts++;
		
	
	T0IR=0x20;                        //清除中断标志,复位CR1中断
	VICVectAddr=0x00;                 //通知VIC中断处理结束

}
void __irq PI_porcess(void)// 每 CKTIME ms计算一次占空比 
{
    
	deltacounts=(rtcounts*1000)/CKTIME;//对脉冲速率采样
	setcounts=varset*5;//把设定的转速转换为脉冲速率
    	
	P_val=setcounts*P_ref*changeref;

	
	if((setcounts-deltacounts)>0)
	if(I_val<MAX_PULSES)I_val++;
	if((setcounts-deltacounts)<0)
	if(I_val>(-MAX_PULSES))I_val--;

	T_val=(I_val*I_ref*changeref*1000)/CKTIME;//平均误差的累积和
	
	T_val=(int32)(T_val/10);//还原changeref的放大倍率

	if(T_val<MIN_PWM)T_val=MIN_PWM;
	if(T_val>MAX_PWM)T_val=MAX_PWM;
	pwmdata=(int32)T_val;
	
	varcrt=deltacounts/5;//把采样的脉冲速率转换为转速
	pwmdata=(int32)(P_val/10);
	rtcounts=0;
   
	
	T1IR=0x01;                        //清除中断标志，复位MR0中断
	VICVectAddr=0x00;                 //通知VIC中断处理结束
}
void capinit(void)
{
T0PR=5;                         //2个主频后TC加1
T0CCR=(1<<3)|(1<<5);          //设置CAP0.1上升沿捕获，捕获后将TC的值放入T0CR1,并产生中断
T0TC=0;
T0TCR=0x01;                           //启动定时器
}

void time1init(void)
{

  T1PR=99;                 //设置定时器分频为25分频,得147450Hz
  T1MCR=0x03;              //匹配通道0匹配中断并复位T1TC
  T1MR0=702;          //比较值,分母为Fosc，分子/2为0.5秒以此类推，此处为0.01秒,27648/10

  T1TCR=0x03;  //启动并复位T1TC            
  T1TCR=0x01;
  
}
void pwminit(void)
{
 	PWMPR=0x00;                      //不分频,计数频率为Fpclk
	PWMMCR=0x02;                     //设置PWMMR0匹配时复位PWMTC
	PWMMR0=MAX_PWM;                     //设置PWM周期
	PWMMR5=1;                     //设置PWM占空比
	PWMLER=0x21;                     //PWMMR0,PWMMR5锁存
	PWMPCR=1<<13;                   //允许PWM5输出,单边PWM
	PWMTCR=0x09;                     //启动定时器,PWM使能
}
/****************************************************************************
* 名称：main()
* 功能：显示文本
****************************************************************************/

int  main(void)
{   
  	 PINSEL1=0x00800400;//引脚功能选择
	IO0DIR =0x020007ff;//对GPIO的方向设置，0入1出。
	
	changeref=(10*MAX_PWM )/ MAX_PULSES;//changeref被放大;

	lcd_init();//LCD的初始化
	Keyboard_Initialize();
	pwminit(); //PWM初始化
	
	capinit();
 	time1init();
 	
 	VICIntSelect=0x00;     
 	
	VICVectCntl0=0x24;
	VICVectAddr0=(uint32)catch_pulses;  
	
	VICVectCntl1=0x25;     
	VICVectAddr1=(uint32)PI_porcess; 
	
	VICIntEnable=0x00000030;            
	IO0CLR =(1<<25);  //设置初始方向电位  
	pwmdata=MIN_PWM;
	while(1)
	{
	
	key=Keyboard_Scan();
	if((key!=255))keydown=1;//捕获按键按下的响应
	else keydown=0;
	Key_Process(key);//键值对应的操作，修改flag,keysum,varset,dirhit,keyhit.
	

	PWMMR0=MAX_PWM;
	PWMMR5=pwmdata;
	PWMLER=0x21;
	
	 if(!flag)
	{
	if(IO0PIN&(1<<23))dircrt=0;//转向检测
	else dircrt=1;
	if(dirhit)IO0SET =(1<<25);//转向开关
	else IO0CLR =(1<<25); 
	

	DisText(0x80,current);
	DisText(0x91,rpm);
	DisText(0xc0,seted);
	DisText(0xd1,rpm);
	if(dircrt)DisText(0x88,dir);//监视的转向显示
	else DisText(0x88,(dir+2));
	if(dirhit)DisText(0xc8,dir);//设置的转向显示
	else DisText(0xc8,(dir+2));
	Int2Str(strcrt,varcrt);//监视的转速显示
	Int2Str(strset,varset);//设置的转速显示
	DisText(0x89,strcrt);
	DisText(0xc9,strset);
	delay(100);
	}
	else
	{
		if((keydown)&&(keyhit<=9)&&(downindex<4))
		{	
		keysum=(int32)(keysum*10+keyhit);//按键和值
		downindex++;
		}
	DisText(0x80,enternum);
	DisCurse(0xc0);	
	Int2Str(strset,keysum);//用户输入的键值显示
	DisText(0xc6,strset);
	if(dirhit)DisText(0xc4,dir);//设置的的转向显示
	else DisText(0xc4,(dir+2));
	delay(100);
	}
	
	}
	
}


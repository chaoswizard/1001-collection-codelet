
;定义堆栈的大小
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         0
IRQ_STACK_LEGTH         EQU         256
ABT_STACK_LEGTH         EQU         0
UND_STACK_LEGTH         EQU         0

NoInt       EQU 0x80

USR32Mode   EQU 0x10
SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f
IRQ32Mode   EQU 0x12
FIQ32Mode   EQU 0x11

    IMPORT __use_no_semihosting_swi


;引入的外部标号在这声明
    IMPORT  FIQ_Exception                   ;快速中断异常处理程序
    IMPORT  __main                          ;C语言主程序入口 
    IMPORT  TargetResetInit                 ;目标板基本初始化


;给外部使用的标号在这声明
    EXPORT  bottom_of_heap
    EXPORT  StackUsr
    
    EXPORT  Reset
    EXPORT __user_initial_stackheap

    CODE32
    PRESERVE8
    AREA    vectors,CODE,READONLY
        ENTRY


;中断向量表
Reset
        LDR     PC, ResetAddr
        LDR     PC, UndefinedAddr
        LDR     PC, SWI_Addr
        LDR     PC, PrefetchAddr
        LDR     PC, DataAbortAddr
        DCD     0xb9205f80
        LDR     PC, [PC, #-0xff0]
        LDR     PC, FIQ_Addr

ResetAddr           DCD     ResetInit
UndefinedAddr    DCD     Undefined
SWI_Addr            DCD     SoftwareInterrupt
PrefetchAddr       DCD     PrefetchAbort
DataAbortAddr   DCD     DataAbort
Nouse                   DCD     0
IRQ_Addr             DCD     0
FIQ_Addr             DCD     FIQ_Handler



Undefined
        B       Undefined


SoftwareInterrupt			
        B       SoftwareInterrupt	


PrefetchAbort
        B       PrefetchAbort


DataAbort
        B       DataAbort


FIQ_Handler
        STMFD   SP!, {R0-R3,R12,LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3,R12,LR}
        SUBS    PC,  LR,  #4
        


InitStack    
        MOV     R0, LR

;设置管理模式堆栈
        MSR     CPSR_c, #0xd3		
        LDR     SP, StackSvc	

;设置中断模式堆栈
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq

;设置快速中断模式堆栈
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq

;设置中止模式堆栈
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt

;设置未定义模式堆栈
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd

;设置系统模式堆栈
        MSR     CPSR_c, #0x5f
        LDR     SP, =StackUsr

        MOV     PC, R0



ResetInit
        
        BL      InitStack               ;初始化堆栈
        BL      TargetResetInit         ;目标板基本初始化
                                        ;跳转到c语言入口 
        B       __main


__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
;    LDR   r1,=StackUsr
    MOV   pc,lr


StackSvc           DCD     SvcStackSpace + (SVC_STACK_LEGTH - 1)* 4
StackIrq             DCD     IrqStackSpace + (IRQ_STACK_LEGTH - 1)* 4
StackFiq           DCD     FiqStackSpace + (FIQ_STACK_LEGTH - 1)* 4
StackAbt           DCD     AbtStackSpace + (ABT_STACK_LEGTH - 1)* 4
StackUnd           DCD     UndtStackSpace + (UND_STACK_LEGTH - 1)* 4


    
;/* 分配堆栈空间 */
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4 	 ;管理模式堆栈空间
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  	;中断模式堆栈空间
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  	;快速中断模式堆栈空间
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  	;中止义模式堆栈空间
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4 	 ;未定义模式堆栈


        AREA    Heap, DATA, NOINIT
bottom_of_heap    SPACE   1

        AREA    Stacks, DATA, NOINIT
StackUsr

    END


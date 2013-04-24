
;�����ջ�Ĵ�С
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


;������ⲿ�����������
    IMPORT  FIQ_Exception                   ;�����ж��쳣�������
    IMPORT  __main                          ;C������������� 
    IMPORT  TargetResetInit                 ;Ŀ��������ʼ��


;���ⲿʹ�õı����������
    EXPORT  bottom_of_heap
    EXPORT  StackUsr
    
    EXPORT  Reset
    EXPORT __user_initial_stackheap

    CODE32
    PRESERVE8
    AREA    vectors,CODE,READONLY
        ENTRY


;�ж�������
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

;���ù���ģʽ��ջ
        MSR     CPSR_c, #0xd3		
        LDR     SP, StackSvc	

;�����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq

;���ÿ����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq

;������ֹģʽ��ջ
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt

;����δ����ģʽ��ջ
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd

;����ϵͳģʽ��ջ
        MSR     CPSR_c, #0x5f
        LDR     SP, =StackUsr

        MOV     PC, R0



ResetInit
        
        BL      InitStack               ;��ʼ����ջ
        BL      TargetResetInit         ;Ŀ��������ʼ��
                                        ;��ת��c������� 
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


    
;/* �����ջ�ռ� */
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4 	 ;����ģʽ��ջ�ռ�
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  	;�ж�ģʽ��ջ�ռ�
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  	;�����ж�ģʽ��ջ�ռ�
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  	;��ֹ��ģʽ��ջ�ռ�
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4 	 ;δ����ģʽ��ջ


        AREA    Heap, DATA, NOINIT
bottom_of_heap    SPACE   1

        AREA    Stacks, DATA, NOINIT
StackUsr

    END


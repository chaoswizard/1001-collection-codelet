NoInt       EQU 0x80

USR32Mode   EQU   0x10
SVC32Mode   EQU   0x13
SYS32Mode    EQU   0x1f
IRQ32Mode     EQU   0x12
FIQ32Mode      EQU  0x11

    CODE32
    PRESERVE8
    AREA    IRQ,CODE,READONLY

    MACRO
$IRQ_Label HANDLER $IRQ_Exception_Function

        EXPORT  $IRQ_Label                                ; ����ı��
        IMPORT  $IRQ_Exception_Function         ; ���õ��ⲿ���

$IRQ_Label
        SUB     LR, LR, #4                               ; ���㷵�ص�ַ
        STMFD   SP!, {R0-R3, R12, LR}       ;  �������񻷾�
        MRS     R3, SPSR                               ;����״̬
        STMFD   SP, {R3,LR}^                        ; ����SPSR���û�״̬��SP,ע�ⲻ�ܻ�д
                                               		 ; �����д�����û���SP�����Ժ���Ҫ����SP
        NOP
        SUB     SP, SP, #4*2

        MSR     CPSR_c, #(NoInt | SYS32Mode)    ; �л���ϵͳģʽ 
       
        BL      $IRQ_Exception_Function         ; ����c���Ե��жϴ������

        MSR     CPSR_c, #(NoInt | IRQ32Mode)    ; �л���irqģʽ
        LDMFD   SP, {R3,LR}^                        ; �ָ�SPSR���û�״̬��SP,ע�ⲻ�ܻ�д
                                               		 ;�����д�����û���SP�����Ժ���Ҫ����SP
        MSR     SPSR_cxsf, R3
        ADD     SP, SP, #4*2                    ; 

        LDMFD   SP!, {R0-R3, R12, PC}^          ;
    MEND



;/* ��������жϾ�����û�����ʵ������ı� */


;Timer0_Handler  HANDLER Timer0

    END


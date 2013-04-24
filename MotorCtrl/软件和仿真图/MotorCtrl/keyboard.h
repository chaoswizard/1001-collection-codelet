
#ifndef  KEYDRV_H
#define  KEYDRV_H  


#define  KEYBOARD_ROW		4						
#define  KEYBOARD_COLUMN	4

extern void  Keyboard_Initialize(void);
extern uint8 Keyboard_Scan(void);
void	Keyboard_Process(void);

#endif

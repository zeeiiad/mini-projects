/*********************************************************
 * File Name:   MY_Common_Macros.h
 * Description: Header File for my common macros
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#ifndef MY_COMMON_MACROS_H_
#define MY_COMMON_MACROS_H_

/* Set a certain bit at any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit at any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit at any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* check if a specific bit is set at any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* check if a specific bit is clear at any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT )

#endif

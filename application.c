/* 
 * File:   application.c
 * Author: Abdallah Saad
* Created on August 7, 2022, 10:39 PM
 */

#include "application.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"


#define CHECK_ADD_TO_SET 0x3FF 
#define EEPROM_LOCATION0 0x00
#define EEPROM_LOCATION1 0x01
#define EEPROM_LOCATION2 0x02
#define EEPROM_LOCATION3 0x03

uint8 CheckValue ; 
uint8 key1 ,key2 ,key3 ,key4 , key5 ,key6 ,key7 ,key8   , flag = 0 ; 
int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    ret = Data_EEPROM_ReadByte( CHECK_ADD_TO_SET ,&CheckValue) ; 
    if(CheckValue == 0xFF){
       ret = lcd_8bit_send_string_pos(&lcd_1 , 2, 1 , "Set Pass : ") ; 
       ret =keypad_get_value_blocking(&keypad1 , &key1) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 12 , key1 ) ; 
       __delay_ms(300) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 12 , '*') ; 
       ret =keypad_get_value_blocking(&keypad1 , &key2) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 13 , key2 ) ; 
       __delay_ms(300) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 13 , '*') ; 
       ret =keypad_get_value_blocking(&keypad1 , &key3) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 14 , key3 ) ; 
       __delay_ms(300) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 14 , '*') ; 
       ret =keypad_get_value_blocking(&keypad1 , &key4) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 15 , key4 ) ; 
       __delay_ms(300) ; 
       ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 15 , '*') ; 
       __delay_ms(300) ; 


       ret = Data_EEPROM_WriteByte(EEPROM_LOCATION0 , key1) ; 
       ret = Data_EEPROM_WriteByte(EEPROM_LOCATION1 , key2) ; 
       ret = Data_EEPROM_WriteByte(EEPROM_LOCATION2 , key3) ; 
       ret = Data_EEPROM_WriteByte(EEPROM_LOCATION3 , key4) ; 
       ret = lcd_8bit_send_command(&lcd_1  , _LCD_CLEAR) ; 
       ret = Data_EEPROM_WriteByte(CHECK_ADD_TO_SET , 0) ; 
    }
    ret = Data_EEPROM_ReadByte( CHECK_ADD_TO_SET ,&CheckValue) ; 
    if (CheckValue == 0x00){


        for(uint8 i = 0 ; i<3 ; i++){
            ret = lcd_8bit_send_command(&lcd_1  , _LCD_CLEAR) ; 
            ret = lcd_8bit_send_string_pos(&lcd_1 , 2, 1 , "Check Pass : ") ; 
            ret =keypad_get_value_blocking(&keypad1 , &key5) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 14 , key5 ) ; 
            __delay_ms(300) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 14 , '*') ; 
            ret =keypad_get_value_blocking(&keypad1 , &key6) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 15 , key6 ) ; 
            __delay_ms(300) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 15 , '*') ; 
            ret =keypad_get_value_blocking(&keypad1 , &key7) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 16 , key7 ) ; 
            __delay_ms(300) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 16 , '*') ; 
            ret =keypad_get_value_blocking(&keypad1 , &key8) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 17 , key8 ) ; 
            __delay_ms(300) ; 
            ret = lcd_8bit_send_char_data_pos(&lcd_1 , 2, 17 , '*') ; 
            __delay_ms(300) ; 

            ret = Data_EEPROM_ReadByte(EEPROM_LOCATION0 , &key1) ; 
            ret = Data_EEPROM_ReadByte(EEPROM_LOCATION1 , &key2) ; 
            ret = Data_EEPROM_ReadByte(EEPROM_LOCATION2 , &key3) ; 
            ret = Data_EEPROM_ReadByte(EEPROM_LOCATION3 , &key4) ; 
            if((key5 == key1) && (key6 == key2) &&(key7 == key3) &&(key8 == key4)){
                ret = lcd_8bit_send_command(&lcd_1  , _LCD_CLEAR) ; 
                ret = lcd_8bit_send_string_pos(&lcd_1 , 2, 2 ," The safe is opened") ;
                ret = lcd_8bit_send_string_pos(&lcd_1 , 3, 7 ," Welcome ") ;
                ret = led_turn_on(&led1) ; 
                __delay_ms(1500) ; 
                ret = led_turn_off(&led1) ; 
                break ; 
            }
            else if( i < 2){
                ret = lcd_8bit_send_command(&lcd_1  , _LCD_CLEAR) ; 
                ret = lcd_8bit_send_string_pos(&lcd_1 , 2, 1 ," Please try again ") ;
                ret = led_turn_on(&led2) ; 
                __delay_ms(800) ; 
                ret = led_turn_off(&led2) ; 

            }
            else if (i == 2){
                ret = lcd_8bit_send_command(&lcd_1  , _LCD_CLEAR) ; 
                ret = lcd_8bit_send_string_pos(&lcd_1 , 2, 2 ," The safe is closed") ;
                ret = lcd_8bit_send_string_pos(&lcd_1 , 3, 7 ," Sorry ") ;
                
            }
        }
             
    }

    while(1){

        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize() ; 
    
}





import sys
import time
import telepot
import serial
from telepot.namedtuple import ReplyKeyboardMarkup, KeyboardButton
from telepot.namedtuple import ReplyKeyboardMarkup, KeyboardButton, ReplyKeyboardRemove
from telepot.namedtuple import InlineKeyboardMarkup, InlineKeyboardButton

try:
    #Conexió amb el port d'arduino
    ser  = serial.Serial('/dev/cu.usbmodem1421', 9600)
    bot = telepot.Bot("<TOKEN>"). # Replace instead with your generated TOKEN
    bot.message_loop (handle)  
    
    print('Esperant ordres ...')                        
    
    while 1:
        time.sleep (20)

except:
    print('PORT [/dev/cu.usbmodem1421] no disponible')




def handle(msg):
    userName = msg['from']['first_name']
    content_type, chat_type, chat_id = telepot.glance(msg)
    print('Chat Message:', content_type, chat_type, chat_id)


    if (content_type == 'text'):
        command = msg ['text']
        print ('Comando Obtenido: %s' % command)

# Iniciació
        if '/start' in command:
            bot.sendMessage (chat_id, "Hola, " + userName + "\n" + "Soc el teu bot, per poder controlar la casa has d'escriure Menú, /start/, o :" + "\n"
                                             + "a) Entrada" + "\n"
                                             + "b) Passadís" + "\n"
                                             + "c) Menjador" + "\n"
                                             + "d) Habitació 1" + "\n"
                                             + "e) Habitació 2" + "\n"
                                             + "f) Sensors")


# Buttons Menú
        if 'Menú' or 'menú' in command:
            bot.sendMessage(chat_id, 'Menú obert, Sr. ' + userName + " 😁",
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                     [KeyboardButton(text="Entrada"), KeyboardButton(text="Passadís")], 
                                     [KeyboardButton(text="Menjador"), KeyboardButton(text="Sensors")],
                                     [KeyboardButton(text="Habitació 1"), KeyboardButton(text="Habitació 2")],
                                ]
                            ))

# Buttons Entrada
        if 'Entrada' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Portes Entrada"), KeyboardButton(text="Llums Entrada")]
                                ]
                            ))

        if 'Portes Entrada' in command:
                bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Porta Entrada"), KeyboardButton(text="Porta Garatge")]
                                ]
                            ))

        if 'Porta Entrada' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Obrir Porta"), KeyboardButton(text="Tancar Porta")]
                                ]
                            ))

        if 'Obrir Porta' in command:
                ser.write (b'A')
                bot.sendMessage (chat_id, "Porta Oberta!")

        if 'Tancar Porta' in command:
                ser.write (b'B')
                bot.sendMessage (chat_id, "Porta Tancada!")                       


        if 'Porta Garatge' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Obrir Porta Garatge")], 
                                    [KeyboardButton(text="Tancar Porta Garatge")]
                                ]
                            )) 

        if 'Obrir Porta Garatge' in command:
                ser.write (b'C')
                bot.sendMessage (chat_id, "Porta Oberta!")   
        
        if 'Tancar Porta Garatge' in command:
                ser.write (b'D')
                bot.sendMessage (chat_id, "Porta Tancada!")   


        if 'Llums Entrada' in command:
                bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Encendre Llums Entrada")], 
                                    [KeyboardButton(text="Apagar Llums Entrada")]
                                ]
                            )) 

        if 'Encendre Llums Entrada' in command:
                ser.write (b'E')
                bot.sendMessage (chat_id, "Llums Encesos!")   
        
        if 'Apagar Llums Entrada' in command:
                ser.write (b'F')
                bot.sendMessage (chat_id, "Llums Apagats!")
        


# Buttons Passadís 

        if 'Passadís' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Llums Passadís"), KeyboardButton(text="Persiana Passadís")]
                                ]
                            ))

    #Llums Passadís

        if 'Llums Passadís' in command:
                bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Encendre Llums Passadís")], 
                                    [KeyboardButton(text="Apagar Llums Passadís")]
                                ]
                            ))


        if 'Encendre Llums Passadís' in command:
                ser.write (b'G')
                bot.sendMessage (chat_id, "Llums Encesos!")
        
        if 'Apagar Llums Passadís' in command:
                ser.write (b'H')
                bot.sendMessage (chat_id, "Llums Apagats!")

    #Persiana Passadís

        if 'Persiana Passadís' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Pujar Persiana Passadís")], 
                                    [KeyboardButton(text="Baixar Persiana Passadís")]
                                ]
                            ))

        if 'Pujar Persiana Passadís' in command:
                ser.write (b'I')
                bot.sendMessage (chat_id, "Persiana Pujada!") 
        
        if 'Baixar Persiana Passadís' in command:
                ser.write (b'J')
                bot.sendMessage (chat_id, "Persiana Baixada!") 
        



# Buttons Menjador 

        if 'Menjador' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Llums Menjador"), KeyboardButton(text="Persianes Menjador")]
                                ]
                            ))

    #Llums Menjador

        if 'Llums Menjador' in command:
                bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Encendre Llums Menjador")], 
                                    [KeyboardButton(text="Apagar Llums Menjador")]
                                ]
                            ))


        if 'Encendre Llums Menjador' in command:
                ser.write (b'K')
                bot.sendMessage (chat_id, "Llums Encesos!")
        
        if 'Apagar Llums Menjador' in command:
                ser.write (b'L')
                bot.sendMessage (chat_id, "Llums Apagats!")

    #Persianes Menjador

        if 'Persianes Menjador' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Pujar Persianes Menjador")], 
                                    [KeyboardButton(text="Baixar Persianes Menjador")]
                                ]
                            ))

        if 'Pujar Persianes Menjador' in command:
                ser.write (b'M')
                bot.sendMessage (chat_id, "Persianes Pujades!") 
        
        if 'Baixar Persianes Menjador' in command:
                ser.write (b'N')
                bot.sendMessage (chat_id, "Persianes Baixades!")



#Buttons Habitació 1

        if 'Habitació 1' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Llums Habitació 1"), KeyboardButton(text="Persianes Habitació 1")]
                                ]
                            ))

    #Llums Habitació 1

        if 'Llums Habitació 1' in command:
                bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Encendre Llums Habitació 1")], 
                                    [KeyboardButton(text="Apagar Llums Habitació 1")]
                                ]
                            ))


        if 'Encendre Llums Habitació 1' in command:
                ser.write (b'O')
                bot.sendMessage (chat_id, "Llums Encesos!")
        
        if 'Apagar Llums Habitació 1' in command:
                ser.write (b'P')
                bot.sendMessage (chat_id, "Llums Apagats!")

    #Persianes Habitació 1

        if 'Persianes Habitació 1' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Pujar Persianes Habitació 1")], 
                                    [KeyboardButton(text="Baixar Persianes Habitació 1")]
                                ]
                            ))

        if 'Pujar Persianes Habitació 1' in command:
                ser.write (b'Q')
                bot.sendMessage (chat_id, "Persianes Pujades!") 
        
        if 'Baixar Persianes Habitació 1' in command:
                ser.write (b'R')
                bot.sendMessage (chat_id, "Persianes Baixades!")



#Buttons Habitació 2

        if 'Habitació 2' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Llums Habitació 2"), KeyboardButton(text="Persianes Habitació 2")]
                                ]
                            ))

    #Llums Habitació 2

        if 'Llums Habitació 2' in command:
                bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Encendre Llums Habitació 2")], 
                                    [KeyboardButton(text="Apagar Llums Habitació 2")]
                                ]
                            ))


        if 'Encendre Llums Habitació 2' in command:
                ser.write (b'S')
                bot.sendMessage (chat_id, "Llums Encesos!")
        
        if 'Apagar Llums Habitació 2' in command:
                ser.write (b'T')
                bot.sendMessage (chat_id, "Llums Apagats!")

    #Persianes Menjador

        if 'Persianes Habitació 2' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Pujar Persianes Habitació 2")], 
                                    [KeyboardButton(text="Baixar Persianes Habitació 2")]
                                ]
                            ))

        if 'Pujar Persianes Habitació 2' in command:
                ser.write (b'U')
                bot.sendMessage (chat_id, "Persianes Pujades!") 
        
        if 'Baixar Persianes Habitació 2' in command:
                ser.write (b'V')
                bot.sendMessage (chat_id, "Persianes Baixades!")



        if 'Sensors' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                            reply_markup=ReplyKeyboardMarkup(
                                keyboard=[
                                    [KeyboardButton(text="Temperatura"), KeyboardButton(text="Humitat")]
                                ]
                            ))
                            
        # -------------- DHT11 -------------- #
        elif 'Temperatura' in command:
                ser.write (b'W')
                temperatura  = ser.readline()
                bot.sendMessage (chat_id, temperatura)

        elif 'Humitat' in command:
                ser.write (b'X')
                temperatura  = ser.readline()
                bot.sendMessage (chat_id, temperatura)


        # -------------- PIR_Alarma -------------- #
        if 'Alarma' in command:
            bot.sendMessage(chat_id, 'Esperant...',
                reply_markup=ReplyKeyboardMarkup(
                    keyboard=[
                        [KeyboardButton(text="Activar Alarma")], 
                        [KeyboardButton(text="Desactivar Alarma")]
                    ]
                ))
        
        if 'Activar Alarma' in command:
            ser.write(b'1')
            bot.sendMessage (chat_id, "Alarma Activada!")
         
        if 'Desactivar Alarma' in command:
            ser.write(b'2')
            bot.sendMessage (chat_id, "Alarma Desactivada!")   
            
            
        # -------------- MODE ECO, func(LDR) -------------- #
        if 'Mode ECO' in command:
            bot.sendMessage(chat_id, 'Esperant...',
            reply_markup=ReplyKeyboardMarkup(
                keyboard=[
                    [KeyboardButton(text="Activar Mode ECO")], 
                    [KeyboardButton(text="Desactivar Mode ECO")]
                ]
            ))
            
        if 'Activar Mode ECO' in command:
            ser.write(b'Y')
            bot.sendMessage (chat_id, "Mode ECO, Activat!")
         
        if 'Desactivar Alarma' in command:
            ser.write(b'Z')
            bot.sendMessage (chat_id, "Mode ECO, Desactivat!")   

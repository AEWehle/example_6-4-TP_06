/*
se esta usando spi
los pines que se usan en la placa son

#define SPI1_MOSI PA_7
#define SPI1_MISO PA_6
#define SPI1_SCK  PA_5
#define SPI1_CS   PD_14

clases
DigitalOut spiSt7920ChipSelect(SPI1_CS);
SPI spiSt7920(SPI1_MOSI, SPI1_MISO, SPI1_SCK); esta clase se le asigna un valor a los 
miso mosi ss y clk


en display init se inicializa asi
    if( display.connection == DISPLAY_CONNECTION_SPI) {
        spiSt7920.format( 8, 3 );
        spiSt7920.frequency( 1000000 );
    }   

 y despues

case DISPLAY_CONNECTION_SPI:
    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                        DISPLAY_IR_FUNCTION_SET | 
                        DISPLAY_IR_FUNCTION_SET_8BITS | 
                        DISPLAY_IR_FUNCTION_SET_2LINES |
                        DISPLAY_IR_FUNCTION_SET_5x8DOTS );
    delay( 1 );         
break;


en la private funcion static void displayCodeWrite( bool type, uint8_t dataBus )
se unsa lock y unlock, es para que el sistema no tome propiedad de esas 
variables mientras estan bloqueadas
esto lo hace parab el objeto spist7920, ya que tiene que cargar los datos a mandar
            spiSt7920.lock();
            spiSt7920ChipSelect = ON;
            if ( type == DISPLAY_RS_INSTRUCTION )           
                spiSt7920.write( ST7920_SPI_SYNCHRONIZING_BIT_STRING |
                                  ST7920_SPI_RW_WRITE |
                                  ST7920_SPI_RS_INSTRUCTION );                              
                else
                spiSt7920.write( ST7920_SPI_SYNCHRONIZING_BIT_STRING |
                                  ST7920_SPI_RW_WRITE |
                                  ST7920_SPI_RS_DATA );               
            spiSt7920.write( dataBus & 0b11110000 );      
            spiSt7920.write( (dataBus<<4) & 0b11110000 );
            spiSt7920ChipSelect = OFF;
            spiSt7920.unlock();

las funciones displayPinWrite( uint8_t pinName, int value ) y  displayDataBusWrite( uint8_t dataBus )
no hace nada en el caso de spi ya que la trama se manda directamente



*/

//=====[Libraries]=============================================================

#include "smart_home_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    smartHomeSystemInit();
    while (true) {
        smartHomeSystemUpdate();
    }
}
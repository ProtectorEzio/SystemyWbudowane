// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
 
// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)
 
// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
 
// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
 
// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
 
// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)
 
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
 
// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)
 
// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
 
// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
 
// CONFIG7H
#pragma config EBTRB = OFF
 
#include <xc.h>
 
#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD
 
#define L_ON    0x0F
#define L_OFF   0x08
#define L_CLR   0x01
#define L_L1    0x80
#define L_L2    0xC0
#define L_CR    0x0F      
#define L_NCR   0x0C  
 
#define L_CFG   0x38
 
void delay(unsigned int ms)
{
    unsigned int i;
    unsigned char j;
   
 for (i =0; i< ms; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
      Nop();
      Nop();
      Nop();
      Nop();
      Nop();
   }
 }
}
 
 
unsigned int adc(unsigned char kanal)
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1
        case 1: ADCON0=0x05; break; //P2
        case 2: ADCON0=0x09; break;
    }
   
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);
 
   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}
 
unsigned char IntToGray(unsigned char input){
    return input ^ (input >> 1);
}
 
void lcd_wr(unsigned char val)
{
  LPORT=val;
}
 
void lcd_cmd(unsigned char val)
{
    LENA=1;
        lcd_wr(val);
        LDAT=0;
        //delay(3);
        LENA=0;
        //delay(3);
    LENA=1;
}
 
void lcd_dat(unsigned char val)
{
    LENA=1;
        lcd_wr(val);
        LDAT=1;
        //delay(3);
        LENA=0;
        //delay(3);
    LENA=1;
}
 
void lcd_init(void)
{
    LENA=0;
    LDAT=0;
    delay(20);
    LENA=1;
   
    lcd_cmd(L_CFG);
    delay(5);
    lcd_cmd(L_CFG);
        delay(1);
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L_OFF);
    lcd_cmd(L_ON); //liga
    lcd_cmd(L_CLR); //limpa
    lcd_cmd(L_CFG); //configura
        lcd_cmd(L_L1);
}
 
void lcd_str(const char* str)
{
 unsigned char i=0;
 
 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }  
}
 
 
 
void main(void) {
   
    //Inicjalizacja konwertera analogowo cyfrowego
    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;
   
    TRISA=0xC3;
    TRISB=0x3F;  
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;
   
    lcd_init(); //Inicjalizacja wyswietlacza
    lcd_cmd(L_CLR);
   
    char x;//zmienna s?u??ca do zmian wartosci w tekst2
    char* tekst1="Gracz 1||Gracz 2";//tekst wyswietlany na ekranie w 1 linii
    char* tekst2="   0:00||   0:00";//tekst wyswietlany na ekranie w 2 linii
                //0123456789012345
    unsigned char gracz='1';//nr gracza który zaczyna
    unsigned char praca=0;//stan pracy zegara
    unsigned int tmp = 0;//zmienna wychwytuj?ca wartosc potencjometru
    while(1)
    {
        if(praca==1)
        {
            delay(1000);
        }
        else delay(200);
        if(PORTBbits.RB3==0)//jezeli wcisniety zostal przycisk RB3
        {
            gracz='1';//ustawiamy gracza 1, jako obecnie rozgrywaj?cego
        }
        if(PORTBbits.RB5==0)//jezeli wcisniety zostal przycisk RB5
        {
            gracz='2';//ustawiamy gracz 2, jako obecnie rozgrywaj?cego
        }
        if(PORTBbits.RB2==0)//jezeli wcisniety zostal przycisk RB2
        {
            praca=1;//ustawiamy stan pracy na 1
        }
        if(PORTBbits.RB1==0)//jezeli wcisniety zostal przycisk RB1
        {//resetujemy poniasze wartosci do stanu przed rozpocz?ciem rozgrywki
           tekst2[3]='0';//1 min gracz1
           tekst2[5]='0';//10 sek gracz1
           tekst2[6]='0';//1 sek gracz1
           tekst2[12]='0';//1 min gracz2
           tekst2[14]='0';//10 sek gracz2
           tekst2[15]='0';//1 sek gracz2
           gracz='1';
           praca=0;
        }
        if(praca==0)//jezeli stan pracy ustawiony jest na 0
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
            lcd_str(tekst1); //wyswietlenie tekst1 w 1 linii ekranu
                   //0123456789012345
            lcd_cmd(L_L2); //Przejscie do drugiej linii
            lcd_str(tekst2);//wyswietlenie tekst2 w 2 linii ekranu
                   //0123456789012345
            tmp=((unsigned int)adc(1) / 10);//przypisanie wartosci potencjometru do zmiennej tmp
       
            if(tmp<=33)//jezeli wartosc potencjometru jest ni?sza lub równa 33 ustawiamy czas obu graczy na 5 min
            {
                tekst2[3]='5';
                tekst2[12]='5';
            }
            else if(tmp>=34 & tmp<=66)//jezeli wartosc potencjometru jest wyssza lub równa 34 i ni?sza lub równa 66 ustawiamy czas obu graczy na 3 min
            {
                tekst2[3]='3';
                tekst2[12]='3';
            }
            else if(tmp>=67)//jezeli wartosc potencjometru jest wyssza lub równa 67 ustawiamy czas obu graczy na 1 min
            {
                tekst2[3]='1';
                tekst2[12]='1';
            }
        }
        if(praca==1)//jezeli stan pracy jest równy 1 zegar jest aktywny i odlicza
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej liniiw
            lcd_str(tekst1); //napis 16 znaków
            lcd_cmd(L_L2); //Przejscie do drugiej linii
            lcd_str(tekst2);
            if(tekst2[3]=='0' & tekst2[5]=='0' & tekst2[6]=='0')
            {//warunek wygrania gracza 2
                praca=2;//wygrywa gracz 2
            }
            if(tekst2[12]=='0' & tekst2[14]=='0' & tekst2[15]=='0')
            {//warunek wygrania gracza 1
                praca=3;//wygrywa gracz 1
            }
            if(gracz=='1')//jezeli rozgrywa gracz 1
            {
                x=tekst2[6];//pobieramy wartosc sekund z tablicy
                x-=1;//zmniejszamy ta wartosc o 1
                tekst2[6]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                if(tekst2[6]<'0')
                {//jezeli wartosc sekund jest mniejsza od 0
                    x=tekst2[5];//pobieramy wartosc "dziesiatek" sekund z tablicy
                    x-=1;//zmniejszamy ta wartosc o 1
                    tekst2[5]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                    tekst2[6]='9';//zmieniamy wartosc sekund na 9
                }
                if(tekst2[6]<'0' & tekst2[3]!='0')
                {//jezeli wartosc sekund jest mniejsza od 0 i wartosc minut nie jest równa 0
                    x=tekst2[5];//pobieramy wartosc "dziesiatek" sekund z tablicy
                    x-=1;//zmniejszamy ta wartosc o 1
                    tekst2[5]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                    tekst2[6]='9';//zmieniamy wartosc sekund na 9
                }
                if(tekst2[5]<'0' & tekst2[3]!='0')
                {//jezeli wartosc "dziesiatek" sekund jest mniejsza od 0 i wartosc minut nie jest równa 0
                    x=tekst2[3];//pobieramy wartosc minut z tablicy)
                    x-=1;//zmniejszamy ta wartosc o 1
                    tekst2[3]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                    tekst2[5]='5';//zmieniamy wartosc "dziesiatek" sekund na 5
                    tekst2[6]='9';//zmieniamy wartosc sekund na 9
                }
            }
            if(gracz=='2')//jezeli rozgrywa gracz 2
            {
                x=tekst2[15];//pobieramy wartosc sekund z tablicy
                x-=1;//zmniejszamy ta wartosc o 1
                tekst2[15]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                if(tekst2[15]<'0')
                {//jezeli wartosc sekund jest mniejsza od 0
                    x=tekst2[14];//pobieramy wartosc "dziesiatek" sekund z tablicy
                    x-=1;//zmniejszamy ta wartosc o 1
                    tekst2[14]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                    tekst2[15]='9';//zmieniamy wartosc sekund na 9
                }
                if(tekst2[15]<'0' & tekst2[12]!='0')
                {//jezeli wartosc sekund jest mniejsza od 0 i wartosc minut nie jest równa 0
                    x=tekst2[12];//pobieramy wartosc "dziesiatek" sekund z tablicy
                    x-=1;//zmniejszamy ta wartosc o 1
                    tekst2[14]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                    tekst2[15]='9';//zmieniamy wartosc sekund na 9
                }
                if(tekst2[14]<'0' & tekst2[12]!='0')
                {//jezeli wartosc "dziesiatek" sekund jest mniejsza od 0 i wartosc minut nie jest równa 0
                    x=tekst2[12];//pobieramy wartosc minut z tablicy)
                    x-=1;//zmniejszamy ta wartosc o 1
                    tekst2[12]=x;//umieszczamy zmienion? wartosc spowrotem w tablicy
                    tekst2[14]='5';//zmieniamy wartosc "dziesiatek" sekund na 5
                    tekst2[15]='9';//zmieniamy wartosc sekund na 9
                }
            }
        }
        if(praca==2)//jezeli stan pracy jest równy 2 wygrywa gracz 2
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
            lcd_str("!!!  Wygral  !!!"); //napis
                   //0123456789012345
            lcd_cmd(L_L2); //Przejscie do drugiej linii
            lcd_str("!!  Gracz  2  !!");
                   //0123456789012345
        }
        if(praca==3)//jezeli stan pracy jest równy 3 wygrywa gracz 1
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
            lcd_str("!!!  Wygral  !!!"); //napis
                   //0123456789012345
            lcd_cmd(L_L2); //Przejscie do drugiej linii
            lcd_str("!!  Gracz  1  !!");
                   //0123456789012345
        }
    }
    return;
}
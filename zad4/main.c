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
   
    char x;//zmienna s?u??ca do zmian wartosci w tekst2 na którejs z pozycji
    unsigned char i=1;//zmienna pomagajaca w zmianie ustawienia mocy
    unsigned char praca=0;//zmienna okreslajaca stan pracy mikrofalówki
    char* tekst1="Moc         Czas";//zmienna przedstawiajaca pierwsza linijke na ekranie
    char* tekst2="800W      00m00s";//zmienna przedstawiajaca druga linijke na ekanie
                //0123456789012345
    lcd_init(); //Inicjalizacja wyswietlacza
    lcd_cmd(L_CLR); //Czyszczenie wyswietlacza
   
    while(1)//petla nieskonczona
    {
        if(praca==1)//jezeli stan pracy jest równy 1
        {
            delay(1000);//opóznienie 1s
        }
        else//w przeciwnym wypadku
        {
            delay(500);//opóznienie 0,5s
        }
        if(PORTBbits.RB2==0)//jezeli zostal wcisniety przycisk RB2
        {
            praca++;//zmieniamy stan pracy na wyzszy o 1
            if(praca>2)//jezeli stan pracy jest wiekszy niz 2 zmieniamy go na 1
            {
                praca=1;
            }
        }
        if(PORTBbits.RB1==0)//jezeli zostal wcisniety przycisk RB1
        {//pod tym warunkiem resetujemy wszystkie wartosci mikrofalówki do stanu poczatkowego
         //oraz resetujemy stan pracy mikrofalówki
           i=1;
           tekst2[10]='0';//10 min
           tekst2[11]='0';//1 min
           tekst2[13]='0';//10 sek
           tekst2[14]='0';//1 sek
           tekst2[0]='8';
           tekst2[1]='0';
           praca=0;
        }
        if(praca==1)//stan pracy == Mikrofalówka pracuje, "podgrzewa danie"
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej liniiw
            lcd_str(tekst1); //wyswietlenie warto?ci tekst1
            lcd_cmd(L_L2); //Przej??ie do drugiej linii
            lcd_str(tekst2);//wyswietlenie warto?ci tekst2
            if(tekst2[10]=='0' & tekst2[11]=='0' & tekst2[13]=='0' & tekst2[14]=='0')
            {//jezeli wszystkie wartosci czasu sa równe 0 zmieniamy stan pracy na 3
                praca=3;//stan pracy == Mikrofalówka zakonczyla prace
            }
            x=tekst2[14];//przypisanie obecnej wartosci(wartosc reprezentujaca sekundy) z tablicy do x
            x-=1;//zmniejszenie tej wartosci o 1
            tekst2[14]=x;//wstawienie zmienionej wartosci w to samo miejsce w tablicy
            if(tekst2[14]<'0')
            {//Jezeli wartosc sekund jest mniejsza niz 0
                x=tekst2[13];//pobieramy obecna wartosc "dziesiatek" sekund do zmiennej x
                x-=1;//zmniejszenie tej wartosci
                tekst2[13]=x;//wstawienie zmienionej wartosci w to samo miejsce w tablicy
                tekst2[14]='9';//zmieniamy wartosc sekund na 9
            }
            if(tekst2[14]<'0' & tekst2[11]!='0')
            {//jezeli watrosc sekund jest mniejsza niz 0 oraz wartosc minut nie jest równa 0
                x=tekst2[13];//pobieramy obecna wartosc "dziesiatek" sekund do zmiennej x
                x-=1;//zmniejszenie tej wartosci
                tekst2[13]=x;//wstawienie zmienionej wartosci w to samo miejsce w tablicy
                tekst2[14]='9';//zmieniamy wartosc sekund na 9
            }
            if(tekst2[13]<'0' & tekst2[11]!='0')
            {//jezeli watrosc "dziesiatek" sekund jest mniejsza niz 0 oraz wartosc minut nie jest równa 0
                x=tekst2[11];//pobieramy obecna wartosc minut do zmiennej x
                x-=1;//zmniejszenie tej wartosci
                tekst2[11]=x;//wstawienie zmienionej wartosci w to samo miejsce w tablicy
                tekst2[13]='5';//zmieniamy wartosc "dziesiatek" sekund na 5
                tekst2[14]='9';//zmieniamy wartosc sekund na 9
            }
            if(tekst2[11]<'0' & tekst2[10]!='0')
            {
                x=tekst2[10];//pobieramy obecna wartosc "dziesiatek" minut do zmiennej x
                x-=1;//zmniejszenie tej wartosc
                tekst2[10]=x;//wstawienie zmienionej wartosci w to samo miejsce w tablicy
                tekst2[11]='9';//zmieniamy wartosc minut na 9
                tekst2[13]='5';//zmieniamy wartosc "dziesi?tek" sekund na 5
                tekst2[14]='9';//zmieniamy wartocs sekund na 9
            }
        }
        if(praca==0)//stan pracy == Mikrofalówka nie pracuje, wybierz moc i czas "pracy" mikrofalówki
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej liniiw
            lcd_str(tekst1); //wyswietlenie warto?ci tekst1
            lcd_cmd(L_L2); //Przejscie do drugiej linii
            lcd_str(tekst2);//wyswietlenie warto?ci tekst2
            if(PORTBbits.RB5==0)//Jezeli zostanie wcisniety przycisk RB5
            {
                i++;//zwiekszamy wartosc wyznaczajaca moc o 1
                if(i>4)//Jezeli wartosc ta jest wieksza od 4 zmieniamy ja na 1
                {
                    i=1;
                }
            }
            if(i==1)//jezeli zmienna wyznaczajaca poziom mocy jest równa 1
            {//zmieniamy wartosci w tablicy, zeby ekran wskazywal 800
                tekst2[0]='8';
                tekst2[1]='0';
            }
            if(i==2)//jezeli zmienna wyznaczajaca poziom mocy jest równa 2
            {//zmieniamy wartosci w tablicy, zeby ekran wskazywal 600
                tekst2[0]='6';
                tekst2[1]='0';
            }
            if(i==3)//jezeli zmienna wyznaczajaca poziom mocy jest równa 3
            {//zmieniamy wartosci w tablicy, zeby ekran wskazywal 350
                tekst2[0]='3';
                tekst2[1]='5';
            }
            if(i==4)//jezeli zmienna wyznaczajaca poziom mocy jest równa 4
            {//zmieniamy wartosci w tablicy, zeby ekran wskazywal 200
                tekst2[0]='2';
                tekst2[1]='0';
            }
            if(PORTBbits.RB4==0)//Jezeli zostanie wcisniety przycisk RB4
            {
                x=tekst2[11];//pobieramy wartosc minut z tablicy
                x+=1;//zwiekszamy ta wartosc o 1
                tekst2[11]=x;//umieszczamy zmieniona wartosc spowrotem w tablicy
            }
            if(tekst2[11]>'9')//Jezeli wartosc minut jest wieksza od 9
            {
                x=tekst2[10];//pobieramy wartosc "dziesiatek" minut z tablicy
                x+=1;//zwiekszamy ta wartosc o 1
                tekst2[10]=x;//umieszczamy zmieniona wartosc spowrotem w tablicy
                tekst2[11]='0';//zmieniamy wartosc minut na 0
            }
            if(PORTBbits.RB3==0)//Jezeli zostanie wcisniety przycisk RB3
            {
                x=tekst2[13];//pobieramy wartosc "dziesiatek" sekund z tablicy
                x+=1;//zwiekszamy ta wartosc o 1
                tekst2[13]=x;//umieszczamy zmieniona wartosc spowrotem w tablicy
            }
            if(tekst2[13]>'5')//jezeli wartosc "dziesiatek" sekund jest wieksza od 5
            {
                x=tekst2[11];//pobieramy wartosc minut z tablicy
                x+=1;//zwiekszamy ta wartosc o 1
                tekst2[11]=x;//umieszczamy zmieniona wartosc spowrotem w tablicy
                tekst2[13]='0';//zmieniamy wartosc "dziesiatek" sekund na 0
            }
        }
        if(praca==2)//stan pracy == praca mikrofalówki zostala wstrzymana
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
            lcd_str(tekst1);//wyswietlenie wartosci tekst1
            lcd_cmd(L_L2); //Przejscie do drugiej linii
            lcd_str(tekst2);//wyswietlenie wartosci tekst2
        }
        if(praca==3)//stan pracy == Mikrofalówka zakonczyla prace
        {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1); //Ustawienie karetki w pierwszej linii
            lcd_str("!!!  GOTOWE  !!!"); //wyswietlenie wiadomosci o skonczeniu pracy przez mikrofalówke
            lcd_cmd(L_L2); //Przej??ie do drugiej linii
            lcd_str("                ");
        }
    }
   
    return;
}
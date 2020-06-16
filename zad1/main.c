#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//Fukncje podane wczeœniej
int IntToBinary(unsigned char input)
{
    short i = 7;
    while(i>=0)
    {
        printf("%d",(input >> i) & 1);
        i--;
    }

    printf("   ");
}

unsigned char IntToGray(unsigned char input)
{
    return input ^ (input >> 1);
}

unsigned char IntToBCD(unsigned char input)
{
    return ((input / 10) << 4)|(input % 10);
}


unsigned char przesuniecie(unsigned char input, unsigned char ileBitow, char kierunek){
    //Funkcja przesuniêcia wartoœci zmiennej input o wartoœæ podan¹ w zmiennej ileBitów w kierunku podanym w zmiennej kierunek
    return kierunek == 'l' || kierunek == 'L' ? input<<ileBitow : input>>ileBitow;
    //Je¿eli wartoœæ zmiennej kierunek jest równa 'l' lub 'L' zwracamy zmienn¹ input przesuniêt¹ w lewo o okreœlon¹ iloœæ bitów
    //w przeciwnym wypadku, gdy wartoœæ zmiennej kierunek jest inna, zwracamy zmienn¹ input przesuniêt¹ w prawo o okreœlon¹ iloœæ bitów
}

unsigned char nBit(unsigned char input, unsigned char pozycja){
    //Funkcja zwracaj¹ca wartoœæ bitu z pozycji podanej w zmiennej pozycja,
    //bit wyci¹gany jest z wartoœci podanej w zmiennej input
    return (input&(1<<pozycja)) == 0 ? 0 : 1;

}

unsigned char PRNG(unsigned char input){
    unsigned char baza = 0b1110011;//baza generatora PRNG
    char wynik = -1;//zmienna przechowuj¹ca wynik operacji XOR, wartoœæ '-1' oznacza, ¿e w danym momencie zmienna nie przechowuje jeszcze wartoœci
    for(int i=0; i<6; i++)//iteracja ma na celu pomijanie ostatniego bitu
        {
        if(nBit(baza,i) == 0) continue;//Jeœli w bazie generatora wystêpuje 0 pomijamy ten bit i kontynuujemy
        if(wynik == -1) wynik=nBit(input,i);//Jeœli wynik operacji XOR nie przechowuje wartoœci nadajemu mu wartoœæ 1 bitu, jest to wykonywane tylko przy pierwszej iteracji
        else wynik=wynik^nBit(input,i);//Jeœli wynik operacji XOR przechowuje wartoœæ wykonujemy kolejn¹ operacjê XOR z bitem wybranym przez iteracjê
    }
    wynik = przesuniecie(wynik,6,'l');//przesuwamy wynik XOR o 1 pozycjê dalej ni¿ zakres input
    input = input | wynik;//³¹czymy wynik XOR z input na odpowiedniej pozycji
    input = przesuniecie(input,1,'p');//przesuwamy bity zmiennej input w prawo o 1 bit
    return input;//zwracamy wartoœæ input po wykonanych wczeœniej operacjach
}

void Opoznienie()
{
    int c,d = 0;
    for (c = 1; c <= 1.25*32767; c++)
            for (d = 1; d <= 1.25*8192; d++)
            {}
}


void main(void)
{

    unsigned char display = 0;//Zmienna przechowuj¹ca wartoœæ przeznaczon¹ do wyœwietlenia w konsoli
    unsigned char licznik = 0;//Zmienna u¿ywana przez podprogramy w ich operacjach
    unsigned char kierunek = 'L';//Zmienna przechowuj¹ca pocz¹tkowy kierunek poruszania siê wê¿yka w podprogramie 7
    unsigned char kolejka = 1;//Zmienna wykorzystywana w podprogramie 8 do wyœwietlania kolejki w zmiennej display
    unsigned char koniecKolejki = 128;//Zmienna wykorzystywana do okreœlenia, w którym miejscu kolejka koñczy siê przesuwaæ
    int podprogram = 1;//wartoœæ okreœlaj¹ca, który podprogram ma dzia³aæ po odpaleniu programu
    while(1)//Pêtla nieskoñczona, w której dzia³aj¹ podprogramy
    {
        printf("\r");//reset konsoli
        char ch='null';//usuwanie poprzedniej wartoœci wciœniêtego przycisku na klawiaturze
        //w powy¿szej zmiennej bêdziemy przechowywaæ wartoœæ wciœniêtego przycisku
        if(kbhit())//Jeœli zosta³ wciœniêty przycisk na klawiaturze sprawdzamy podwarunki
        {
            ch=getch();//wy³apujemy wartoœæ wciœniêtego przycisku
            if(ch==72)//je¿eli wy³apana wartoœæ to 72 zmieniamy podprogram na podprogram o wartoœci wy¿szej o 1
            {//strza³ka w górê
                podprogram++;
                if(podprogram>9) podprogram=1;//je¿eli wartoœæ podprogramu jest równa 9 zmieniamy t¹ wartoœæ na 1
            }
            else if(ch==80)//je¿eli wy³apana wartoœæ to 80 zmieniamy podprogram na podprogram o wartoœci ni¿szej o 1
            {//strza³ka w dó³
                podprogram--;
                if(podprogram<1) podprogram=9;//je¿eli wartoœæ podprogramu jest równa 1 zmieniamy t¹ wartoœæ na 9
            }
            else//je¿eli wy³apana wartoœæ jest inna ni¿ powy¿sze ignorujemy j¹ i kontynuujemu
            {
                continue;
            }


            if(podprogram==1)
            {
                display=licznik;
                //Przypisanie wartoœci licznik do display
            }
            else if(podprogram==2)
            {
                display=licznik;
                //Przypisanie wartoœci licznik do display
            }
            else if(podprogram==3)
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
            }
            else if(podprogram==4)
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
            }
            else if(podprogram==5)
            {
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
            }
            else if(podprogram==6)
            {
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
            }
            else if(podprogram==7)
            {
                licznik=7;//ustawienie wartoœci pocz¹tkowej wê¿yka
                kierunek='L';//okreœlenie kierunku przesuwania wê¿yka
            }
            if(podprogram==8)
            {
                licznik=0;//zerowanie licznika, przechowuj¹cego kolejki
                kolejka=1;//ustawienie kolejki na najm³odszy bit
                koniecKolejki=0b10000000;//domyœlna d³ugoœæ kolejki
                display=licznik|kolejka;//rzypisanie kolejki do display
            }
            if(podprogram==9)
            {
                licznik=1;//ustawienie wejœcia dla generatora
                display=licznik;////Przypisanie wartoœci licznik do display
            }
        }
        else//je¿eli przycisk na klawiaturze nie by³ wciœniêty program wykonuje poni¿sze operacje
        {
            if(podprogram==1)//kontynuacja podprogramu 1
            {
                display=licznik;
                //Przypisanie wartoœci licznik do display
                licznik++;//zwiêkszenie licznika
            }
            else if(podprogram==2)//kontynuacja podprogramu 2
            {
                display=licznik;
                //Przypisanie wartoœci licznik do display
                licznik--;//zmniejszenie licznika
            }
            else if(podprogram==3)//kontynuacja podprogramu 3
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
                licznik++;//zwiêkszenie licznika
            }
            else if(podprogram==4)//kontynuacja podprogramu 4
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
                licznik--;//zmniejszenie licznika
            }
            else if(podprogram==5)//kontynuacja podprogramu 5
            {
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
                licznik++;//zwiêkszenie licznika
                if(licznik >99) licznik=0;//je¿eli licznik jest wiêkszy ni¿ 99 zmieniamy jego wartoœæ na 0
            }
            else if(podprogram==6)//kontynuacja podprogramu 6
            {
                if(licznik<0) licznik=99;//je¿eli licznik jest mniejszy ni¿ 0 zmieniamy jego wartoœæ na 99
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej wartoœci licznik do display
                licznik--;//zmniejszenie licznika
            }
            else if(podprogram==7)//kontynuacja podprogramu 7
            {
                if(kierunek=='L')//je¿eli kierunek wê¿yka to 'L'
                {
                    display=licznik;
                    //Przypisanie wartoœci licznik do display
                    licznik=licznik<<1;
                    //przesuniêcie bitów wartoœci licznika w lew¹ stronê o 1
                    if(licznik==224) kierunek='P';//je¿eli wartoœæ licznika jest równa 224 zmieniamy kierunek wê¿yka, gdy¿ doszed³ do "lewej œciany"
                }
                else if(kierunek=='P')//je¿eli kierunek wê¿yka to 'P'
                {
                    display=licznik;
                    //Przypisanie wartoœci licznik do display
                    licznik=licznik>>1;
                    //przesuniêcie bitów wartoœci licznika w lew¹ stronê o 1
                    if(licznik==7) kierunek='L';//je¿eli wartoœæ licznika jest równa 224 zmieniamy kierunek wê¿yka, gdy¿ doszed³ do "prawej œciany"
                }
            }
            if(podprogram==8)//kontynuacja podprogramu 8
            {
                if(licznik==255)//warunek przywracaj¹cy kolejkê do stanu pocz¹tkowego
                {
                    licznik=0;//Przywrócenie wartoœci zmiennej do domyœlnej wartoœci
                    kolejka=1;//jak wy¿ej
                    koniecKolejki=128;//jak wy¿ej
                    display = licznik | kolejka;//jak wy¿ej
                    continue;
                }
                kolejka = kolejka << 1;//przesuniêcie bitów kolejki o 1 w lewo
                if(kolejka==0) kolejka=1;//je¿eli wartoœæ kolejki jest równa 0 zmieniamy t¹ wartoœæ na 1
                if(kolejka==koniecKolejki)//je¿eli wartoœæ kolejki jest równa wartoœci koñca kolejki
                {
                    koniecKolejki=koniecKolejki>>1;//przesuniêcie bitów koñca kolejki o 1 w prawo
                    licznik=licznik|kolejka;//wype³nienie licznika po zakoñczeniu podró¿y kolejki
                    kolejka=0;//wartoœæ zerowana, aby zacz¹æ nastêpn¹ kolejkê od najm³odszego bitu
                }
                display=licznik|kolejka;//po³¹czenie stoj¹cych kolejek z podró¿uj¹c¹
            }
            if(podprogram==9)//kontynuacja podprogramu 9
            {
                licznik=PRNG(licznik);//Wygenerowanie nowej wartoœci na podstawie poprzedniego licznika i przypisanie tej wartoœci do licznika
                display=licznik;
                //przypisanie wartoœci licznika do display
            }
        }
        IntToBinary(display);//wyœwietlenie przekonwertowanej wartoœci display
        Opoznienie();
    }
    return 0;
}

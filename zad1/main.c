#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//Fukncje podane wcze�niej
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
    //Funkcja przesuni�cia warto�ci zmiennej input o warto�� podan� w zmiennej ileBit�w w kierunku podanym w zmiennej kierunek
    return kierunek == 'l' || kierunek == 'L' ? input<<ileBitow : input>>ileBitow;
    //Je�eli warto�� zmiennej kierunek jest r�wna 'l' lub 'L' zwracamy zmienn� input przesuni�t� w lewo o okre�lon� ilo�� bit�w
    //w przeciwnym wypadku, gdy warto�� zmiennej kierunek jest inna, zwracamy zmienn� input przesuni�t� w prawo o okre�lon� ilo�� bit�w
}

unsigned char nBit(unsigned char input, unsigned char pozycja){
    //Funkcja zwracaj�ca warto�� bitu z pozycji podanej w zmiennej pozycja,
    //bit wyci�gany jest z warto�ci podanej w zmiennej input
    return (input&(1<<pozycja)) == 0 ? 0 : 1;

}

unsigned char PRNG(unsigned char input){
    unsigned char baza = 0b1110011;//baza generatora PRNG
    char wynik = -1;//zmienna przechowuj�ca wynik operacji XOR, warto�� '-1' oznacza, �e w danym momencie zmienna nie przechowuje jeszcze warto�ci
    for(int i=0; i<6; i++)//iteracja ma na celu pomijanie ostatniego bitu
        {
        if(nBit(baza,i) == 0) continue;//Je�li w bazie generatora wyst�puje 0 pomijamy ten bit i kontynuujemy
        if(wynik == -1) wynik=nBit(input,i);//Je�li wynik operacji XOR nie przechowuje warto�ci nadajemu mu warto�� 1 bitu, jest to wykonywane tylko przy pierwszej iteracji
        else wynik=wynik^nBit(input,i);//Je�li wynik operacji XOR przechowuje warto�� wykonujemy kolejn� operacj� XOR z bitem wybranym przez iteracj�
    }
    wynik = przesuniecie(wynik,6,'l');//przesuwamy wynik XOR o 1 pozycj� dalej ni� zakres input
    input = input | wynik;//��czymy wynik XOR z input na odpowiedniej pozycji
    input = przesuniecie(input,1,'p');//przesuwamy bity zmiennej input w prawo o 1 bit
    return input;//zwracamy warto�� input po wykonanych wcze�niej operacjach
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

    unsigned char display = 0;//Zmienna przechowuj�ca warto�� przeznaczon� do wy�wietlenia w konsoli
    unsigned char licznik = 0;//Zmienna u�ywana przez podprogramy w ich operacjach
    unsigned char kierunek = 'L';//Zmienna przechowuj�ca pocz�tkowy kierunek poruszania si� w�yka w podprogramie 7
    unsigned char kolejka = 1;//Zmienna wykorzystywana w podprogramie 8 do wy�wietlania kolejki w zmiennej display
    unsigned char koniecKolejki = 128;//Zmienna wykorzystywana do okre�lenia, w kt�rym miejscu kolejka ko�czy si� przesuwa�
    int podprogram = 1;//warto�� okre�laj�ca, kt�ry podprogram ma dzia�a� po odpaleniu programu
    while(1)//P�tla niesko�czona, w kt�rej dzia�aj� podprogramy
    {
        printf("\r");//reset konsoli
        char ch='null';//usuwanie poprzedniej warto�ci wci�ni�tego przycisku na klawiaturze
        //w powy�szej zmiennej b�dziemy przechowywa� warto�� wci�ni�tego przycisku
        if(kbhit())//Je�li zosta� wci�ni�ty przycisk na klawiaturze sprawdzamy podwarunki
        {
            ch=getch();//wy�apujemy warto�� wci�ni�tego przycisku
            if(ch==72)//je�eli wy�apana warto�� to 72 zmieniamy podprogram na podprogram o warto�ci wy�szej o 1
            {//strza�ka w g�r�
                podprogram++;
                if(podprogram>9) podprogram=1;//je�eli warto�� podprogramu jest r�wna 9 zmieniamy t� warto�� na 1
            }
            else if(ch==80)//je�eli wy�apana warto�� to 80 zmieniamy podprogram na podprogram o warto�ci ni�szej o 1
            {//strza�ka w d�
                podprogram--;
                if(podprogram<1) podprogram=9;//je�eli warto�� podprogramu jest r�wna 1 zmieniamy t� warto�� na 9
            }
            else//je�eli wy�apana warto�� jest inna ni� powy�sze ignorujemy j� i kontynuujemu
            {
                continue;
            }


            if(podprogram==1)
            {
                display=licznik;
                //Przypisanie warto�ci licznik do display
            }
            else if(podprogram==2)
            {
                display=licznik;
                //Przypisanie warto�ci licznik do display
            }
            else if(podprogram==3)
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
            }
            else if(podprogram==4)
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
            }
            else if(podprogram==5)
            {
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
            }
            else if(podprogram==6)
            {
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
            }
            else if(podprogram==7)
            {
                licznik=7;//ustawienie warto�ci pocz�tkowej w�yka
                kierunek='L';//okre�lenie kierunku przesuwania w�yka
            }
            if(podprogram==8)
            {
                licznik=0;//zerowanie licznika, przechowuj�cego kolejki
                kolejka=1;//ustawienie kolejki na najm�odszy bit
                koniecKolejki=0b10000000;//domy�lna d�ugo�� kolejki
                display=licznik|kolejka;//rzypisanie kolejki do display
            }
            if(podprogram==9)
            {
                licznik=1;//ustawienie wej�cia dla generatora
                display=licznik;////Przypisanie warto�ci licznik do display
            }
        }
        else//je�eli przycisk na klawiaturze nie by� wci�ni�ty program wykonuje poni�sze operacje
        {
            if(podprogram==1)//kontynuacja podprogramu 1
            {
                display=licznik;
                //Przypisanie warto�ci licznik do display
                licznik++;//zwi�kszenie licznika
            }
            else if(podprogram==2)//kontynuacja podprogramu 2
            {
                display=licznik;
                //Przypisanie warto�ci licznik do display
                licznik--;//zmniejszenie licznika
            }
            else if(podprogram==3)//kontynuacja podprogramu 3
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
                licznik++;//zwi�kszenie licznika
            }
            else if(podprogram==4)//kontynuacja podprogramu 4
            {
                display=IntToGray(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
                licznik--;//zmniejszenie licznika
            }
            else if(podprogram==5)//kontynuacja podprogramu 5
            {
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
                licznik++;//zwi�kszenie licznika
                if(licznik >99) licznik=0;//je�eli licznik jest wi�kszy ni� 99 zmieniamy jego warto�� na 0
            }
            else if(podprogram==6)//kontynuacja podprogramu 6
            {
                if(licznik<0) licznik=99;//je�eli licznik jest mniejszy ni� 0 zmieniamy jego warto�� na 99
                display=IntToBCD(licznik);
                //Przypisanie przekonwertowanej warto�ci licznik do display
                licznik--;//zmniejszenie licznika
            }
            else if(podprogram==7)//kontynuacja podprogramu 7
            {
                if(kierunek=='L')//je�eli kierunek w�yka to 'L'
                {
                    display=licznik;
                    //Przypisanie warto�ci licznik do display
                    licznik=licznik<<1;
                    //przesuni�cie bit�w warto�ci licznika w lew� stron� o 1
                    if(licznik==224) kierunek='P';//je�eli warto�� licznika jest r�wna 224 zmieniamy kierunek w�yka, gdy� doszed� do "lewej �ciany"
                }
                else if(kierunek=='P')//je�eli kierunek w�yka to 'P'
                {
                    display=licznik;
                    //Przypisanie warto�ci licznik do display
                    licznik=licznik>>1;
                    //przesuni�cie bit�w warto�ci licznika w lew� stron� o 1
                    if(licznik==7) kierunek='L';//je�eli warto�� licznika jest r�wna 224 zmieniamy kierunek w�yka, gdy� doszed� do "prawej �ciany"
                }
            }
            if(podprogram==8)//kontynuacja podprogramu 8
            {
                if(licznik==255)//warunek przywracaj�cy kolejk� do stanu pocz�tkowego
                {
                    licznik=0;//Przywr�cenie warto�ci zmiennej do domy�lnej warto�ci
                    kolejka=1;//jak wy�ej
                    koniecKolejki=128;//jak wy�ej
                    display = licznik | kolejka;//jak wy�ej
                    continue;
                }
                kolejka = kolejka << 1;//przesuni�cie bit�w kolejki o 1 w lewo
                if(kolejka==0) kolejka=1;//je�eli warto�� kolejki jest r�wna 0 zmieniamy t� warto�� na 1
                if(kolejka==koniecKolejki)//je�eli warto�� kolejki jest r�wna warto�ci ko�ca kolejki
                {
                    koniecKolejki=koniecKolejki>>1;//przesuni�cie bit�w ko�ca kolejki o 1 w prawo
                    licznik=licznik|kolejka;//wype�nienie licznika po zako�czeniu podr�y kolejki
                    kolejka=0;//warto�� zerowana, aby zacz�� nast�pn� kolejk� od najm�odszego bitu
                }
                display=licznik|kolejka;//po��czenie stoj�cych kolejek z podr�uj�c�
            }
            if(podprogram==9)//kontynuacja podprogramu 9
            {
                licznik=PRNG(licznik);//Wygenerowanie nowej warto�ci na podstawie poprzedniego licznika i przypisanie tej warto�ci do licznika
                display=licznik;
                //przypisanie warto�ci licznika do display
            }
        }
        IntToBinary(display);//wy�wietlenie przekonwertowanej warto�ci display
        Opoznienie();
    }
    return 0;
}

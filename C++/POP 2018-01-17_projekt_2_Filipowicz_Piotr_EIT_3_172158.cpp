//POP 2018-01-17 projekt 2 Filipowicz Piotr EIT 3 172158   CodeBlocks   GNU GCC Compiler

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void menu(string &polecenie);
void formatowanie_polecenia(string &polecenie);
void error(string fun,string &linia);
void stat(string fun,string linia, int &znaki, int &znaki_1, int &slowa, int &zdania);
void transformacja(string fun, string &linia);
void sprawdz_polecenie(string &pol, string &fun,string polecenie, string &nazwa_pliku);
void zapis(string fun, int znaki, int zdania, int znaki_1, int slowa, string nazwa_pliku);
void spacje(string &linia);
void podwojne(string &linia);

int main()
{
    string polecenie;
    string linia;
    string pol, fun;
    string nazwa_pliku;
    int znaki = 0, znaki_1 = 0, slowa = 0, zdania = 0;

    menu(polecenie);
    sprawdz_polecenie(pol, fun, polecenie, nazwa_pliku);

    ifstream pliko;
    pliko.open(nazwa_pliku.c_str());

    do
    {
        getline(pliko,linia);

        if(pol=="error")
            error(fun,linia);

        else if(pol=="stat")
            stat(fun, linia, znaki, znaki_1, slowa, zdania);

        else if(pol=="transform")
            transformacja(fun,linia);

        else {cout << "Bledne polecenie"; pliko.close(); return 0;}

        ofstream plikz("wynik.txt", ios::app);
        plikz << linia << endl;
        plikz.close();

    }while(pliko.eof()==false);

    pliko.close();

    remove(nazwa_pliku.c_str());
    rename("wynik.txt",nazwa_pliku.c_str());

    if(pol=="stat")
        zapis(fun, znaki, zdania, znaki_1, slowa, nazwa_pliku);

    ofstream plikz(nazwa_pliku.c_str(), ios::app);

    plikz.close();

    return 0;
}

void zapis(string fun, int znaki, int zdania, int znaki_1, int slowa, string nazwa_pliku)
{
    ofstream plikz(nazwa_pliku.c_str(), ios::app);
    plikz << endl << "W tekscie jest: " << endl;

    if (fun == "znaki" || fun == "")
        plikz << "znakow (ze spacjami): " << znaki << endl;

    if (fun == "znaki_1" || fun == "")
        plikz << "znakow (bez spacji): " << znaki_1 << endl;

    if (fun == "slowa" || fun == "")
        plikz << "slow: " << slowa << endl;

    if (fun == "zdania" || fun == "")
        plikz << "zdan: " << zdania << endl;

    plikz.close();
}

void spacje(string &linia)
{
     for(int i=0;i<linia.length();i++)
            if(linia[i]==' '&&linia[i+1]==' ')
            {
                linia.erase(i,1);
                i--;
            }
}

void podwojne(string &linia)
{
    for(int i=0;i<linia.length();i++)
            if((linia[i]==33 || linia[i]==46 || linia[i]==63 || linia[i]==58 || linia[i]==59 || linia[i]==40 || linia[i]==34 || linia[i]==32 || linia[i]==44) && linia[i]==linia[i+1])
            {
                linia.erase(i,1);
                i--;
            }
}

void error(string fun,string &linia)
{

    if(fun=="spacja" || fun=="")
        spacje(linia);

    if(fun=="podwojne" || fun=="")
        podwojne(linia);

    if(fun=="powtorzenia" || fun=="")
    {
        string pomoc;
        int pocz=0, kon=0;
        for (int k=0; k<linia.length(); k++)
        {
            pomoc.erase(0,pomoc.length());
            if((linia[k] >= 97 && linia[k] <=122) || (linia[k] >= 65 && linia[k] <=90))
               for (int i=k; i<=linia.length(); i++)
               {
                  if(linia[i]==33 || linia[i]==46 || linia[i]==63 || linia[i]==58 || linia[i]==59 || linia[i]==40 || linia[i]==34 || linia[i]==32 || linia[i]==44 || i==linia.length())
                     {
                         for(int j=k; j<i; j++)
                         {
                             pomoc+=linia[j];
                             kon = j;
                         }
                         pocz = k;
                         k = i;
                         break;
                     }
               }
            int pozycja = linia.find(pomoc, kon);
            int dlugosc = pomoc.length();

            if(pozycja != string::npos)
            {
                linia.erase(pozycja, dlugosc);
            }
        }
        spacje(linia);
        podwojne(linia);
    }
}

void transformacja(string fun, string &linia)
{
    if(fun=="male")
        for(int i=0; i<linia.length(); i++)
            if(linia[i] >= 65 && linia[i] <= 90)
                linia[i] += 32;

    if(fun=="duze")
        for(int i=0; i<linia.length(); i++)
            if(linia[i] >= 97 && linia[i] <= 122)
                linia[i] -= 32;

    if(fun=="zdanie")
    {
        for(int i=0; i<linia.length(); i++)
            if(linia[i] >= 65 && linia[i] <= 90)
                linia[i] += 32;

         for (int k=0; k<linia.length(); k++)
            if(linia[k] >= 97 && linia[k] <=122)
                {
                    linia[k] -= 32;
                    break;
                }

        for (int i=0; i<linia.length(); i++)
            if(linia[i]==33 || linia[i]==46 || linia[i]==63)
                for (int j=i; j<linia.length(); j++)
                    if(linia[j] >= 97 && linia[j] <=122)
                        {
                            linia[j] -= 32;
                            break;
                        }
    }
}

void stat(string fun,string linia, int &znaki, int &znaki_1, int &slowa, int &zdania)
{
    if (fun == "znaki" || fun == "")
    {
        znaki += linia.length();
    }

    if (fun == "znaki_1" || fun == "")
    {
        znaki_1 += linia.length();

        for (int i=0; i<linia.length(); i++)
            if(isspace(linia[i]) != 0) znaki_1--;
    }

    if(fun == "slowa" || fun == "")
    {
        for (int k=0; k<linia.length(); k++)
            if((linia[k] >= 97 && linia[k] <=122) || (linia[k] >= 65 && linia[k] <=90))
               for (int i=k; i<=linia.length(); i++)
               {
                  if(linia[i]==33 || linia[i]==46 || linia[i]==63 || linia[i]==58 || linia[i]==59 || linia[i]==40 || linia[i]==34 || linia[i]==32 || linia[i]==44 || i==linia.length())
                     {
                         slowa++;
                         k = i-1;
                         break;
                     }
               }
    }

    if(fun=="zdania" || fun=="")
    {
        for (int k=0; k<linia.length(); k++)
            if ((linia[k] >= 97 && linia[k] <=122) || (linia[k] >= 65 && linia[k] <=90))
                for (int i=k; i<=linia.length(); i++)
                    if (linia[i]==33 || linia[i]==46 || linia[i]==63)
                    {
                         zdania++;
                         k = i-1;
                         break;
                    }
    }
}

void sprawdz_polecenie(string &pol, string &fun,string polecenie, string &nazwa_pliku)
{
    string pomoc = "";
    fun = "";
    bool dwukrop=false;
    for(int i=0;i<polecenie.length();i++)
    {
        if(polecenie[i]==':')
        {
            pomoc="";
            for(int j=0;j<i;j++)
            {
                pomoc += polecenie[j];
            }
            pol = pomoc;
            pomoc="";
            for(int j=i+1;j<polecenie.find('(');j++)
            {
                pomoc += polecenie[j];
            }
            fun = pomoc;
            dwukrop = true;
        }

        if(polecenie[i]=='('&&dwukrop==false)
        {
            for(int j=0;j<i;j++)
            {
                pomoc += polecenie[j];
            }
            pol = pomoc;
        }
    }

    pomoc="";
    for(int i=polecenie.find('(')+1; i<polecenie.find(')'); i++)
    {
        pomoc += polecenie[i];
    }
    nazwa_pliku = pomoc;
}

void menu (string &polecenie)
{
    cout << "Podaj polecenie: " << endl;
    getline(cin,polecenie);

    formatowanie_polecenia(polecenie);
}

void formatowanie_polecenia(string &polecenie)
{
    for(int i=0;i<polecenie.length();i++)
    {

        if(polecenie[i]>='A' && polecenie[i]<='Z')
        {
            polecenie[i]+=32;
        }
        else if(polecenie[i]==32)
        {
            polecenie.erase(i,1);
            i-=1;
        }
    }
}

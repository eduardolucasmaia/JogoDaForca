#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<string>

using namespace std;

int main()
{
	string palavra, lacuna, dica;
	char letra;
	int vida=7, cont, venceu=0, pontos=0;

	cout << "Digite a palavra secreta: ";
	getline(cin, palavra);
	cout << "Digite a dica: ";
	getline(cin, dica);

	for(int i=0; i<palavra.length(); i++)
    {
        if(palavra[i]==' ') lacuna.push_back(' ');
        else lacuna.push_back('_');
    }

	while(vida > 0 && venceu == 0)
	{
	    system("cls");

		cout << "Dica: " << dica << endl;
		cout << "Quantidade de letras: " << palavra.length() << endl;
		cout << "Vidas: " << vida << "\n\n";

		cout << lacuna << endl << endl;

		cout << "Digite uma letra: ";
		letra = getch();

		cout << letra << endl;

		for(int i=0; i<palavra.length(); i++)
		{
			if(palavra[i]==letra)
			{
				lacuna[i] = letra;
				cont++;
				pontos+=2;
			}
		}

		if(cont==0)
		{
		    cout << "Voce errou uma letra!" << endl;
			vida--;
			Sleep(500);
		}

		if(cont>0)
		{
		    cout << "Voce acertou uma letra!" << endl;
			Sleep(500);
		}
		if(vida == 0) venceu=-1;

		if(palavra == lacuna) venceu=1;
		cont=0;

	}

	cout << endl;
	if(venceu==1) cout << "Parabens, Voce venceu! Fez " << pontos+vida*3 << " pontos.\n\n";
	if(venceu==-1) cout << "Voce perdeu. Fez " << pontos << " pontos.\n\n";

	cout << "Pressione qualquer tecla para continuar...";
	getch();

}

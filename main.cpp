#include <iostream>

#include "gamelib/janela.h"
#include "gamelib/imagens.h"
#include "gamelib/mensagem.h"
#include "gamelib/fontes_e_texto.h"
#include "gamelib/eventos.h"
#include "gamelib/mouse.h"
#include "gamelib/teclado.h"
#include "gamelib/audio.h"
#include "gamelib/timer.h"
#include "gamelib/animacoes.h"
#include "gamelib/sprites.h"

using namespace std;

int main(void){

    int menu_close = 0;
    int opcao = 0;

    while (!menu_close){
        cout << "Escolha uma opcao:" << endl;
        cout << "1 - Janela" << endl;
        cout << "2 - Imagens" << endl;
        cout << "3 - Mensagem" << endl;
        cout << "4 - Fontes e texto" << endl;
        cout << "5 - Eventos" << endl;
        cout << "6 - Mouse" << endl;
        cout << "7 - Teclado" << endl;
        cout << "8 - Audio" << endl;
        cout << "9 - Timer" << endl;
        cout << "10 - Animacoes" << endl;
        cout << "11 - Sprites" << endl;
        cout << "0 - Sair" << endl;

        cin >> opcao;

        switch (opcao){
        case 1:
            janela();
            break;
        case 2:
            imagens();
            break;
        case 3:
            mensagem();
            break;
        case 4:
            fontes_e_texto();
            break;
        case 5:
            eventos();
            break;
        case 6:
            mouse();
            break;
        case 7:
            teclado();
            break;
        case 8:
            audio();
            break;
        case 9:
            timer_f();
            break;
        case 10:
            animacoes();
            break;
        case 11:
            sprites();
            break;
        case 0:
            cout << "Voce escolheu sair" << endl;
            menu_close = 1;
            break;
        default:
            cout << "Opcao invalida" << endl << endl;
            break;
        }
    }

    return 0;
}

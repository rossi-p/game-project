#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>

int mensagem(void){
    //guarda o t�tulo da caixa de texto
    char tcaixa[50] = "Meu titulo";
    //o t�tulo da mensagem dentro da caixa
    char titulo[100] = "Sou uma caixa de texto";
    //o conte�do da mensagem exibida
    char texto[200] = "A mensagem a ser exibida deve ficar aqui";
    //mostra a caixa de texto
    int r = al_show_native_message_box(NULL,tcaixa,titulo,texto,NULL,ALLEGRO_MESSAGEBOX_OK_CANCEL);
    printf("%i",r);
    return 0;
}

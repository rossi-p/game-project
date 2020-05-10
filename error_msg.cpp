#include <allegro5/allegro_native_dialog.h>

//função que mostra mensagem de erro em uma caixa de texto nativa
//a função recebe a string da mensagem como parâmetro
void error_msg(char *text){
    al_show_native_message_box(NULL,"ERRO",
        "Ocorreu o seguinte erro e o programa sera finalizado:",
        text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}

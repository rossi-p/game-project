#include <allegro5/allegro_native_dialog.h>

//fun��o que mostra mensagem de erro em uma caixa de texto nativa
//a fun��o recebe a string da mensagem como par�metro
void error_msg(char *text){
    al_show_native_message_box(NULL,"ERRO",
        "Ocorreu o seguinte erro e o programa sera finalizado:",
        text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}

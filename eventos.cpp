// Os arquivos de cabe�alho
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#include "gamelib/error_msg.h"

// Atributos da tela
#define LARGURA_TELA 640
#define ALTURA_TELA 480

int eventos(void){
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_BITMAP *imagem = NULL;
	//declara a fila de eventos
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    //Inicializa��o da biblioteca Allegro
	if (!al_init()){
		error_msg("Falha ao inicializar a Allegro");
		return -1;
	}

	//tenta iniciar o m�dulo de imagens
	if (!al_init_image_addon()){
		error_msg("Falha ao inicializar add-on allegro_image");
		return -1;
	}

	//cria display em janela
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
	//caso al_create_display retorne NULL, encerra programa
	if (!janela){
		error_msg("Falha ao criar janela");
		return -1;
	}

	//carrega imagem
	imagem = al_load_bitmap("hu3.bmp");
	//caso al_load_bitmap retorne NULL, encerra programa
	if (!imagem){
		error_msg("Falha ao carregar o arquivo de imagem");
		al_destroy_display(janela);
		return -1;
	}

	//cria fila de eventos
	fila_eventos = al_create_event_queue();
	//caso al_create_event_queue retorne NULL, destroi a janela e encerra o programa
	if (!fila_eventos){
		error_msg("Falha ao criar fila de eventos");
		al_destroy_display(janela);
		return -1;
	}

	//registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	//desenha imagem no display ativo em X:0 Y:0
	al_draw_bitmap(imagem, 0, 0, 0);

	//atualiza tela
	al_flip_display();

	while (1){
		//declara vriavel que recebe evento e timeout
		ALLEGRO_EVENT evento;
		//espero por um evento da fila, e guarda em evento
		al_wait_for_event(fila_eventos, &evento);

		//se teve eventos e foi um evento de fechar janela, encerra repeti��o
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			int resp = al_show_native_message_box(janela,"Fechar",
				"Deseja sair do programa?","",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
			if (resp)
				break;
		}

		al_draw_bitmap(imagem, 0, 0, 0);
		al_flip_display();
	}

	//destroi janela e fila de eventos ao fim
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

	return 0;
}

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "gamelib/error_msg.h"

//fps = frames per second = atualizacoes por segundo
#define FPS 60.0
#define LARGURA_TELA 640
#define ALTURA_TELA 480

ALLEGRO_DISPLAY *janela_timer = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos_timer = NULL;
//declara o timer do programa
ALLEGRO_TIMER *timeroftimer = NULL;

int inicializar_timer(){
    if (!al_init()){
        error_msg("Falha ao inicializar a Allegro");
        return 0;
    }

    //cria o timer com o intervalo de tempo que ele ira disparar
    timeroftimer = al_create_timer(1.0 / FPS);
    if(!timeroftimer) {
        error_msg("Falha ao criar temporizador");
        return 0;
    }

    janela_timer = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if(!janela_timer) {
        error_msg("Falha ao criar janela_timer");
        al_destroy_timer(timeroftimer);
        return 0;
    }

    al_set_window_title(janela_timer, "Utilizando timers");

    fila_eventos_timer = al_create_event_queue();
    if(!fila_eventos_timer) {
        error_msg("Falha ao criar fila de eventos");
        al_destroy_timer(timeroftimer);
        al_destroy_display(janela_timer);
        return 0;
    }

    al_register_event_source(fila_eventos_timer, al_get_display_event_source(janela_timer));
    //registra o timer na fila de eventos
    al_register_event_source(fila_eventos_timer, al_get_timer_event_source(timeroftimer));
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    //inicia a contagem do timer
    al_start_timer(timeroftimer);

    return 1;
}

int timer_f(void){
    //flag que determina quando a tela precisa ser atualizada
    int desenha = 1;
    //flag que determina quando devemos sair do loop principal
    int sair = 0;
    //vetor que guarda as componentes RGB que sera impresso no fundo da tela
    int cor[3]={0,0,0};
    //i= indice que acessamos o veror
    //inc= direcao que a cor incremente, ou ele sera +1 ou -1
    int i=0,inc=1;


    if (!inicializar_timer()){
        return -1;
    }

    while(!sair){
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos_timer, &evento);

        /* -- EVENTOS -- */
        //se o tipo do evento for o disparo de um timer
        if(evento.type == ALLEGRO_EVENT_TIMER){
            cor[i]+=inc;
            if (cor[i]>=255)
                inc*=-1;
            if (cor[i]<=0){
                i=(i+1)%3;
                inc*=-1;
            }
            desenha = 1;
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            sair = 1;
        }

        /* -- ATUALIZA TELA -- */
        if(desenha && al_is_event_queue_empty(fila_eventos_timer)) {
            al_clear_to_color(al_map_rgb(cor[0],cor[1],cor[2]));
            al_flip_display();
            //zera flag para nao entrar aqui no proximo loop
            desenha = 0;
        }
    }

    al_destroy_timer(timeroftimer);
    al_destroy_display(janela_timer);
    al_destroy_event_queue(fila_eventos_timer);

    return 0;
}

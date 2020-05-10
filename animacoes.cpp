#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "gamelib/error_msg.h"

//fps = frames per second = atualizacoes de tela por segundo
#define FPS 60.0
#define LARGURA_TELA 640
#define ALTURA_TELA 480

ALLEGRO_DISPLAY *janela_animacoes = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos_animacoes = NULL;
ALLEGRO_TIMER *timer_animacao = NULL;
ALLEGRO_BITMAP *quadrado = NULL;

int inicializar_animacoes(){
    if (!al_init()){
        error_msg("Falha ao inicializar a Allegro");
        return 0;
    }

    //cria o timer com o intervalo de tempo que ele ira disparar
    timer_animacao = al_create_timer(1.0 / FPS);
    if(!timer_animacao) {
        error_msg("Falha ao criar temporizador");
        return 0;
    }

    janela_animacoes = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if(!janela_animacoes) {
        error_msg("Falha ao criar janela_animacoes");
        al_destroy_timer(timer_animacao);
        return 0;
    }

    al_set_window_title(janela_animacoes, "Testando FPS");

    quadrado = al_create_bitmap(50, 50);
    if (!quadrado){
        error_msg("Falha ao criar bitmap");
        al_destroy_timer(timer_animacao);
        al_destroy_display(janela_animacoes);
        return 0;
    }
    al_set_target_bitmap(quadrado);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(janela_animacoes));

    fila_eventos_animacoes = al_create_event_queue();
    if(!fila_eventos_animacoes) {
        error_msg("Falha ao criar fila de eventos");
        al_destroy_timer(timer_animacao);
        al_destroy_display(janela_animacoes);
        al_destroy_bitmap(quadrado);
        return 0;
    }

    al_register_event_source(fila_eventos_animacoes, al_get_display_event_source(janela_animacoes));
    al_register_event_source(fila_eventos_animacoes, al_get_timer_event_source(timer_animacao));
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer_animacao);

    return 1;
}

int animacoes(void){
    //define quando a tela sera atualizada
    int desenha = 1;
    //quando o loop principal deve encerrar
    int sair = 0;
    //posicao do quadrado e quanto ele andara a cada disparo do timer, para coordenada X e Y
    int posx=50, dir_x=5;
    int posy=100, dir_y=5;

    if (!inicializar_animacoes()){
        return -1;
    }

    while(!sair){
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos_animacoes, &evento);

        /* -- EVENTOS -- */
        //se o tipo do evento for o disparo de um timer
        if(evento.type == ALLEGRO_EVENT_TIMER){
            posx+=dir_x;
            posy+=dir_y;
            //se passou das bordas, inverte a direcao
            if (posx<=10 || posx>=LARGURA_TELA-60)
                dir_x*=-1;
            if (posy<=10 || posy>=ALTURA_TELA-60)
                dir_y*=-1;
            desenha=1;
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            sair = 1;
        }

        /* -- ATUALIZA TELA -- */
        if(desenha && al_is_event_queue_empty(fila_eventos_animacoes)) {

            al_clear_to_color(al_map_rgb(0,0,0));

            //desenha o quadrado na tela nas posicoes X e Y
            al_draw_bitmap(quadrado, posx, posy, 0);

            al_flip_display();

            //zera flag para nao entrar aqui no proximo loop
            desenha = 0;
        }
    }

    al_destroy_bitmap(quadrado);
    al_destroy_timer(timer_animacao);
    al_destroy_display(janela_animacoes);
    al_destroy_event_queue(fila_eventos_animacoes);

    return 0;
}

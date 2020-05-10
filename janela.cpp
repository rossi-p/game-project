// Inclui o arquivo de cabe�alho da biblioteca Allegro 5
#include <allegro5/allegro.h>

// Nossa conhecida fun��o main...
int janela(void)
{
    // Vari�vel representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;

    // Inicializamos a biblioteca
    al_init();

    // Criamos a nossa janela - dimens�es de 640x480 px
    janela = al_create_display(640, 480);

    // Preenchemos a janela de branco
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Atualiza a tela
    al_flip_display();

    // Segura a execu��o por 10 segundos
    al_rest(5.0);

    // Finaliza a janela
    al_destroy_display(janela);

    return 0;
}

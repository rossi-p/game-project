// Inclui o cabe�alho da bibilioteca Allegro 5
#include <allegro5/allegro.h>

// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>

int imagens(void)
{
    // Vari�vel representando a janela principal
    ALLEGRO_DISPLAY *janela = NULL;

    // Vari�vel representando a imagem
    ALLEGRO_BITMAP *imagem = NULL;

    // Inicializa a Allegro
    al_init();

    // Inicializa o add-on para utiliza��o de imagens
    al_init_image_addon();

    // Configura a janela
    janela = al_create_display(640, 480);

    // Carrega a imagem
    imagem = al_load_bitmap("hu3.bmp");

    // Desenha a imagem na tela
    al_draw_bitmap(imagem, 0, 0, 0);

    // Atualiza a tela
    al_flip_display();

    // Segura a execu��o por 10 segundos
    al_rest(5.0);

    // Finaliza a janela
    al_destroy_display(janela);

    return 0;
}

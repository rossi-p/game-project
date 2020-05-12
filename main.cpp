#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FPS 60.0

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *menu_font_tittle = NULL;
ALLEGRO_FONT *menu_font_options = NULL;
ALLEGRO_BITMAP *gui_pieces = NULL;
//ALLEGRO_SAMPLE *sound_(...) = NULL;
//ALLEGRO_AUDIO_STREAM *music_(...) = NULL;

int DISPLAY_WIDTH = 800;
int DISPLAY_HEIGHT = DISPLAY_WIDTH * 0.75;

void error_message(char *text){
    al_show_native_message_box(NULL, "ERROR",
                               "Oops. The app had to be terminated due to the following issue:",
                               text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

int initialize(){

    if (!al_init()){
        error_message("Error initializing Allegro5");
        return 0;
    }
    if (!al_init_image_addon()){
        error_message("Error initializing image add-on");
        return 0;
    }
    if(!al_init_font_addon()){
        error_message("Error initializing font add-on");
        return 0;
    }
    if(!al_init_ttf_addon()){
        error_message("Error initializing ttf add-on");
        return 0;
    }
    if (!al_install_mouse()){
        error_message("Error installing mouse");
        return 0;
    }
    if (!al_install_keyboard()){
        error_message("Error installing keyboard");
        return 0;
    }
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (!display){
        error_message("Error creating display");
        return 0;
    }
    al_set_window_title(display, "My Game");

    event_queue = al_create_event_queue();
    if (!event_queue){
        error_message("Error creting event queue");
        al_destroy_display(display);
        return 0;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        error_message("Error creating timer");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return 0;
    }
    menu_font_tittle = al_load_font("gamelib/fonts/arial.ttf", 34, 0);
    if (!menu_font_tittle){
        error_message("Error loading font");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return 0;
    }
    menu_font_options = al_load_font("gamelib/fonts/arial.ttf", 16, 0);
    if (!menu_font_options){
        error_message("Error loading font");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return 0;
    }
    gui_pieces = al_load_bitmap("gamelib/images/gui_pieces.bmp");
    if (!gui_pieces){
        error_message("Error loading menu buttons");
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return 0;
    }
    al_convert_mask_to_alpha(gui_pieces,al_map_rgb(255,0,255));

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    return 1;
}

int game_options(){

    return 0;
}

int game_play(){

    return 0;
}

int game_menu(){
    int game_menu = 1;
    int draw = 1;
    int menu_option = 1, menu_max_options = 3;

    while (game_menu){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER){
            draw = 1;
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            //Pressionar tecla
            if (event.keyboard.keycode == ALLEGRO_KEY_UP ||
                event.keyboard.keycode == ALLEGRO_KEY_W){
                    if (menu_option > 1) menu_option -= 1;
                    else menu_option = menu_max_options;
                }
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN ||
                event.keyboard.keycode == ALLEGRO_KEY_S){
                    if (menu_option < menu_max_options) menu_option += 1;
                    else menu_option = 1;
                }
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER ||
                event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    switch (menu_option){
                    case 1:
                        game_play();
                        break;
                    case 2:
                        game_options();
                        break;
                    case 3:
                        game_menu = 0;
                        break;
                    }
                }
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    game_menu = 0;//fecha o menu
                }
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES){
            //Mover o mouse
            if (event.mouse.x > DISPLAY_WIDTH / 2 - 70 &&
                event.mouse.x < DISPLAY_WIDTH / 2 + 78 &&
                event.mouse.y > 230 + (0 * 30) &&
                event.mouse.y < 253 + (0 * 30)){
                menu_option = 1;
            }
            if (event.mouse.x > DISPLAY_WIDTH / 2 - 70 &&
                event.mouse.x < DISPLAY_WIDTH / 2 + 78 &&
                event.mouse.y > 230 + (1 * 30) &&
                event.mouse.y < 253 + (1 * 30)){
                menu_option = 2;
            }
            if (event.mouse.x > DISPLAY_WIDTH / 2 - 70 &&
                event.mouse.x < DISPLAY_WIDTH / 2 + 78 &&
                event.mouse.y > 230 + (2 * 30) &&
                event.mouse.y < 253 + (2 * 30)){
                menu_option = 3;
            }
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            //Clicar
            if (event.mouse.x > DISPLAY_WIDTH / 2 - 70 &&
                event.mouse.x < DISPLAY_WIDTH / 2 + 78 &&
                event.mouse.y > 230 + (0 * 30) &&
                event.mouse.y < 253 + (0 * 30)){
                game_play();
            }
            if (event.mouse.x > DISPLAY_WIDTH / 2 - 70 &&
                event.mouse.x < DISPLAY_WIDTH / 2 + 78 &&
                event.mouse.y > 230 + (1 * 30) &&
                event.mouse.y < 253 + (1 * 30)){
                game_options();
            }
            if (event.mouse.x > DISPLAY_WIDTH / 2 - 70 &&
                event.mouse.x < DISPLAY_WIDTH / 2 + 78 &&
                event.mouse.y > 230 + (2 * 30) &&
                event.mouse.y < 253 + (2 * 30)){
                game_menu = 0;//fecha o menu
            }
        }
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            game_menu = 0;//fecha o menu
        }

        if (draw == 1 && al_is_event_queue_empty(event_queue)){
            //desenha tudo na tela
            al_clear_to_color(al_map_rgb(0, 0, 0));//background
            al_draw_bitmap_region(gui_pieces, 2, 582, 300, 300, DISPLAY_WIDTH / 2 -150, 150, 0);
            al_draw_bitmap_region(gui_pieces, 350, 666 + (menu_option-1)*16, 134, 15, DISPLAY_WIDTH / 2 - 62, 234 + (menu_option-1)*30, 0);
            al_draw_bitmap_region(gui_pieces, 335, 668, 10, 100, DISPLAY_WIDTH / 2 - 59, 236, 0);
            al_draw_text(menu_font_tittle, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 + 2, 164, ALLEGRO_ALIGN_CENTER, "THE GAME");
            al_draw_text(menu_font_options, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 + 15, 233, ALLEGRO_ALIGN_CENTER, "PLAY");
            al_draw_text(menu_font_options, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 + 15, 263, ALLEGRO_ALIGN_CENTER, "OPTIONS");
            al_draw_text(menu_font_options, al_map_rgb(0, 0, 0), DISPLAY_WIDTH / 2 + 15, 293, ALLEGRO_ALIGN_CENTER, "EXIT");
            //atualiza a tela
            al_flip_display();
            //seta draw = 0 para não desenhar nada entre frames
            draw = 0;
        }
    }
    return 0;
}

int main(void){

    if (!initialize()){
        return -1;
    }

    //carrega o menu do jogo
    game_menu();

    al_destroy_bitmap(gui_pieces);
    al_destroy_font(menu_font_options);
    al_destroy_font(menu_font_tittle);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}

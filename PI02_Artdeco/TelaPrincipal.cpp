#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

const int WIDTH = 1920;
const int HEIGHT = 985;

int telaInicial(ALLEGRO_DISPLAY* display) {

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_mouse();

    al_set_window_position(display, 0, 35);
    al_set_window_title(display, "ArtDeco");
    ALLEGRO_MOUSE_STATE state;
    ALLEGRO_FONT* font_tittle = al_load_font("./assets/fonts/Cinzel-Regular.ttf", 70, ALLEGRO_TTF_NO_KERNING);
    ALLEGRO_FONT* font_options = al_load_font("./assets/fonts/MontserratSubrayada-Regular.ttf", 40, ALLEGRO_TTF_NO_KERNING);
    ALLEGRO_FONT* font_text = al_load_font("./assets/fonts/MontserratAlternates-Regular.ttf", 50, ALLEGRO_TTF_NO_KERNING);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    ALLEGRO_BITMAP* pincel_cursor = al_load_bitmap("./assets/img/cursor.png");
    ALLEGRO_MOUSE_CURSOR* cursor = al_create_mouse_cursor(pincel_cursor, 0, 0);
    al_set_mouse_cursor(display, cursor);
    al_show_mouse_cursor(display);
    ALLEGRO_BITMAP* moldura = al_load_bitmap("./assets/img/moldura2.png");
    ALLEGRO_BITMAP* monalisa = al_load_bitmap("./assets/img/monalisa2.png");
    ALLEGRO_BITMAP* santa_ceia = al_load_bitmap("./assets/img/santa_ceia.png");
    ALLEGRO_BITMAP* noite_estrelada = al_load_bitmap("./assets/img/noite_estrelada.png");
    ALLEGRO_BITMAP* bandeirantes = al_load_bitmap("./assets/img/retirantes.png");
    int novaTela = 0;
    while (true) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        al_get_mouse_state(&state);
        int mouseX = state.x;
        int mouseY = state.y;
        int mouseB = state.buttons;
        int r = 0;
        int g = 0;
        int b = 0;

        al_clear_to_color(al_map_rgb(196, 196, 196));
        al_draw_scaled_bitmap(noite_estrelada, 0, 0, al_get_bitmap_width(noite_estrelada), al_get_bitmap_height(noite_estrelada), 230, 125, 1500, 735, 0);
        al_draw_scaled_rotated_bitmap(monalisa, al_get_bitmap_width(monalisa) / 2, al_get_bitmap_height(monalisa) / 2, 350, 700, 0.45, 0.45, 25 * ALLEGRO_PI / 180, 0);
        al_draw_scaled_rotated_bitmap(santa_ceia, al_get_bitmap_width(santa_ceia) / 2, al_get_bitmap_height(santa_ceia) / 2, 1550, 210, 0.6, 0.6, 14 * ALLEGRO_PI / 180, 0);
        al_draw_scaled_rotated_bitmap(bandeirantes, al_get_bitmap_width(bandeirantes) / 2, al_get_bitmap_height(bandeirantes) / 2, 1550, 700, 0.2, 0.2, 353 * ALLEGRO_PI / 180, 0);
        al_draw_scaled_bitmap(moldura, 0, 0, al_get_bitmap_width(moldura), al_get_bitmap_height(moldura), -130, -73, 2160, 1165, 0);
        al_draw_text(font_tittle, al_map_rgba(0, 0, 0, 70), WIDTH / 2 - 5, 205, ALLEGRO_ALIGN_CENTER, "ArtDeco");
        al_draw_text(font_tittle, al_map_rgb(0, 0, 0), WIDTH / 2, 200, ALLEGRO_ALIGN_CENTER, "ArtDeco");

        if (mouseX > (WIDTH / 2) - 100 && mouseX < (WIDTH / 2) + 100 && mouseY > 400 && mouseY < 440) {
            r = 225;
            g = 190;
            b = 0;
            if (mouseB == 1) {
                r = 0; g = 0; b = 0;
                novaTela = 3;
                break;
                
            }
        }
        else { b = 0; }
        char buffer[50]; // Buffer para a string formatada

        // Formatar a string
        snprintf(buffer, sizeof(buffer), "Jogar");


        al_draw_text(font_options, al_map_rgb(r, g, b), WIDTH / 2, 400, ALLEGRO_ALIGN_CENTER, "Jogar");

        if (mouseX > WIDTH / 2 - 100 && mouseX < WIDTH / 2 + 100 && mouseY > 500 && mouseY < 540) {
            r = 225;
            g = 190;
            b = 0;
            if (mouseB == 1) {
                r = 0; g = 0; b = 0;
                novaTela = 6;
                break;

            }
        }
        else { r = 0; g = 0; b = 0; }
        al_draw_text(font_options, al_map_rgb(r, g, b), WIDTH / 2, 500, ALLEGRO_ALIGN_CENTER, "Níveis");

        if (mouseX > WIDTH / 2 - 100 && mouseX < WIDTH / 2 + 100 && mouseY > 600 && mouseY < 640) {
            r = 225;
            g = 190;
            b = 0;
            if (mouseB == 1) {
                r = 0; g = 0; b = 0;
                novaTela = 5;
                break;

            }
        }
        else { r = 0; g = 0; b = 0; }
        al_draw_text(font_options, al_map_rgb(r, g, b), WIDTH / 2, 600, ALLEGRO_ALIGN_CENTER, "Galeria");

        if (mouseX > WIDTH / 2 - 100 && mouseX < WIDTH / 2 + 100 && mouseY > 700 && mouseY < 740) {
            r = 225;
            g = 190;
            b = 0;
            if (mouseB == 1) {
                r = 0; g = 0; b = 0;
                novaTela = 4;
                break;

            }
        }
        else { r = 0; g = 0; b = 0; }
        al_draw_text(font_options, al_map_rgb(r, g, b), WIDTH / 2, 700, ALLEGRO_ALIGN_CENTER, "Opções");

        if (mouseX > 270 && mouseX < 330 && mouseY > 170 && mouseY < 230) {
            r = 228;
            g = 195;
            b = 78;
            if (mouseB == 1) {
                r = 196; g = 196; b = 196;
            }
        }
        else { r = 196; g = 196; b = 196; }

        al_draw_filled_circle(295, 205, 30, al_map_rgba(0, 0, 0, 70));
        al_draw_filled_circle(300, 200, 30, al_map_rgb(r, g, b));
        al_draw_circle(300, 200, 30, al_map_rgb(0, 0, 0), 1.5);
        al_draw_text(font_text, al_map_rgba(0, 0, 0, 70), 297, 170, ALLEGRO_ALIGN_CENTER, "?");
        al_draw_text(font_text, al_map_rgb(0, 0, 0), 300, 167, ALLEGRO_ALIGN_CENTER, "?");

        al_flip_display();
    }

    al_destroy_bitmap(moldura);
    al_destroy_font(font_tittle);
    al_destroy_font(font_options);
    al_destroy_font(font_text);
    al_destroy_event_queue(event_queue);
    al_destroy_mouse_cursor(cursor);
    al_destroy_bitmap(pincel_cursor);

    return novaTela;
}

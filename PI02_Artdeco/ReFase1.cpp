#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <vector>
#include "ReFase1.h"
#include "LevelData.h"

ALLEGRO_FONT* font;
const int WIDTH = 1920;
const int HEIGHT = 985;
int novaTela = 0;

/*
0 - Branco
1 - Preto
2 - Borda
3 - Hover
4 - Flag
5 - Errado
*/

int makeRowHints(int startX, int startY, ALLEGRO_FONT* font, int square, ALLEGRO_BITMAP* boxes[], int gameWidth, int gameHeight, std::vector<std::vector<int>> coords) {
    std::string hintRow;
    int conjuntoRow;
    int offset;
    int maior = 1;

    for (int j = 0; j < gameHeight; j++) {
        conjuntoRow = 0;
        hintRow = "";
        offset = 0;

        for (int i = gameWidth-1; i >= 0; i--) {
            if (coords[j][i] == 1) { 
                conjuntoRow++; 
            }
            if ((coords[j][i] == 0 or i == 0) and conjuntoRow > 0) {
                hintRow = std::to_string(conjuntoRow);
                conjuntoRow = 0;

                int x = startX - offset * square;
                int y = square + j * square + startY;
                al_draw_scaled_bitmap(boxes[2], 0, 0, al_get_bitmap_width(boxes[2]), al_get_bitmap_height(boxes[2]), x, y, square, square, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), x, y - 2, 0, hintRow.c_str());
                offset++;
            }
            else if (hintRow == "" and i == 0) {
                hintRow = "0";

                int x = startX - offset * square;
                int y = square + j * square + startY;
                al_draw_scaled_bitmap(boxes[2], 0, 0, al_get_bitmap_width(boxes[2]), al_get_bitmap_height(boxes[2]), x, y, square, square, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), x, y - 2, 0, hintRow.c_str());
            }
            if (maior < offset) { maior = offset - 1; }
        }
    }
    return maior;
}

int makeColHints(int startX, int startY, ALLEGRO_FONT* font, int square, ALLEGRO_BITMAP* boxes[], int gameWidth, int gameHeight, std::vector<std::vector<int>> coords) {
    std::string hintCol;
    int conjuntoCol;
    int offset;
    int maior = 1;


    for (int j = 0; j < gameWidth; j++) {
        conjuntoCol = 0;
        hintCol = "";
        offset = 0;

        for (int i = gameHeight-1; i >= 0; i--) {
            if (coords[i][j] == 1) {
                conjuntoCol++; 
            }
            if ((coords[i][j] == 0 or i == 0) and conjuntoCol > 0) {
                hintCol = std::to_string(conjuntoCol);
                conjuntoCol = 0;
                
                int x = square + j * square + startX;
                int y = startY - offset * square;
                al_draw_scaled_bitmap(boxes[2], 0, 0, al_get_bitmap_width(boxes[2]), al_get_bitmap_height(boxes[2]), x, y, square, square, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), x + 2, y - 2, 0, hintCol.c_str());
                offset++;
            }
            else if (hintCol == "" and i == 0) {
                hintCol = "0";

                int x = square + j * square + startX;
                int y = startY - offset * square;
                al_draw_scaled_bitmap(boxes[2], 0, 0, al_get_bitmap_width(boxes[2]), al_get_bitmap_height(boxes[2]), x, y, square, square, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), x + 2, y - 2, 0, hintCol.c_str());
            }
            if (maior < offset) { maior = offset - 1; }

        }
    }
    return maior;
}

int gridLogic(int startX, int startY, int square, int gameWidth, int gameHeight, ALLEGRO_BITMAP* boxes[], ALLEGRO_FONT* font, int mouseX, int mouseY, int mouse, std::vector<std::vector<int>> coords, std::vector<std::vector<int>>& playerCoords, int *playerBlacks, int *playerLifes, ALLEGRO_BITMAP* canvas, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* hintsCanvas, int Mx, int My) {
    al_set_target_bitmap(canvas);
    int width = gameWidth + 1;
    int height = gameHeight + 1;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int x = i * square + startX;
            int y = j * square + startY;

            if (i > 0 && j > 0) {
                int corBox;
                int player = playerCoords[j - 1][i - 1];
                int gabarito = coords[j - 1][i - 1];

                if (mouseX >= x && x + square > mouseX && mouseY >= y && y + square > mouseY) {
                    if (player != 1 && player != 5) {
                        if (mouse == 1) {
                            if (gabarito == 1) {
                                playerCoords[j - 1][i - 1] = 1;
                                (*playerBlacks)++;
                            }
                            else { 
                                playerCoords[j - 1][i - 1] = 5;
                                (*playerLifes)--;
                            }
                        }
                        else if (mouse == 2) {
                            if (player == 0) { playerCoords[j - 1][i - 1] = 4; }
                            else if (player == 4) { playerCoords[j - 1][i - 1] = 0; }
                        }
                    }

                    if (player == 0) { corBox = 3; }
                    else { corBox = player; }
                }
                else { corBox = player; }
                al_draw_scaled_bitmap(boxes[corBox], 0, 0, al_get_bitmap_width(boxes[corBox]), al_get_bitmap_height(boxes[corBox]), x, y, square, square, 0);
            }
            else {
                al_draw_scaled_bitmap(boxes[2], 0, 0, al_get_bitmap_width(boxes[2]), al_get_bitmap_height(boxes[2]), x, y, square, square, 0);
            }
        }
    }
    
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_filled_rectangle(width * square + startX, height * square + startY, startX - Mx * square, startY - My * square, al_map_rgb(200, 200, 200));
    al_draw_bitmap(canvas, 0, 0, 0);
    al_draw_bitmap(hintsCanvas, 0, 0, 0);
    

    return 0;
}
int fase(ALLEGRO_DISPLAY* display, int *pFasesDesb, int level, int returnScreen) {
    novaTela = returnScreen;
    int now_w = al_get_display_width(display);
    int now_h = al_get_display_height(display);
    ALLEGRO_BITMAP* back = al_load_bitmap("./assets/img/back.png");

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_mouse();

    ALLEGRO_BITMAP* boxes[6] = {
    al_load_bitmap("./assets/img/whiteBox.png"),
    al_load_bitmap("./assets/img/blackBox.png"),
    al_load_bitmap("./assets/img/grayBox.png"),
    al_load_bitmap("./assets/img/hoverBox.png"),
    al_load_bitmap("./assets/img/flagBox.png"),
    al_load_bitmap("./assets/img/wrongBox.png")
    };

    char buffer[50];
    std::vector<std::vector<int>> coords = criarMatriz(level);
    
    int gameWidth = static_cast<int>(coords[0].size());
    int gameHeight = static_cast<int>(coords.size());

    std::vector<std::vector<int>> playerCoords(gameHeight, std::vector<int>(gameWidth));

    int gameBlacks = 0;
    int playerBlacks = 0;
    int playerLifes = 5;
    int pause = false;
    double beforeTime = al_get_time();
    double nowTime;

    for (int i = 0; i < gameWidth; i++) {
        for (int j = 0; j < gameHeight; j++) {
            playerCoords[j][i] = 0;
            if (coords[j][i] == 1) { gameBlacks++; }
        }
    }

    al_set_window_position(display, 0, 35);
    al_set_window_title(display, "ArtDeco");
    ALLEGRO_MOUSE_STATE state;
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
    ALLEGRO_BITMAP* pausa = al_load_bitmap("./assets/img/pausa.png");
    ALLEGRO_BITMAP* relogio = al_load_bitmap("./assets/img/relogio.png");
    ALLEGRO_BITMAP* noite_estrelada = al_load_bitmap("./assets/img/noite_estrelada.png");

    ALLEGRO_BITMAP* hintsCanvas = al_create_bitmap(now_w, now_h);
    int Mx = -1;
    int My = -1;
    while (true) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            novaTela = 0;
            break;
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            al_acknowledge_resize(display);
            now_w = al_get_display_width(display);
            now_h = al_get_display_height(display);
        }

        float scale_x = (float)now_w / WIDTH;
        float scale_y = (float)now_h / HEIGHT;

        ALLEGRO_FONT* font_tittle = al_load_font("./assets/fonts/CinzelDecorative-Regular.ttf", 50 * scale_y, 0);
        ALLEGRO_FONT* font_text = al_load_font("./assets/fonts/MontserratAlternates-Regular.ttf", 50 * scale_y, 0);
        ALLEGRO_FONT* font_text2 = al_load_font("./assets/fonts/MontserratAlternates-Regular.ttf", 40 * scale_y, 0);

        al_get_mouse_state(&state);
        int mouseX = state.x;
        int mouseY = state.y;
        int mouseB = state.buttons;
        int r = 0;
        int g = 0;
        int b = 0;


        al_clear_to_color(al_map_rgb(196, 196, 196));
        al_draw_scaled_bitmap(noite_estrelada, 0, 0, al_get_bitmap_width(noite_estrelada), al_get_bitmap_height(noite_estrelada), 190 * scale_x, 125 * scale_y, 1540 * scale_x, 735 * scale_y, 0);
        al_draw_scaled_bitmap(moldura, 0, 0, al_get_bitmap_width(moldura), al_get_bitmap_height(moldura), -180 * scale_x, -73 * scale_y, 2220 * scale_x, 1165 * scale_y, 0);
        
        faseTitle(level, buffer, sizeof(buffer));
        al_draw_text(font_tittle, al_map_rgba(0, 0, 0, 70), now_w / 2 - 5 * scale_x, 155 * scale_y, ALLEGRO_ALIGN_CENTER, buffer);
        al_draw_text(font_tittle, al_map_rgb(0, 0, 0), now_w / 2, 150 * scale_y, ALLEGRO_ALIGN_CENTER, buffer);

        if (mouseX > 1620 * scale_x && mouseX < 1680 * scale_x && mouseY > 170 * scale_y && mouseY < 230 * scale_y) {
            r = 228;
            g = 195;
            b = 78;
            if (mouseB == 1) {
                nowTime = al_get_time();
                if(nowTime - beforeTime >= 0.25){
                    pause = ~pause;
                    beforeTime = nowTime;
                }
               
            }
        }
        else { r = 196; g = 196; b = 196; }

        al_draw_filled_circle(1645 * scale_x, 205 * scale_y, 30 * scale_y, al_map_rgba(0, 0, 0, 70));
        al_draw_filled_circle(1650 * scale_x, 200 * scale_y, 30 * scale_y, al_map_rgb(r, g, b));
        al_draw_circle(1650 * scale_x, 200 * scale_y, 30 * scale_y, al_map_rgb(0, 0, 0), 1.5);
        al_draw_scaled_bitmap(pausa, 0, 0, al_get_bitmap_width(pausa), al_get_bitmap_height(pausa), 1625 * scale_x, 175 * scale_y, 50*scale_x, 50* scale_y, 0);

        snprintf(buffer, sizeof(buffer), "%.2f%%", (float)playerBlacks/gameBlacks*100);
        al_draw_filled_rectangle(now_w / 4 - 150 * scale_x, 350 * scale_y, now_w / 4 + 150 * scale_x, 575 * scale_y, al_map_rgba(240, 209, 86, 70));
        al_draw_rectangle(now_w / 4 - 150 * scale_x, 350 * scale_y, now_w / 4 + 150 * scale_x, 575 * scale_y, al_map_rgb(0, 0, 0), 1);
        al_draw_text(font_text2, al_map_rgb(0, 0, 0), 475 * scale_x, 360 * scale_y, ALLEGRO_ALIGN_CENTER, "Progresso");
        al_draw_text(font_text2, al_map_rgb(0, 0, 0), 475 * scale_x, 450 * scale_y, ALLEGRO_ALIGN_CENTER, buffer );

        snprintf(buffer, sizeof(buffer), "%d", playerLifes);
        al_draw_filled_rectangle(now_w / 4 - 150 * scale_x, 575 * scale_y, now_w / 4 + 150 * scale_x, 800 * scale_y, al_map_rgba(240, 209, 86, 70));
        al_draw_rectangle(now_w / 4 - 150 * scale_x, 575 * scale_y, now_w / 4 + 150 * scale_x, 800 * scale_y, al_map_rgb(0, 0, 0), 1);
        al_draw_text(font_text2, al_map_rgb(0, 0, 0), 475 * scale_x, 590 * scale_y, ALLEGRO_ALIGN_CENTER, "Vidas");
        al_draw_text(font_text2, al_map_rgb(0, 0, 0), 475 * scale_x, 680 * scale_y, ALLEGRO_ALIGN_CENTER, buffer);
          
        //CHEAT SQUARE - clique nessa região e passe a tela automaticamente (DEBUG)
        //al_draw_filled_rectangle(now_w - 50 * scale_x, 150 * scale_y, now_w, 220 * scale_y, al_map_rgb(255, 255, 255));
        if (mouseX > now_w - 50 * scale_x && mouseX < now_w && mouseY >  150 * scale_y && mouseY < 220 * scale_y) {
            if (mouseB == 1) {
                playerBlacks = gameBlacks;
            }
        }
        else { r = 196; g = 196; b = 196; }

        int squareS;
        if (gameWidth < gameHeight) { squareS = (int)round(450 * scale_y / (gameHeight + 1)); }
        else { squareS = (int)round(450 * scale_x / (gameWidth + 1)); }
        ALLEGRO_FONT* fontHint = al_load_font("./assets/fonts/CinzelDecorative-Regular.ttf", squareS + 1*scale_y, 0);
        
        if (pause == false) {
            if (playerLifes > 0) {
                int x0 = (int)round(now_w / 2 - 112 * scale_x);
                int y0 = (int)round(350 * scale_y);
                ALLEGRO_BITMAP* canvas = al_create_bitmap(now_w, now_h);

                if (Mx == -1) {
                    al_set_target_bitmap(hintsCanvas);
                    Mx = makeRowHints(x0, y0, fontHint, squareS, boxes, gameWidth, gameHeight, coords);
                    My = makeColHints(x0, y0, fontHint, squareS, boxes, gameWidth, gameHeight, coords);
                    al_set_target_bitmap(al_get_backbuffer(display));
                }


                gridLogic(x0, y0, squareS, gameWidth, gameHeight, boxes, fontHint, mouseX, mouseY, mouseB, coords, playerCoords, &playerBlacks, &playerLifes, canvas, display, hintsCanvas, Mx, My);
                if (gameBlacks == playerBlacks) {
                    *pFasesDesb = 1;
                    al_draw_text(font_text2, al_map_rgb(0, 0, 0), now_w / 2, 210 * scale_y, ALLEGRO_ALIGN_CENTER, "Quadro Completo!");
                }
                al_destroy_bitmap(canvas);
            }
            else {
                al_draw_text(font_text2, al_map_rgb(0, 0, 0), now_w / 2, 210 * scale_y, ALLEGRO_ALIGN_CENTER, "Game Over");
            }
        }
        else {
            al_draw_filled_rectangle(now_w / 2 - 250 * scale_x, now_h/2 - 200 * scale_y, now_w / 2 + 250 * scale_x, now_h/2 + 100 * scale_y, al_map_rgb(255, 255, 255));
            al_draw_rectangle(now_w / 2 - 250 * scale_x, now_h/2 - 200 * scale_y, now_w / 2 + 250 * scale_x, now_h/2 + 100 * scale_y, al_map_rgb(0, 0, 0), 1);
            al_draw_text(font_text2, al_map_rgb(0, 0, 0), now_w / 2, now_h/2 - 180 * scale_y, ALLEGRO_ALIGN_CENTER, "Menu");


            if (mouseX > now_w / 2 - 150 * scale_x && mouseX < now_w / 2 + 150 * scale_x && mouseY > now_h / 2 - 100 * scale_y && mouseY < now_h / 2 - 20 * scale_y){
                r = 225;
                g = 190;
                b = 0;
                if (mouseB == 1) {
                    if (gameBlacks != playerBlacks) {novaTela = level + 12;}
                    else if (level < 29) { novaTela = level + 13; }
                    else { novaTela = 11; }
                    break;
                }
            }
            else { r = 0; g = 0; b = 0; }
            al_draw_filled_rectangle(now_w / 2 - 150 * scale_x, now_h / 2 - 100 * scale_y, now_w / 2 + 150 * scale_x, now_h / 2 - 20 * scale_y, al_map_rgb(50, 116, 177));
            al_draw_rectangle(now_w / 2 - 150 * scale_x, now_h / 2 - 100 * scale_y, now_w / 2 + 150 * scale_x, now_h / 2 - 20 * scale_y, al_map_rgb(0, 0, 0), 1);
            if (gameBlacks != playerBlacks) { snprintf(buffer, sizeof(buffer), "Reiniciar"); }
            else if (level < 29) { snprintf(buffer, sizeof(buffer), "Próxima Fase"); }
            else{ snprintf(buffer, sizeof(buffer), "Galeria"); }
            al_draw_text(font_text2, al_map_rgb(r, g, b), now_w / 2, now_h / 2 - 85 * scale_y, ALLEGRO_ALIGN_CENTER, buffer);

            if (mouseX > now_w / 2 - 150 * scale_x && mouseX < now_w / 2 + 150 * scale_x && mouseY > now_h / 2 && mouseY < now_h / 2 + 80 * scale_y) {
                r = 225;
                g = 190;
                b = 0;
                if (mouseB == 1) {
                    novaTela = returnScreen;
                    break;
                }
            }
            else { r = 0; g = 0; b = 0; }
            al_draw_filled_rectangle(now_w / 2 - 150 * scale_x, now_h / 2, now_w / 2 + 150 * scale_x, now_h / 2 + 80 * scale_y, al_map_rgb(50, 116, 177));
            al_draw_rectangle(now_w / 2 - 150 * scale_x, now_h / 2, now_w / 2 + 150 * scale_x, now_h / 2 + 80 * scale_y, al_map_rgb(0, 0, 0), 1);
            al_draw_text(font_text2, al_map_rgb(r, g, b), now_w / 2, now_h / 2 + 15 * scale_y, ALLEGRO_ALIGN_CENTER, "Sair");

        }

        al_flip_display();
        al_destroy_font(font_tittle);
        al_destroy_font(font_text);
        al_destroy_font(font_text2);
        al_destroy_font(fontHint);
        
    }

    al_destroy_bitmap(moldura);
    al_destroy_bitmap(hintsCanvas);
    al_destroy_event_queue(event_queue);
    al_destroy_mouse_cursor(cursor);
    al_destroy_bitmap(pincel_cursor);

    return novaTela;
    }
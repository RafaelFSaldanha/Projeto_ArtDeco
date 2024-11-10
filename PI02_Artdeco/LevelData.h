#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <allegro5/allegro.h>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> criarMatriz(int level);
int getGameWidth(int level);
int getGameHeight(int level);
#endif

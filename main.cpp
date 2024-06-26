#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include<random>
#include<fstream>
#define g 1
#define fric 0.6
#define PI 22 / 7

using namespace std;
using namespace sf;


float window_x = 1880, window_y = 950, tile_width = 268, tile_height = 149, loop_width = 536, loop_height = 298, shapes_width = 89.33333, shapes_height = 149;
const int tile_y = 10, tile_x = 70;//number of tiles on x and y axis

int cnt = 0, cnt1 = 0, op_animation = 0, cnt3 = 0, cv = 50, cv2 = 3, scr = 0,scov=0;
bool cvm = false, cvp = false, msg = false, inmain = true;


//sprites
Sprite main_menu, play, options, credits, quit, katkot, zeroo, twoo, threee, four, five, credit, background, pic_credits, gameOver;
Text score;
Sprite sonic, finish, hor_ground[tile_y][tile_x], slope[tile_y][tile_x], curve[tile_y][tile_x], jumper_h[tile_y][tile_x], jumper[tile_y][tile_x], loop[tile_y][tile_x], coin[tile_y][tile_x * 3], crab[tile_y][tile_x], na7la[tile_y][tile_x], bullet[tile_x], tree[tile_y][tile_x], spikes[tile_y][tile_x];

//tile map
/*
1 : horizontal ground
2 : positive slope ground
3 : negative slope
4 : curve
5 : rest of curve
6 : under positive slope
7 : under negative slope
8 : spikes
10: obstacle
11 : tile not to make sonic fall when going to horizontal ground from sloped or curved one

1  2  3  4  5  6  7  8   9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70  */
int tile_map[tile_y][tile_x] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,10, 0, 0,10, 0, 0, 0, 0, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10, 0, 0, 0,10, 0, 0,10, 0, 0, 0, 0, 0, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10, 8, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 7, 3, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 2, 1, 1, 9, 0, 0, 0, 0, 7, 1, 1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


/*
6 : loop 1
7 : loop2
8 : loop3
9 : loop4

1  2  3  4  5  6  7  8   9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35  */
int loop_map[tile_y / 2][tile_x / 2] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

//jumper and enemies
// 1 : hor jumper
// 2 :right jumper
// 3 :left jumper
// -1 crab
// -2 na7la
//                                     1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67  68 69 70
int obstacle_map[tile_y][tile_x] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0,-2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-2, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

//coins and trees
//-3 : tree
// 1 : coin
//                                       1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70
int shapes_map[tile_y][tile_x * 3] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,-3,-3,-3,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3,-3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,-3,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-3,-3, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
//struct

//sonic
struct character {
	float x = 290, y = 200, v_x = 0, v_y = 0, a_x = 0.09, chrg_v = 0, width = 40.5 / 2, height = 44.5, av_x = 0, av_y = 0, angle = 0;
	int animation = 0, jump_animation = 0, charge_animation = 0, column = 500 / 254, row = 762 / 254, loop_column = 500 / 536, loop_row = 762 / 298, a_cnt = 0; //index of tile sonic is standing on;
	int atk_time = 0, death_cnt = 100, revive_cnt = 201, second_jump2 = 0, gameOver_cnt = 0, gover_music = 0, finish_cnt = 0;//counter b3ed beh sonic a3d ad ehh fy el attack
																															 //34an lazm a4el 2edy mn 3al space el awl
	bool moving = false, can_jump = true, in_curve = false, down_curve = false, user_control = true, knock_out = false, alive = true, game_over = false, won = false;
	bool looped1 = false, looped2 = false, looped3 = false, looped4 = false, attacking = false, draw = true, second_jump = false, infinish = false;//attack speed
	bool check_point = false;
}s;

//coins
struct shapess_map {
	int column = 500 / 89, row = 762 / 149, animation[tile_y][tile_x * 3];
	// s.x / shapes_width
	bool intersection[tile_y][tile_x * 3];

}c;

struct fallen_coins {
	int row = 0, column = 0;
	float x = 0, y = 0, v_x = 0, v_y = 0;

}f_c[tile_y][tile_x * 3];

//jumper
struct jumper {
	float v_y = 0;
	int cnt = 0, animation_cnt[tile_y][tile_x], snt[tile_y][tile_x];
	bool right = false, left = false, animate[tile_y][tile_x];
}j;

//enemy
struct enemies {
	float v_x = 2, v_y = 0, x = 0, y = 0;
	int animation = 0, atc_cnt = 0, atc_animation = 0;
	bool attacking = false, can_move = true;

}e[tile_y][tile_x], n7[tile_y][tile_x];

//bullet
struct projectiles {
	float x = 0, y = 0, v_x = 0, v_y = 0, angle = 0, fixed_v = 6;//the velocity that will be resolved in x and y dir
	int row = 0, column = 0;

}b[tile_x];

//keys_pressed
void key_pressed();

//obstacle
void obstacle();

//coin
void coins();

//sonic
void sonic_move();
void sonic_aninmation();
void charge();
void sonic_attack();
void sonic_hit();
void after_hit();
void sonic_death();

//ground functions
void Ground();

//from side
void ground_collisions();

//save & load
void save();
void save_newgame();
void load();
void load_newgame();
void checkPoint();

//enemies
void crabs(int i, int j);
void bee(int i, int j);
void enemy_collision();
void enemy_attack(int i, int j);
void bullet_collision(int i, int j);

//coins movement
void coin_movement(int i, int j);

void finish_();

//camera view
View view(FloatRect(0, 0, window_y, window_y));
//void camera_view();

void mainmenu(RenderWindow& window);
//music
SoundBuffer mss;
Sound ms;

SoundBuffer opmm;
Sound opm;

SoundBuffer scvv;
Sound scv;

SoundBuffer goverr;
Sound gover;

SoundBuffer shh;
Sound sh;

SoundBuffer deathh;
Sound death;

SoundBuffer jpss;
Sound jps;

int main()
{

	RenderWindow window(VideoMode(window_x, window_y), "Sonic", Style::Fullscreen);
	window.setFramerateLimit(60);

	view.setCenter(sonic.getPosition());


	//textures
	Texture tx, flat_ground, Slope, up_Hill, up_ground, jumperr_h, jumperr, loop1, loop2, loop3, loop4, coinn, crabb, cre, backgroundd, na7laa, tl2a, treee, GameOver, Spikes, finishh;
	tx.loadFromFile("asly.png");
	flat_ground.loadFromFile("ground3.png");
	Slope.loadFromFile("slope3.png");
	up_Hill.loadFromFile("under2.png");
	up_ground.loadFromFile("above1.png");
	jumperr.loadFromFile("ook.png");
	jumperr_h.loadFromFile("dkka.png");
	loop1.loadFromFile("looop11.png");
	loop2.loadFromFile("looop22.png");
	loop3.loadFromFile("looop3.png");
	loop4.loadFromFile("looop4.png");
	coinn.loadFromFile("coin.png");
	crabb.loadFromFile("crab.png");
	cre.loadFromFile("credits.png");
	backgroundd.loadFromFile("bgg.png");
	na7laa.loadFromFile("na7la.png");
	tl2a.loadFromFile("tl2a.png");
	treee.loadFromFile("tree.png");
	GameOver.loadFromFile("1..png");
	Spikes.loadFromFile("spikes.png");
	finishh.loadFromFile("finish.png");

	//sonic
	sonic.setTexture(tx);
	sonic.setOrigin(s.width, s.height);
	sonic.setPosition(s.x, s.y);
	sonic.setScale(2, 2);


	// finish
	finish.setTexture(finishh);
	finish.setTextureRect(IntRect(15, 0, 109, 115));
	finish.setPosition(17656, 637);
	finish.setOrigin(finish.getGlobalBounds().width/2,0);


	//game over
	gameOver.setTexture(GameOver);
	gameOver.setScale(1.022, 1.137);

	// Create the main window
	//texture
	Texture menu, playy, optionss, creditss, quitt, katkott, wallpaperr, two, three, fourr, fivee, pic_creditss;

	//menu
	menu.loadFromFile("p.c.png");
	main_menu.setTexture(menu);
	main_menu.setScale(1.022, 1.137);


	//play
	playy.loadFromFile("star.t.png");
	play.setTexture(playy);
	play.setScale(1.022, 1.137);

	//options
	optionss.loadFromFile("o.p.png");
	options.setTexture(optionss);
	options.setScale(1.022, 1.137);
	//credits
	creditss.loadFromFile("c.r.png");
	credits.setTexture(creditss);
	credit.setTexture(cre);
	credits.setScale(1.022, 1.137);
	//quit
	quitt.loadFromFile("e.x.png");
	quit.setTexture(quitt);
	quit.setScale(1.022, 1.137);
	//katkot
	katkott.loadFromFile("unknown 3.png");
	katkot.setTexture(katkott);
	katkot.setScale(2, 2);
	katkot.setPosition(50, 30);
	//options
	wallpaperr.loadFromFile("0.png");
	zeroo.setTexture(wallpaperr);
	zeroo.setScale(1.122, 1);

	two.loadFromFile("25.png");
	twoo.setTexture(two);
	twoo.setScale(1.122, 1);

	three.loadFromFile("50.png");
	threee.setTexture(three);
	threee.setScale(1.122, 1);

	fourr.loadFromFile("75.png");
	four.setTexture(fourr);
	four.setScale(1.122, 1);

	fivee.loadFromFile("100.png");
	five.setTexture(fivee);
	five.setScale(1.122, 1);

	pic_creditss.loadFromFile("credits.png");
	pic_credits.setTexture(pic_creditss);
	pic_credits.setScale(1.498, 1.498);

	//background
	background.setTexture(backgroundd);
	background.setOrigin(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2);

	//Music
	//game sound
	mss.loadFromFile("sonic song.wav");
    ms.setBuffer(mss);
	ms.setLoop(true);

	//sound options
	opmm.loadFromFile("oP.wav");
	opm.setBuffer(opmm);
	opm.setVolume(cv);
	opm.setLoop(true);
	opm.play();

	//coin sound
	scvv.loadFromFile("coin sound.wav");
	scv.setBuffer(scvv);

	//game over sound
	goverr.loadFromFile("game over.wav");
	gover.setBuffer(goverr);

	//sound hit
	shh.loadFromFile("hit.wav");
	sh.setBuffer(shh);

	//sound death
	deathh.loadFromFile("death.wav");
	death.setBuffer(deathh);
	//sound jumper
	jpss.loadFromFile("jump sound.wav");
	jps.setBuffer(jpss);

	//score
	Font scoree;
	scoree.loadFromFile("NiseSegaSonic.TTF");
	score.setFont(scoree);

	score.setFillColor(Color::Black);
	score.setCharacterSize(34);


	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			coin[i][j].setTexture(coinn);

			//tree
			if (shapes_map[i][j * 3] == -3) {
				tree[i][j * 3].setTexture(treee);
				tree[i][j * 3].setOrigin(tree[i][j * 3].getGlobalBounds().width / 2, tree[i][j * 3].getGlobalBounds().height);
				tree[i][j * 3].setScale(1.5, 4);
				tree[i][j * 3].setPosition(j * 3 * shapes_width, i * shapes_height + 52);
			}
			if (shapes_map[i][(j * 3) + 1] == -3) {
				tree[i][(j * 3) + 1].setTexture(treee);
				tree[i][(j * 3) + 1].setOrigin(tree[i][(j * 3) + 1].getGlobalBounds().width / 2, tree[i][(j * 3) + 1].getGlobalBounds().height);
				tree[i][(j * 3) + 1].setScale(1.5, 4);
				tree[i][(j * 3) + 1].setPosition(((j * 3) + 1) * shapes_width, i * shapes_height + 52);
			}
			if (shapes_map[i][(j * 3) + 2] == -3) {
				tree[i][(j * 3) + 2].setTexture(treee);
				tree[i][(j * 3) + 2].setOrigin(tree[i][(j * 3) + 2].getGlobalBounds().width / 2, tree[i][(j * 3) + 2].getGlobalBounds().height);
				tree[i][(j * 3) + 2].setScale(1.5, 4);
				tree[i][(j * 3) + 2].setPosition(((j * 3) + 2) * shapes_width, i * shapes_height + 52);
			}
			//coin
			if (shapes_map[i][j * 3] == 1) {
				coin[i][j * 3].setTexture(coinn);
				coin[i][j * 3].setPosition(j * 3 * shapes_width, i * shapes_height + 100);
				coin[i][j * 3].setScale(0.3, 0.3);
			}
			if (shapes_map[i][(j * 3) + 1] == 1) {
				coin[i][(j * 3) + 1].setTexture(coinn);
				coin[i][(j * 3) + 1].setPosition(((j * 3) + 1) * shapes_width, i * shapes_height + 100);
				coin[i][(j * 3) + 1].setScale(0.3, 0.3);
			}
			if (shapes_map[i][(j * 3) + 2] == 1) {
				coin[i][(j * 3) + 2].setTexture(coinn);
				coin[i][(j * 3) + 2].setPosition(((j * 3) + 2) * shapes_width, i * shapes_height + 100);
				coin[i][(j * 3) + 2].setScale(0.3, 0.3);
			}
			//texture el bullet
			if (i == 0) {
				bullet[j].setTexture(tl2a);
			}

			//horizontal ground
			if (tile_map[i][j] == 1) {
				hor_ground[i][j].setTexture(flat_ground);
				hor_ground[i][j].setPosition(j * tile_width, i * tile_height);
				hor_ground[i][j].setScale(1.1, 0.8);
			}
			// positive slope
			else if (tile_map[i][j] == 2) {
				slope[i][j].setTexture(Slope);
				slope[i][j].setPosition(j * tile_width, i * tile_height);
				slope[i][j].setScale(1, 1);
			}
			//negative slope
			else if (tile_map[i][j] == 3) {
				slope[i][j].setTexture(Slope);
				slope[i][j].setScale(-1, 1);
				slope[i][j].setOrigin(268, 0);
				slope[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//curve
			else if (tile_map[i][j] == 4) {
				curve[i][j].setTexture(up_Hill);
				curve[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//rest of curve
			else if (tile_map[i][j] == 5) {
				curve[i][j].setTexture(up_ground);
				curve[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//spikes
			else if (tile_map[i][j] == 8) {
				spikes[i][j].setTexture(Spikes);
				spikes[i][j].setPosition(j * tile_width, i * tile_height + 77);
			}
			//loop
			else if (loop_map[i][j] == 6) {
				loop[i][j].setTexture(loop1);
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 7) {
				loop[i][j].setTexture(loop2);
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 8) {
				loop[i][j].setTexture(loop3);
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 9) {
				loop[i][j].setTexture(loop4);
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}

			//jumper
			if (obstacle_map[i][j] == 1) {
				jumper_h[i][j].setTexture(jumperr_h);
				jumper_h[i][j].setTextureRect(IntRect(103.7, 0, 103.7, 78));
				jumper_h[i][j].setPosition(j * tile_width + 134, i * tile_height + 74);
				//jumper[i][j].setScale(3, 1.5);
				jumper_h[i][j].setOrigin(jumper[i][j].getGlobalBounds().width / 2, jumper[i][j].getGlobalBounds().height / 8);
			}
			if (obstacle_map[i][j] == 2) {
				jumper[i][j].setTexture(jumperr);
				jumper[i][j].setTextureRect(IntRect(0, 0, 43, 51));
				jumper[i][j].setPosition(j * tile_width - 14, i * tile_height);
				jumper[i][j].setScale(1.5, 1.5);
			}
			if (obstacle_map[i][j] == 3) {
				jumper[i][j].setTexture(jumperr);
				jumper[i][j].setTextureRect(IntRect(0, 0, 43, 51));
				jumper[i][j].setPosition(j * tile_width + 283, i * tile_height);
				jumper[i][j].setScale(-1.5, 1.5);

			}

			//enemy
			if (obstacle_map[i][j] == -1) {
				crab[i][j].setTexture(crabb);
				crab[i][j].setPosition(j * tile_width, i * tile_height + 82);
				crab[i][j].setScale(1.8, 1.8);
			}
			else if (obstacle_map[i][j] == -2) {
				na7la[i][j].setTexture(na7laa);
				na7la[i][j].setOrigin(na7la[i][j].getGlobalBounds().width / 8, na7la[i][j].getOrigin().y);
				na7la[i][j].setPosition(j * tile_width + 30, i * tile_height + 100);
				na7la[i][j].setScale(-1.5, 1.5);
			}
		}
	}

	//b3ml save ll initial values elly bd2 beha
	save_newgame();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				save();
				window.close();

			}

		}
		score.setString("Score: " + to_string(scr));
		mainmenu(window);

		//window.setView(view);

	}

	return 0;
}

void key_pressed() {


	s.moving = false;

	if (Keyboard::isKeyPressed(Keyboard::Key::S) && Keyboard::isKeyPressed(Keyboard::Key::LShift) && abs(s.v_x) < 16 && s.can_jump && !s.in_curve /* && s.death_cnt > 100b4of lw hwa lessa madrob ybtl charge */) {
		charge();

	}
	if (Keyboard::isKeyPressed(Keyboard::Key::LControl) && Keyboard::isKeyPressed(Keyboard::Key::S)) {
		save();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::LControl) && Keyboard::isKeyPressed(Keyboard::Key::L)) {
		load_newgame();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::A) && s.user_control || Keyboard::isKeyPressed(Keyboard::Key::Left) && s.user_control) {
		s.moving = true;
		if (s.v_x > 0) {
			s.v_x -= fric;
		}
		if (s.v_x > -15) {
			s.v_x -= s.a_x;
		}
		sonic.setScale(-2, 2);
		//s.animation++;

	}

	if (Keyboard::isKeyPressed(Keyboard::Key::D) && s.user_control || Keyboard::isKeyPressed(Keyboard::Key::Right) && s.user_control) {

		s.moving = true;
		if (s.v_x < 0) {

			s.v_x += fric;
		}
		sonic.setScale(2, 2);
		if (s.v_x < 15) {

			s.v_x += s.a_x;
		}

	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && s.can_jump && !s.in_curve && s.user_control) {

		s.v_y = -20;
		s.can_jump = false;
	}

	/*if (!Keyboard::isKeyPressed(Keyboard::Key::Space) && !s.can_jump) {
	s.second_jump2 = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && !s.can_jump && !s.in_curve && s.user_control && !s.second_jump && s.second_jump2) {
	if (sonic.getScale().x > 0) {
	s.v_x += 10;
	}
	else {
	s.v_x -= 10;
	}
	s.second_jump = true;
	s.second_jump2 = false;
	}*/

	if ((!Keyboard::isKeyPressed(Keyboard::Key::S) || !Keyboard::isKeyPressed(Keyboard::Key::LShift)) && abs(s.chrg_v) > 0) {
		s.v_x += s.chrg_v;
		s.chrg_v = 0;
		s.can_jump = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && Keyboard::isKeyPressed(Keyboard::Key::LShift) && !s.attacking && s.a_cnt > 70 && abs(s.v_x) < 15) {
		s.attacking = true;
	}
}

void sonic_move() {

	if (!s.looped3) {
		sonic.move(s.v_x, s.v_y);
	}

	s.x = sonic.getPosition().x;
	s.column = s.x / tile_width;
	s.loop_column = s.x / loop_width;
	c.column = s.x / shapes_width;

	s.y = sonic.getPosition().y;
	s.row = s.y / tile_height;
	s.loop_row = s.y / loop_height;
	c.row = s.y / shapes_height;

	if (!s.can_jump) {

		sonic.setTextureRect(IntRect((s.jump_animation) * 35, 187, 35, 32));
		s.jump_animation++;
		s.jump_animation %= 5;
		s.v_y += g;
	}

	if (s.v_x > 15) {
		s.v_x -= fric;

	}

	else if (s.v_x < -15) {
		s.v_x += fric;
	}

	else if (!s.moving && abs(s.v_x) <= 15 && s.v_x != 0) {

		if (tile_map[s.row][s.column] != 0 && !s.in_curve) {
			sonic.setTextureRect(IntRect((s.animation / 10) * 55, 254, 55, 43));
			s.animation++;
			s.animation %= 40;
		}

		if (sonic.getScale().x > 0) {
			if (s.v_x - fric < 0) {
				s.v_x = 0;
			}
			else {
				s.v_x -= fric;
			}

		}
		else if (sonic.getScale().x < 0) {
			if (fric + s.v_x > 0) {

				s.v_x = 0;
			}
			else {
				s.v_x += fric;
			}
		}
	}

}

void Ground() {
	if (s.alive) {

		s.in_curve = false;
		s.user_control = true;
		sonic.setRotation(0);

		if (loop_map[s.loop_row][s.loop_column] == 0) {
			s.looped1 = false;
			s.looped2 = false;
			s.looped3 = false;
			s.looped4 = false;
		}

		//horizontal ground
		if (tile_map[s.row][s.column] == 1) {
			s.v_y = 0;
			s.can_jump = true;
			sonic.setPosition(s.x, s.row * tile_height);
		}

		//postitve slope
		else if (tile_map[s.row][s.column] == 2) {

			if (s.y + s.v_y > (tile_height * (1 + s.row)) - (0.55597 * (s.x - (s.column * tile_width))) || (s.y + s.v_y < (tile_height * (1 + s.row)) - (0.55597 * (s.x - (s.column * tile_width))) && s.can_jump)) {
				s.v_y = 0;
				s.can_jump = true;
				sonic.setRotation(-30);
				sonic.setPosition(s.x, (tile_height * (1 + s.row)) - (0.55597 * (s.x - (s.column * tile_width))));

				if (tile_map[s.row + 1][s.column - 1] == 2 && s.can_jump && s.v_x + s.x < tile_width * s.column) {
					s.v_y = 0;
					s.can_jump = true;
					sonic.setRotation(-30);
					sonic.setPosition(s.x + s.v_x, (tile_height * (1 + s.row)) - (0.55597 * (s.x + s.v_x - (s.column * tile_width))));
				}

				else if (tile_map[s.row - 1][s.column + 1] != 2 && s.can_jump && s.v_x + s.x >= tile_width * (s.column + 1)) {
					s.v_y = -s.v_x / 7;
					s.can_jump = false;
				}
			}
		}

		//under positive slope
		else if (tile_map[s.row][s.column] == 6) {
			s.v_y = 0;
			s.can_jump = true;
			sonic.setRotation(-30);
			sonic.setPosition(s.x, (tile_height * (s.row)) - (0.55597 * (s.x - (s.column * tile_width))));

		}

		//negative slope
		else if (tile_map[s.row][s.column] == 3) {
			if (s.y + s.v_y > (s.row * tile_height) + 0.55597 * (s.x - (s.column * tile_width)) || (s.y + s.v_y < (s.row * tile_height) + 0.55597 * (s.x - (s.column * tile_width)) && s.can_jump)) {
				s.v_y = 0;
				s.can_jump = true;
				sonic.setPosition(s.x, (s.row * tile_height) + 0.55597 * (s.x - (s.column * tile_width)));
				//s.v_x += 0.2;
				sonic.setRotation(30);

				if (tile_map[s.row + 1][s.column + 1] == 3 && s.can_jump && s.v_x + s.x > tile_width * (s.column + 1)) {
					s.v_y = 0;
					s.can_jump = true;
					sonic.setRotation(30);
					sonic.setPosition(s.x + s.v_x, (s.row * tile_height) + 0.55597 * ((s.x + s.v_x) - (s.column * tile_width)));
				}

				else if (tile_map[s.row - 1][s.column - 1] != 3 && s.can_jump && s.v_x + s.x < tile_width * s.column) {
					s.v_y = s.v_x / 7;
					s.can_jump = false;
				}
			}

		}

		//under negative slope
		else if (tile_map[s.row][s.column] == 7) {
			s.v_y = 0;
			s.can_jump = true;
			sonic.setPosition(s.x, ((s.row - 1) * tile_height) + 0.55597 * (s.x - (s.column * tile_width)));

			sonic.setRotation(30);

		}

		//curve
		else if (tile_map[s.row][s.column] == 4) {

			if (s.y + s.v_y > 2 * sqrt(888 * (25 - (pow(s.x - (s.column * tile_width), 2) / 2873))) + ((s.row - 1) * tile_height) || (s.y + s.v_y < 2 * sqrt(888 * (25 - (pow(s.x - (s.column * tile_width), 2) / 2873))) + ((s.row - 1) * tile_height) && s.can_jump)) {

				s.can_jump = true;
				s.in_curve = true;
				s.v_x -= (s.x - s.column * tile_width) / 150.0;

				//if velocity + position will make him pass the whole curve
				if (s.v_x + s.x - (s.column * tile_width) >= 268) {

					sonic.setPosition(s.column * tile_width + 268, tile_height * s.row - 149);
					s.v_y = -s.v_x;
					s.v_x = 10;
					if (s.v_y < -15) {
						s.v_y = -15;
					}
				}
				//equation of curve
				else {
					sonic.setPosition(s.x, 2 * sqrt(888 * (25 - (pow(s.x - (s.column * tile_width), 2) / 2873))) + ((s.row - 1) * tile_height));
				}
				s.v_y = 0;
			}
			else {
				s.can_jump = false;

			}

		}

		//rest of curve
		else if (tile_map[s.row][s.column] == 5) {


			if (s.y + s.v_y > 2 * sqrt(888 * (25 - (pow((s.x) - (s.column * tile_width), 2) / 2873))) + ((s.row) * tile_height) || (s.y + s.v_y < 2 * sqrt(888 * (25 - (pow((s.x) - (s.column * tile_width), 2) / 2873))) + ((s.row) * tile_height) && s.can_jump)) {
				if (s.v_y > 5) {
					s.v_x = -5;
				}
				if (s.v_x > -15) {

					//if velocity + position will make him pass the whole curve
					if (s.x + s.v_x - (s.column * tile_width) >= 268 && s.v_x > 15) {
						sonic.setPosition(s.x, s.row * tile_height);
						s.v_y = -s.v_x;
						s.v_x = 10;
						if (s.v_y < -15) {
							s.v_y = -15;
						}
					}
					//equation of curve
					else {
						sonic.setPosition(s.x, 2 * sqrt(888 * (25 - (pow((s.x) - (s.column * tile_width), 2) / 2873))) + ((s.row) * tile_height));
					}
					s.can_jump = true;
					s.v_x -= (s.x - s.column * tile_width) / 150.0;
				}
				else {
					s.can_jump = false;
				}
			}
			else {
				s.can_jump = false;
			}
			//s.user_control = false;
			s.in_curve = true;
		}

		//spikes
		else if (tile_map[s.row][s.column] == 8) {
			if (s.y - s.row * tile_height > 80) {
				s.v_y = 0;
				sonic_hit();
				sonic.setPosition(s.x, s.row * tile_height + 81);
				s.can_jump = true;
			}
		}

		//under curve
		else if (tile_map[s.row][s.column] == 9) {

			sonic.setPosition(s.x, 2 * sqrt(888 * (25 - (pow(s.x - (s.column * tile_width), 2) / 2873))) + ((s.row - 2) * tile_height));
			s.v_y = 0;
		}

		//loop1
		else if (loop_map[s.loop_row][s.loop_column] == 6) {

			s.looped3 = false;
			if (!s.looped4) {
				//ard mostakema
				if (s.y + s.v_y > loop_height * s.loop_row + 261 && s.x - (loop_width * s.loop_column) > 150) {
					sonic.setPosition(s.x, loop_height * s.loop_row + 262);
					s.v_y = 0;
					s.can_jump = true;
				}
				else if (s.x - (loop_width * s.loop_column) < 150 && s.y + s.v_y > -0.047 * (s.x - (loop_width * s.loop_column)) + 269 + (loop_height * s.loop_row)) {
					sonic.setPosition(s.x, -0.047 * (s.x - (loop_width * s.loop_column)) + 269 + (loop_height * s.loop_row));
					s.can_jump = true;
				}
				else {
					s.can_jump = false;
				}
				s.looped1 = true;
			}
			else {

				if (s.v_x < 10) {
					if (s.v_x < -25) {
						s.v_x += 10;
					}
					s.v_x += (s.x - s.loop_column * loop_width) / 100;
				}

				sonic.setPosition(s.x, sqrt((271 * 271) - pow((s.loop_column + 1) * loop_width - s.x, 2)) + (s.loop_row * loop_height));
				s.can_jump = true;
				s.looped1 = false;
				s.in_curve = true;
				sonic.setRotation((((s.loop_column + 1) * loop_width - s.x) / 3.5));
			}

		}

		//loop2
		else if (loop_map[s.loop_row][s.loop_column] == 7) {
			if (!s.looped1) {
				s.looped2 = false;
				//el ard el mostakema
				if (s.y + s.v_y > loop_height * (s.loop_row + 1) - 2) {
					sonic.setPosition(s.x, loop_height * (s.loop_row + 1) - 1);
					s.v_y = 0;
					s.can_jump = true;
					s.looped4 = true;

				}
				else {
					s.can_jump = false;
				}
			}
			else {
				//lma y3dy ll rob3 elly b3do fy el loop
				if ((s.x + s.v_x) - s.loop_column * loop_width > 271) {
					if (!s.looped2) {
						sonic.setPosition(270.9 + s.loop_column * loop_width, sqrt((271 * 271) - pow(270.9, 2)) + ((s.loop_row) * loop_height));
						s.looped2 = true;
						s.user_control = false;
						sonic.move(-s.v_x, 0);
						sonic.setTextureRect(IntRect((s.animation / 7) * 45, 146, 45, 42));
						s.animation++;
						s.animation %= 28;
						sonic.setRotation(-(s.x - s.loop_column * loop_width) / 3.5);
					}
					else {
						sonic.setPosition(s.x - 0.5 * s.v_x, -sqrt((271 * 271) - pow(s.x - 0.5 * s.v_x - loop_width * s.loop_column, 2)) + s.loop_row * loop_height);
						s.v_x = 15;
						s.moving = false;
						sonic.setRotation((180 - (s.loop_column * loop_width - s.x) / 3.5));
					}

					sonic.setRotation(-(s.x - s.loop_column * loop_width) / 3.5);
				}
				//equation el rob3 dah 3ady
				else {
					s.v_x -= ((s.loop_column + 1) * loop_width - s.x) / 201;
					sonic.setPosition(s.x, sqrt((271 * 271) - pow(s.x - s.loop_column * loop_width, 2)) + ((s.loop_row) * loop_height));
					sonic.setRotation(-(s.x - s.loop_column * loop_width) / 3.5);
				}
				s.can_jump = true;
				s.in_curve = true;

			}
		}

		//loop3
		else if (loop_map[s.loop_row][s.loop_column] == 8) {

			s.looped2 = false;
			if (s.x + s.v_x - s.loop_column * loop_width > 271 && !s.looped3) {
				s.looped3 = true;
				sonic.setPosition(270.9 + loop_width * s.loop_column, -sqrt((271 * 271) - pow(270.9, 2)) + (s.loop_row + 1) * loop_height - 19.9);
				sonic.setRotation(-80);

			}
			//ama yro7 ll rob3 elly b3do
			else if (s.x - s.v_x - s.loop_column * loop_width <= 0) {
				sonic.setPosition(s.x - s.v_x, sqrt((271 * 271) - pow(s.loop_column * loop_width - (s.x - s.v_x), 2)) + ((s.loop_row - 1) * loop_height) + 65);
				sonic.setRotation((180 - (s.loop_column * loop_width - s.x) / 3.5));
			}

			else {
				//s.v_x -= ((s.loop_column + 1) * loop_width - s.x) / 201;
				sonic.setPosition(s.x - s.v_x, -sqrt((271 * 271) - pow(s.x - s.v_x - loop_width * s.loop_column, 2)) + (s.loop_row + 1) * loop_height);
				s.can_jump = true;
				sonic.setRotation(-(90 - (s.x - s.loop_column * loop_width) / 3.5) - 90);
			}
		}

		//loop4
		else if (loop_map[s.loop_row][s.loop_column] == 9) {

			s.looped2 = false;

			//lw 5ls el rob3 dah w da5el 3ally b3do
			if ((s.x - 0.5 * s.v_x) - s.loop_column * loop_width < 265) {

				sonic.setPosition(s.x, sqrt((271 * 271) - pow((s.loop_column + 1) * loop_width - s.x, 2)) + ((s.loop_row + 1) * loop_height));

			}

			// fy el rob3 dah
			else {

				if (s.v_x < 10) {
					s.v_x += (s.x - s.loop_column * loop_width) / 120;
				}

				sonic.setPosition(s.x - s.v_x, -sqrt((271 * 271) - pow((s.loop_column + 1) * loop_width - (s.x - s.v_x), 2)) + ((s.loop_row + 1) * loop_height));
				s.can_jump = true;
				s.looped4 = true;
				sonic.setRotation((180 - ((s.loop_column + 1) * loop_width - s.x) / 3.5));
			}
		}


		else if (loop_map[s.loop_row][s.loop_column] == 11) {
			sonic.setPosition(s.x, s.loop_row * loop_height - 2);
		}

		//not to fall from going from sloped ground to horizontal
		else if (tile_map[s.row][s.column] == 11) {
			sonic.setPosition(s.x, s.row * tile_height - 2);

		}

		else {

			//34an ama ym4y mn ard mayla l2aerd mostakema may3ml4 animation el jump
			if ((tile_map[s.row][s.column - 1] == 3 || tile_map[s.row][s.column + 1] == 2 || tile_map[s.row][s.column + 1] == 4 || loop_map[s.loop_row][s.loop_column + 1] == 6) && s.v_y < 2 && s.y - s.row * tile_height > 145) {

				sonic.setPosition(s.x, s.y + 1);
				if (abs(s.v_x) <= 6) {

					sonic.setTextureRect(IntRect((s.animation / 7) * 48, 56, 48, 49));
					s.animation++;
					s.animation %= 42;

				}
				else if (abs(s.v_x) <= 10) {
					sonic.setTextureRect(IntRect((s.animation / 7) * 45, 101, 45, 42));
					s.animation++;
					s.animation %= 28;
				}
				else {
					sonic.setTextureRect(IntRect((s.animation / 7) * 45, 146, 45, 42));
					s.animation++;
					s.animation %= 28;
				}

			}

			else {
				s.can_jump = false;
			}

		}
	}
}

void ground_collisions() {
	if (s.alive) {

		if (tile_map[s.row - 1][s.column + 1] == 10 || tile_map[s.row - 1][s.column + 1] == 1 || tile_map[s.row - 1][s.column + 1] == 8) {

			//if collided with ground from side while going right
			if (s.x + s.v_x >= (s.column * tile_width) + 235 && s.y > ((s.row - 2) * tile_height) - 80 && !s.in_curve) {
				sonic.setPosition((s.column * tile_width) + 235, s.y);
				s.chrg_v = 0;
				s.v_x = 0;
			}
		}

		//if collided with ground from side while going left
		if (tile_map[s.row - 1][s.column - 1] == 10 || tile_map[s.row - 1][s.column - 1] == 1 || tile_map[s.row - 1][s.column - 1] == 8) {
			if (s.x + s.v_x <= (s.column * tile_width) + 35 && s.y > ((s.row - 2) * tile_height) - 80) {
				sonic.setPosition((s.column * tile_width) + 35, s.y);
				s.v_x = 0;
				s.chrg_v = 0;
			}
		}
		if (tile_map[s.row][s.column + 1] == 1 && !s.in_curve) {
			if (s.x + s.v_x >= (s.column * tile_width) + 235 && !s.can_jump && s.v_x > 0 && s.y - s.row * tile_height > 90) {
				sonic.setPosition((s.column * tile_width) + 235, s.y);
				s.v_x = 0;
				s.chrg_v = 0;

			}
		}

		if (tile_map[s.row][s.column - 1] == 1) {
			if (s.x + s.v_x <= (s.column * tile_width) + 35 && !s.can_jump && s.v_x < 0 && s.y - s.row * tile_height > 90) {
				sonic.setPosition((s.column * tile_width) + 35, s.y);
				s.v_x = 0;
				s.chrg_v = 0;
			}
		}
		if (s.x + s.v_x < 30) {
			sonic.setPosition(35, s.y);
			s.v_x = 0;
		}
		/*if (obstacle_map[s.row - 1][s.column] == 1) {
		if (s.x - s.column * tile_width <= 110  && (s.x + s.v_x) - s.column * tile_width >= 110) {
		sonic.setPosition(s.column * tile_width + 109, s.y);
		s.v_x = 0;
		}
		else if (s.x - s.column * tile_width >= 215 && (s.x + s.v_x) - s.column * tile_width <= 215) {
		sonic.setPosition(s.column * tile_width + 216, s.y);
		s.v_x = 0;
		}
		}
		*/
	}
}

void sonic_aninmation() {

	sonic.setOrigin(s.width, s.height);
	//sonic.setTextureRect(IntRect(0, 0, 47, 60));

	if (s.v_x == 0 && s.v_y == 0) {

		sonic.setOrigin(s.width, s.height + 5);
		sonic.setTextureRect(IntRect((s.animation / 25) * 49, 0, 49, 55));
		s.animation++;
		s.animation %= 150;
		if (s.animation / 25 == 0 || s.animation / 25 == 1 || s.animation / 25 == 2) {
			s.animation = 75;
		}

	}

	if (s.can_jump && s.v_x != 0) {

		if (sonic.getScale().x < 0) {

			if (s.v_x >= -6) {
				//sonic.setOrigin(s.width, s.height - 5);
				sonic.setTextureRect(IntRect((s.animation / 7) * 48, 56, 48, 49));
				s.animation++;
				s.animation %= 42;

			}
			else if (s.v_x >= -10) {
				sonic.setOrigin(s.width, s.height - 2);
				sonic.setTextureRect(IntRect((s.animation / 7) * 45, 101, 45, 42));
				s.animation++;
				s.animation %= 28;
			}
			else {
				sonic.setOrigin(s.width, s.height - 5);

				sonic.setTextureRect(IntRect((s.animation / 7) * 45, 146, 45, 42));
				s.animation++;
				s.animation %= 28;
			}
		}
		else {
			if (s.v_x <= 6) {
				//sonic.setOrigin(s.width, s.height - 10);
				sonic.setTextureRect(IntRect((s.animation / 7) * 48, 56, 48, 49));
				s.animation++;
				s.animation %= 42;

			}
			else if (s.v_x <= 10) {
				sonic.setOrigin(s.width, s.height - 2);
				sonic.setTextureRect(IntRect((s.animation / 7) * 45, 101, 45, 42));
				s.animation++;
				s.animation %= 28;
			}
			else {
				sonic.setOrigin(s.width, s.height - 5);

				sonic.setTextureRect(IntRect((s.animation / 7) * 45, 146, 45, 42));
				s.animation++;
				s.animation %= 28;
			}
		}
	}

	if (abs(s.v_x) > 16 || abs(s.chrg_v) > 0) {
		sonic.setOrigin(s.width, s.height - 13);
		sonic.setTextureRect(IntRect(s.charge_animation * 36, 221, 36, 35));
		s.charge_animation++;
		s.charge_animation %= 6;
	}

}

void charge() {
	if (abs(s.chrg_v) < 60) {

		if (sonic.getScale().x > 0) {
			s.chrg_v += 1;
		}
		else {
			s.chrg_v -= 1;
		}
	}
	s.user_control = false;
	s.v_x = 0;
	s.v_y = 0;
	/*
	if (s.death_cnt < 120) {
	s.chrg_v = 0;
	s.v_x = 0;
	s.v_y = -10;
	}*/

}

//jumper
void obstacle() {

	if (s.alive) {
		//hor jumper
		if (obstacle_map[s.row][s.column] == 1) {

			if (sonic.getGlobalBounds().intersects(jumper_h[s.row][s.column].getGlobalBounds())) {
				s.user_control = false;
				j.animate[s.row][s.column] = true;
				s.v_y = -30;
				jps.play();
			}
		}
		else if (obstacle_map[s.row - 1][s.column] == 1) {

			if (sonic.getGlobalBounds().intersects(jumper_h[s.row - 1][s.column].getGlobalBounds())) {
				s.user_control = false;
				j.animate[s.row - 1][s.column] = true;
				s.v_y = -30;
				jps.play();
			}
		}

		else if (obstacle_map[s.row][s.column] == 2) {

			if (sonic.getGlobalBounds().intersects(jumper[s.row][s.column].getGlobalBounds())) {
				j.right = true;
				j.left = false;
				j.animate[s.row][s.column] = true;
				j.v_y = -((s.y - ((s.row - 1) * tile_height)) / 15);
				jps.play();
			}
		}
		else if (obstacle_map[s.row - 1][s.column] == 2) {

			if (sonic.getGlobalBounds().intersects(jumper[s.row - 1][s.column].getGlobalBounds())) {
				j.right = true;
				j.left = false;
				j.animate[s.row - 1][s.column] = true;
				j.v_y = -15;
				jps.play();
			}

		}
		else if (obstacle_map[s.row][s.column] == 3) {

			if (sonic.getGlobalBounds().intersects(jumper[s.row][s.column].getGlobalBounds())) {
				j.v_y = -((s.y - ((s.row - 1) * tile_height)) / 15);
				j.right = false;
				j.animate[s.row][s.column] = true;
				j.left = true;
				jps.play();
			}
		}
		else if (obstacle_map[s.row - 1][s.column] == 3) {

			if (sonic.getGlobalBounds().intersects(jumper[s.row - 1][s.column].getGlobalBounds())) {
				j.right = false;
				j.animate[s.row - 1][s.column] = true;
				j.left = true;
				j.v_y = -15;
				jps.play();
			}
		}
		if (j.right) {

			j.cnt++;
			if (j.cnt == 10) {
				j.right = false;
				j.cnt = 0;
			}
			s.user_control = false;
			s.v_y = j.v_y;
			s.v_x = 26;

		}
		else if (j.left) {

			j.cnt++;
			if (j.cnt == 10) {
				j.left = false;
				j.cnt = 0;
			}
			s.user_control = false;
			s.v_y = j.v_y;
			s.v_x = -26;
		}
	}
}

void coins() {

	if (s.alive) {
		//ama yb2a sonic fe nfs 2l tile bta3t 2l coin
		if (shapes_map[c.row][c.column] == 1 && !c.intersection[c.row][c.column] && s.y - (s.row * tile_height) >= 100) {
			shapes_map[c.row][c.column] = 0;
			coin[c.row][c.column].setScale(0, 0);
			c.intersection[c.row][c.column] = true;
			scr++;
			scv.play();
		}

		//ama yb2a 2l coin 3la ymen sonic (34an origin sonic fe nos)
		if (shapes_map[c.row][c.column + 1] == 1 && !c.intersection[c.row][c.column + 1] && s.y - (s.row * tile_height) >= 100) {
			if (c.column * shapes_width - s.x < s.width - 75) {
				shapes_map[c.row][c.column + 1] = 0;
				coin[c.row][c.column + 1].setScale(0, 0);
				c.intersection[c.row][c.column + 1] = true;
				scr++;
				scv.play();
			}
		}

		if (shapes_map[c.row - 1][c.column] == 1 && !c.intersection[c.row - 1][c.column] && s.y - ((s.row - 1) * tile_height) <= 200) {
			coin[c.row - 1][c.column].setScale(0, 0);
			shapes_map[c.row - 1][c.column] = 0;
			c.intersection[c.row - 1][c.column] = true;
			scr++;
			scv.play();
		}

		if (shapes_map[c.row - 1][c.column + 1] == 1 && !c.intersection[c.row - 1][c.column + 1] && s.y - ((s.row - 1) * tile_height) <= 200) {
			if (c.column * shapes_width - s.x < s.width - 75) {
				coin[c.row - 1][c.column + 1].setScale(0, 0);
				shapes_map[c.row - 1][c.column + 1] = 0;
				c.intersection[c.row - 1][c.column + 1] = true;
				scr++;
				scv.play();
			}
		}
	}
}

//collision of sonic with enemy
void enemy_collision() {

	if (s.alive) {
		//crab
		if (obstacle_map[s.row][s.column] == -1) {
			if (sonic.getGlobalBounds().intersects(crab[s.row][s.column].getGlobalBounds()) && !s.attacking && !s.knock_out) {
				crab[s.row][s.column].setScale(0, 0);
				obstacle_map[s.row][s.column] = 0;
				if (s.v_y > 0) {
					s.v_y = -15;
				}
			}
		}
		//crab
		if (obstacle_map[s.row - 1][s.column] == -1) {
			if (sonic.getGlobalBounds().intersects(crab[s.row - 1][s.column].getGlobalBounds()) && !s.attacking && !s.knock_out) {
				if (abs(s.v_x) > 16) {
					crab[s.row - 1][s.column].setScale(0, 0);
					obstacle_map[s.row - 1][s.column] = 0;
				}
				else {
					if (s.revive_cnt > 200) {
						sonic_hit();
					}
				}
			}
		}

		//n7la
		if (sonic.getGlobalBounds().intersects(na7la[s.row][s.column].getGlobalBounds()) && !s.attacking && !s.knock_out) {
			na7la[s.row][s.column].setScale(0, 0);
			obstacle_map[s.row][s.column] = 0;
			s.v_y = -15;
		}
	}
}

void sonic_attack() {

	if (s.alive) {
		if (s.a_cnt > 100000) {
			s.a_cnt = 50;
		}
		s.a_cnt++;

		if (s.attacking && s.av_x == 0 && s.av_y == 0 && !s.knock_out) {

			//lw sonic m3 el enemy fy nfs el tile ama sonic ynot
			if (obstacle_map[s.row][s.column] == -1 && ((sonic.getScale().x > 0 && e[s.row][s.column].x - s.x > 0) || (sonic.getScale().x < 0 && e[s.row][s.column].x - s.x < 0))) {

				s.av_x = ((e[s.row][s.column].x + 20) - s.x) / 6;
				s.av_y = ((e[s.row][s.column].y + 30) - s.y) / 6;

				e[s.row][s.column].can_move = false;

			}

			//ama sonic yb2a fo2 el enemy bs fnfs el column
			else if (obstacle_map[s.row + 1][s.column] == -1 && ((sonic.getScale().x > 0 && e[s.row + 1][s.column].x - s.x > 0) || (sonic.getScale().x < 0 && e[s.row + 1][s.column].x - s.x < 0))) {
				s.av_x = ((e[s.row + 1][s.column].x + 20) - s.x) / 6;
				s.av_y = ((e[s.row + 1][s.column].y + 30) - s.y) / 6;

				e[s.row + 1][s.column].can_move = false;

			}
			//sonic fy nfs tile el na7la
			else if (obstacle_map[s.row][s.column] == -2 && ((sonic.getScale().x > 0 && n7[s.row][s.column].x - s.x > 0) || (sonic.getScale().x < 0 && n7[s.row][s.column].x - s.x < 0))) {
				s.av_x = ((n7[s.row][s.column].x) - s.x) / 6;
				s.av_y = ((n7[s.row][s.column].y + 30) - s.y) / 6;

			}
			//sonic t7t el na7la b tile w fnfs el column
			else if (obstacle_map[s.row - 1][s.column] == -2 && ((sonic.getScale().x > 0 && n7[s.row - 1][s.column].x - s.x > 0) || (sonic.getScale().x < 0 && n7[s.row - 1][s.column].x - s.x < 0))) {
				s.av_x = ((n7[s.row - 1][s.column].x) - s.x) / 6;
				s.av_y = ((n7[s.row - 1][s.column].y + 30) - s.y) / 6;
			}
			//sonic fo2 el na7la b tile w fnfs el column
			else if (obstacle_map[s.row + 1][s.column] == -2 && ((sonic.getScale().x > 0 && n7[s.row + 1][s.column].x - s.x > 0) || (sonic.getScale().x < 0 && n7[s.row + 1][s.column].x - s.x < 0))) {
				s.av_x = ((n7[s.row + 1][s.column].x) - s.x) / 6;
				s.av_y = ((n7[s.row + 1][s.column].y + 30) - s.y) / 6;

			}
			//lw sonic wa2f 3la el ard w drb el n7la
			else if (obstacle_map[s.row - 2][s.column] == -2 && ((sonic.getScale().x > 0 && n7[s.row - 2][s.column].x - s.x > 0) || (sonic.getScale().x < 0 && n7[s.row - 2][s.column].x - s.x < 0))) {
				s.av_x = ((n7[s.row - 2][s.column].x) - s.x) / 6;
				s.av_y = ((n7[s.row - 2][s.column].y + 30) - s.y) / 6;
			}
			//sonic nfs row el n7la bs b3dha
			else if (obstacle_map[s.row][s.column - 1] == -2 && sonic.getScale().x < 0) {
				s.av_x = ((n7[s.row][s.column - 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row][s.column - 1].y + 30) - s.y) / 6;

			}
			//sonic b3d el n7la w t7taha b tile
			else if (obstacle_map[s.row - 1][s.column - 1] == -2 && sonic.getScale().x < 0) {
				s.av_x = ((n7[s.row - 1][s.column - 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row - 1][s.column - 1].y + 30) - s.y) / 6;

			}
			//sonic b3d el na7la w fo2ha b tile
			else if (obstacle_map[s.row + 1][s.column - 1] == -2 && sonic.getScale().x < 0) {
				s.av_x = ((n7[s.row + 1][s.column - 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row + 1][s.column - 1].y + 30) - s.y) / 6;

			}
			//sonic wa2f 3al2ard b3d el n7la b tile
			else if (obstacle_map[s.row - 2][s.column - 1] == -2 && sonic.getScale().x < 0) {
				s.av_x = ((n7[s.row - 2][s.column - 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row - 2][s.column - 1].y + 30) - s.y) / 6;

			}
			//sonic nfs row el n7la bs ablha
			else if (obstacle_map[s.row][s.column + 1] == -2 && sonic.getScale().x > 0) {
				s.av_x = ((n7[s.row][s.column + 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row][s.column + 1].y + 30) - s.y) / 6;

			}
			//sonic abl el n7la w t7taha b tile
			else if (obstacle_map[s.row - 1][s.column + 1] == -2 && sonic.getScale().x > 0) {
				s.av_x = ((n7[s.row - 1][s.column + 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row - 1][s.column + 1].y + 30) - s.y) / 6;

			}
			//sonic abl el n7la w fo2ha b tile
			else if (obstacle_map[s.row + 1][s.column + 1] == -2 && sonic.getScale().x > 0) {
				s.av_x = ((n7[s.row + 1][s.column + 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row + 1][s.column + 1].y + 30) - s.y) / 6;

			}
			//sonic wa2f 3al2ard abl el n7la b tile
			else if (obstacle_map[s.row - 2][s.column + 1] == -2 && sonic.getScale().x > 0) {
				s.av_x = ((n7[s.row - 2][s.column + 1].x) - s.x) / 6;
				s.av_y = ((n7[s.row - 2][s.column + 1].y + 30) - s.y) / 6;

			}

			//lw sonic abl el enemy b tile ama sonic ynot
			else if (obstacle_map[s.row][s.column + 1] == -1 && sonic.getScale().x > 0) {
				s.av_x = ((e[s.row][s.column + 1].x + 20) - s.x) / 6;
				s.av_y = ((e[s.row][s.column + 1].y + 30) - s.y) / 6;

				e[s.row][s.column + 1].can_move = false;

			}
			//lw sonic abl el enemy b tile w fo2o b tile ama sonic ynot
			else if (obstacle_map[s.row + 1][s.column + 1] == -1 && sonic.getScale().x > 0) {
				s.av_x = ((e[s.row + 1][s.column + 1].x + 20) - s.x) / 6;
				s.av_y = ((e[s.row + 1][s.column + 1].y + 30) - s.y) / 6;

				e[s.row + 1][s.column + 1].can_move = false;

			}
			//lw sonic b3d el enemy b tile ama sonic ynot
			else if (obstacle_map[s.row][s.column - 1] == -1 && sonic.getScale().x < 0) {
				s.av_x = ((e[s.row][s.column - 1].x + 20) - s.x) / 6;
				s.av_y = ((e[s.row][s.column - 1].y + 30) - s.y) / 6;

				e[s.row][s.column - 1].can_move = false;

			}
			//lw sonic b3d el enemy b tile w fo2o b tile ama sonic ynot
			else if (obstacle_map[s.row + 1][s.column - 1] == -1 && sonic.getScale().x < 0) {
				s.av_x = ((e[s.row + 1][s.column - 1].x + 20) - s.x) / 6;
				s.av_y = ((e[s.row + 1][s.column - 1].y + 30) - s.y) / 6;

				e[s.row + 1][s.column - 1].can_move = false;

			}

			else {
				s.attacking = false;
				s.av_x = 0;
				s.av_y = 0;
			}
		}

		else if (s.attacking && s.av_x != 0 && s.av_y != 0) {
			s.user_control = false;
			s.v_x = s.av_x;
			s.v_y = s.av_y;
			s.atk_time++;


			if (sonic.getGlobalBounds().intersects(crab[s.row][s.column].getGlobalBounds())) {

				s.attacking = false;
				s.av_x = 0;
				s.av_y = 0;
				s.v_x = s.v_x / 4;
				s.v_y = -15;
				crab[s.row][s.column].setScale(0, 0);
				obstacle_map[s.row][s.column] = 0;
				s.a_cnt = 0;
			}

			if (sonic.getGlobalBounds().intersects(na7la[s.row][s.column].getGlobalBounds())) {
				s.attacking = false;
				s.av_x = 0;
				s.av_y = 0;
				s.v_x = s.v_x / 4;
				s.v_y = -15;
				na7la[s.row][s.column].setScale(0, 0);
				obstacle_map[s.row][s.column] = 0;
				s.a_cnt = 0;
			}

			if (s.atk_time > 7) {
				s.atk_time = 0;
				s.av_x = 0;
				s.av_y = 0;
				s.v_x = 0;
				s.v_y = 0;
				s.attacking = false;
			}
		}
	}
}

//t7rek crab w bgeb el pos bt3thom w animation
void crabs(int i, int j) {

	if (e[i][j].can_move) {
		crab[i][j].move(e[i][j].v_x, 0);
	}

	e[i][j].x = crab[i][j].getPosition().x;
	e[i][j].y = crab[i][j].getPosition().y;

	crab[i][j].setTextureRect(IntRect((e[i][j].animation / 7) * 50, 0, 40, 50));
	e[i][j].animation++;
	e[i][j].animation %= 28;

	//crab
	if ((e[i][j].x + e[i][j].v_x) - j * tile_width > 200) {
		e[i][j].v_x *= -1;
	}
	else if ((e[i][j].x + e[i][j].v_x) - j * tile_width < 0) {
		e[i][j].v_x *= -1;
	}



}

//t7rek n7la w bgeb el pos bt3thom w animation
void bee(int i, int j) {

	if (n7[i][j].can_move) {
		na7la[i][j].move(n7[i][j].v_x, 0);
	}

	n7[i][j].x = na7la[i][j].getPosition().x;
	n7[i][j].y = na7la[i][j].getPosition().y;

	na7la[i][j].setTextureRect(IntRect((n7[i][j].animation / 7) * 49, 0, 49, 32.5));
	n7[i][j].animation++;
	n7[i][j].animation %= 28;

	//na7la
	if ((n7[i][j].x + n7[i][j].v_x) - j * tile_width > 230) {
		n7[i][j].v_x *= -1;
		na7la[i][j].setScale(1.5, 1.5);

	}
	else if ((n7[i][j].x + n7[i][j].v_x) - j * tile_width < 20) {
		n7[i][j].v_x *= -1;

		na7la[i][j].setScale(-1.5, 1.5);

	}
}

//attack animation of n7la and time lapse between attacks and bullet speed and animation w el eauation bta3 el bullet speed
void enemy_attack(int i, int j) {
	n7[i][j].atc_cnt++;

	//checking whether the enemy will attack or now and setting the init speed & position of bullet and the direction and bullet animation
	if (abs(s.x - n7[i][j].x) < 500 && n7[i][j].y < s.y && n7[i][j].atc_cnt > 200) {

		bullet[j].setTextureRect(IntRect(17, 4, 7, 8));
		bullet[j].setScale(2, 2);

		n7[i][j].atc_cnt = 0;
		n7[i][j].atc_animation = 0;

		//equation of motion of bullet
		b[j].angle = atan((abs((s.y - 40) - (n7[i][j].y + 20))) / (abs(s.x - (n7[i][j].x + 10))));

		//b4of lw sonic abl aw b3d el enemy 34an a5aly el vel +ve aw -ve
		if (s.x >= n7[i][j].x) {
			b[j].v_x = cos(b[j].angle) * b[j].fixed_v;
		}
		else {
			b[j].v_x = -cos(b[j].angle) * b[j].fixed_v;
		}
		b[j].v_y = sin(b[j].angle) * b[j].fixed_v;

		if (s.x > n7[i][j].x) {
			na7la[i][j].setScale(-1.5, 1.5);
			//bullet[j].setOrigin(bullet[j].getGlobalBounds().width / 2, bullet[j].getGlobalBounds().height);
			bullet[j].setPosition(n7[i][j].x + 24, n7[i][j].y + 15);
		}

		else {
			na7la[i][j].setScale(1.5, 1.5);
			bullet[j].setPosition(n7[i][j].x - 24, n7[i][j].y + 15);
		}
		b[j].x = bullet[j].getPosition().x;
		b[j].y = bullet[j].getPosition().y;
	}

	//animation of n7la attack (m4 el bullet)
	if (n7[i][j].atc_animation < 22) {
		if (n7[i][j].atc_animation > 7 && n7[i][j].atc_animation < 15) {

			na7la[i][j].setTextureRect(IntRect(0, 33, 40, 34));
		}
		else {
			na7la[i][j].setTextureRect(IntRect(40, 33, 43, 36));
		}
		n7[i][j].atc_animation++;
		if (n7[i][j].atc_animation == 22) {
			if (n7[i][j].v_x > 0) {
				na7la[i][j].setScale(-1.5, 1.5);
			}
			else {
				na7la[i][j].setScale(1.5, 1.5);
			}
		}
	}
}

//bgeb el pos w el collision
void bullet_collision(int i, int j) {


	bullet[j].move(b[j].v_x, b[j].v_y);

	b[j].x = bullet[j].getPosition().x;
	b[j].y = bullet[j].getPosition().y;
	b[j].column = b[j].x / 265;
	b[j].row = b[j].y / 149;


	//collision with sonic
	if (abs(b[j].x - s.x) < 25 && s.y - b[j].y < 100 && s.y - b[j].y > 0 && bullet[j].getScale().x != 0 && !s.attacking) {
		sonic_hit();
		bullet[j].setScale(0, 0);
		b[j].v_x = 0;
		b[j].v_y = 0;
	}

	//collision with ground
	if (tile_map[b[j].row][b[j].column] != 0) {

		if (tile_map[b[j].row][b[j].column] == 2) {

			if (b[j].y + b[j].v_y > (tile_height * (1 + b[j].row)) - (0.55597 * (b[j].x - (b[j].column * tile_width)))) {
				bullet[j].setScale(0, 0);
				b[j].v_x = 0;
				b[j].v_y = 0;
			}
		}

		else if (tile_map[b[j].row][b[j].column] == 3) {
			if (b[j].y + b[j].v_y > (b[j].row * tile_height) + 0.55597 * (b[j].x - (b[j].column * tile_width))) {
				bullet[j].setScale(0, 0);
				b[j].v_x = 0;
				b[j].v_y = 0;
			}
		}

		else if (tile_map[b[j].row][b[j].column] == 4) {
			if (b[j].y + b[j].v_y > 2 * sqrt(888 * (25 - (pow(b[j].x - (b[j].column * tile_width), 2) / 2873))) + ((b[j].row - 1) * tile_height)) {

				bullet[j].setScale(0, 0);
				b[j].v_x = 0;
				b[j].v_y = 0;
			}
		}

		else if (tile_map[b[j].row][b[j].column] == 5) {
			if (b[j].y + b[j].v_y > 2 * sqrt(888 * (25 - (pow((b[j].x) - (b[j].column * tile_width), 2) / 2873))) + (b[j].row * tile_height)) {

				bullet[j].setScale(0, 0);
				b[j].v_x = 0;
				b[j].v_y = 0;
			}
		}
		else {
			bullet[j].setScale(0, 0);
			b[j].v_x = 0;
			b[j].v_y = 0;
		}

	}

}

void sonic_hit() {

	if (s.alive) {

		if (s.revive_cnt > 200) {
			if (scr > 0) {

				s.knock_out = true;
				s.revive_cnt = 0;
				s.death_cnt = 0;
				if (scr > 0) {
					//animation el moot
					if (sonic.getScale().x > 0) {
						s.v_x = -15;
						s.v_y = -10;
					}
					else {
						s.v_x = 15;
						s.v_y = -10;
					}
				}

				for (int i = 0; i < tile_y; i++) {
					if (scr == 0) {
						break;
					}
					for (int j = 0; j < tile_x; j++) {
						if (scr == 0) {
							break;
						}
						if (shapes_map[i][j] == 0) {
							shapes_map[i][j] = 10;

							//coin[i][j].setPosition(s.x - 40, s.y - 100);
							coin[i][j].setScale(0.3, 0.3);
							coin[i][j].setOrigin(0, 133);

							f_c[i][j].x = coin[i][j].getPosition().x;
							f_c[i][j].y = coin[i][j].getPosition().y;

							f_c[i][j].column = f_c[i][j].x / tile_width;
							f_c[i][j].row = f_c[i][j].y / tile_height;

							if (scr % 2 == 0) {
								f_c[i][j].v_x = -(4 + (rand() % 15));
								coin[i][j].setPosition(s.x - 40, s.y - 100);
							}
							else {
								f_c[i][j].v_x = 4 + (rand() % 15);
								coin[i][j].setPosition(s.x + 40, s.y - 100);
							}
							scr--;
						}


					}

				}
			}
			else {
				s.alive = false;
				save();
				death.play();
				s.v_y = -25;
				s.v_x = 0;
			}
		}
	}
}

void coin_movement(int i, int j) {

	s.death_cnt++;
	coin[i][j].move(f_c[i][j].v_x, f_c[i][j].v_y);
	if (f_c[i][j].v_x > 0) {
		f_c[i][j].v_x -= 0.2;
		if (f_c[i][j].v_x < 0.2) {
			f_c[i][j].v_x = 0;
		}
	}
	else {
		f_c[i][j].v_x += 0.2;
		if (f_c[i][j].v_x > -0.2) {
			f_c[i][j].v_x = 0;
		}
	}

	f_c[i][j].x = coin[i][j].getPosition().x;
	f_c[i][j].y = coin[i][j].getPosition().y;


	f_c[i][j].column = f_c[i][j].x / tile_width;
	f_c[i][j].row = f_c[i][j].y / tile_height;

	//collision m3 3l tiles mn el gmb
	if ((tile_map[f_c[i][j].row][f_c[i][j].column + 1] == 1 || tile_map[f_c[i][j].row][f_c[i][j].column + 1] == 10 || tile_map[f_c[i][j].row][f_c[i][j].column + 1] == 8) && ((f_c[i][j].v_x + f_c[i][j].x) - (f_c[i][j].column * tile_width) >= 226)) {
		coin[i][j].setPosition(((f_c[i][j].column + 1) * tile_width) - 43, f_c[i][j].y);
		f_c[i][j].v_x = 0;
	}
	else if ((tile_map[f_c[i][j].row][f_c[i][j].column - 1] == 1 || tile_map[f_c[i][j].row][f_c[i][j].column - 1] == 10 || tile_map[f_c[i][j].row][f_c[i][j].column - 1] == 8) && ((f_c[i][j].v_x + f_c[i][j].x) - (f_c[i][j].column * tile_width) <= 0)) {
		coin[i][j].setPosition((f_c[i][j].column * tile_width) + 23, f_c[i][j].y);
		f_c[i][j].v_x = 0;
	}

	if (tile_map[f_c[i][j].row][f_c[i][j].column] == 0) {
		f_c[i][j].v_y += 0.5;
	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 1) {

		if (f_c[i][j].v_y <= 2) {
			coin[i][j].setPosition(f_c[i][j].x, f_c[i][j].row * tile_height);
			f_c[i][j].v_y = 0;
		}
		else {
			coin[i][j].setPosition(f_c[i][j].x, f_c[i][j].row * tile_height);
			f_c[i][j].v_y /= -1.5;
		}
	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 2) {

		if (f_c[i][j].y + f_c[i][j].v_y > (tile_height * (1 + f_c[i][j].row)) - (0.55597 * (f_c[i][j].x - (f_c[i][j].column * tile_width))) - 12) {

			coin[i][j].setPosition(f_c[i][j].x, (tile_height * (1 + f_c[i][j].row)) - (0.55597 * (f_c[i][j].x - (f_c[i][j].column * tile_width))) - 12);
			f_c[i][j].v_x -= 0.7;
			f_c[i][j].v_y = 0;
		}
		else {
			f_c[i][j].v_y += 0.5;
		}
	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 6) {
		f_c[i][j].v_y = 0;
		coin[i][j].setPosition(f_c[i][j].x, (tile_height * f_c[i][j].row) - (0.55597 * (f_c[i][j].x - (f_c[i][j].column * tile_width))) - 12);


	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 3) {

		if (f_c[i][j].y + f_c[i][j].v_y > (f_c[i][j].row * tile_height) + 0.55597 * (f_c[i][j].x - (f_c[i][j].column * tile_width))) {

			f_c[i][j].v_y = 0;
			f_c[i][j].v_x += 0.7;
			coin[i][j].setPosition(f_c[i][j].x, (f_c[i][j].row * tile_height) + 0.55597 * (f_c[i][j].x - (f_c[i][j].column * tile_width)));
		}
		else {
			f_c[i][j].v_y += 0.5;
		}
	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 7) {

		f_c[i][j].v_y = 0;
		coin[i][j].setPosition(f_c[i][j].x, ((f_c[i][j].row - 1) * tile_height) + 0.55597 * (f_c[i][j].x - (f_c[i][j].column * tile_width)));

	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 4) {

		if (f_c[i][j].y + f_c[i][j].v_y > 2 * sqrt(888 * (25 - (pow(f_c[i][j].x - (f_c[i][j].column * tile_width), 2) / 2873))) + ((f_c[i][j].row - 1) * tile_height) - 10) {

			f_c[i][j].v_y = 0;
			f_c[i][j].v_x -= 1;
			coin[i][j].setPosition(f_c[i][j].x, 2 * sqrt(888 * (25 - (pow(f_c[i][j].x - (f_c[i][j].column * tile_width), 2) / 2873))) + ((f_c[i][j].row - 1) * tile_height) - 10);

		}
		else {
			f_c[i][j].v_y += 0.5;
		}
	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 5) {

		if (f_c[i][j].y + f_c[i][j].v_y > 2 * sqrt(888 * (25 - (pow((f_c[i][j].x) - (f_c[i][j].column * tile_width), 2) / 2873))) + ((f_c[i][j].row) * tile_height) - 10) {

			f_c[i][j].v_y = 0;
			f_c[i][j].v_x -= 2;
			coin[i][j].setPosition(f_c[i][j].x, 2 * sqrt(888 * (25 - (pow((f_c[i][j].x) - (f_c[i][j].column * tile_width), 2) / 2873))) + ((f_c[i][j].row) * tile_height) - 10);

		}
		else {
			f_c[i][j].v_y += g / 2;
		}


	}

	else if (tile_map[f_c[i][j].row][f_c[i][j].column] == 8) {
		if (f_c[i][j].row * tile_height < 80) {
			f_c[i][j].v_y += 0.5;
		}
		else {
			coin[i][j].setPosition(f_c[i][j].x, f_c[i][j].row * tile_height + 80);
		}
	}


	if (coin[i][j].getScale().x != 0 && s.death_cnt > 100 && s.x - f_c[i][j].x < 80 && s.x - f_c[i][j].x > -35 && s.y - f_c[i][j].y > -40 && s.y - f_c[i][j].y < 100 && s.alive) {

		coin[i][j].setScale(0, 0);

		shapes_map[i][j] = 0;
		scr++;
	}

	//el coins el w23a te5tfy
	if (s.revive_cnt > 200) {
		coin[i][j].setScale(0, 0);

		shapes_map[i][j] = 0;
	}
}

void after_hit() {
	if (s.revive_cnt <= 200) {
		s.revive_cnt++;

		if (s.knock_out) {
			sonic.setTextureRect(IntRect(0, 398, 58, 48));
			sonic.setTextureRect(IntRect(0, 398, 58, 48));
			sh.play();
			sh.setPlayingOffset(seconds(0.5));
		}

		if (s.v_y == 0 && tile_map[s.row][s.column] != 0) {
			s.knock_out = false;
		}
		if (s.revive_cnt % 2 == 0) {

			if (s.draw) {
				s.draw = false;
			}
			else {
				s.draw = true;
			}
		}

	}
	else {
		s.draw = true;
	}
}

void sonic_death() {

	if (!s.alive) {
		s.user_control = false;
		s.gameOver_cnt++;
		s.gover_music++;
		s.v_y += g;
		sonic.setTextureRect(IntRect(116, 398, 58, 48));
		if (s.gover_music == 75) {
			gover.play();
		}
		if (s.gameOver_cnt >= 75)
		{
			s.game_over = true;
			s.gameOver_cnt = 0;
		}
	}
}

void save() {
	fstream file("tiles.txt");
	ofstream output("tiles.txt");

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << tile_map[i][j] << " ";
		}
	}

	for (int i = 0; i < tile_y / 2; i++) {
		for (int j = 0; j < tile_x / 2; j++) {
			output << loop_map[i][j] << " ";
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			if (shapes_map[i][j] == 10) {
				shapes_map[i][j] = 0;
			}

			output << shapes_map[i][j] << " ";
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << obstacle_map[i][j] << " ";
		}
	}

	//coins variables
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			output << c.intersection[i][j] << " ";
		}
	}

	//crab
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << e[i][j].x << " " << e[i][j].y << " " << e[i][j].v_x << " " << e[i][j].v_y << " ";
		}
	}

	//n7la
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << n7[i][j].x << " " << n7[i][j].y << " " << n7[i][j].v_x << " " << n7[i][j].v_y << " ";
		}
	}


	output << s.x << " " << s.y << " " << s.column << " " << s.row << " " << s.loop_column << " " << s.loop_row << " " << c.column << " " << c.row << " " << scr << " ";


	file.close();
}

void save_newgame() {
	fstream file2("newgame.txt");

	ofstream output("newgame.txt");

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << tile_map[i][j] << " ";
		}
	}

	for (int i = 0; i < tile_y / 2; i++) {
		for (int j = 0; j < tile_x / 2; j++) {
			output << loop_map[i][j] << " ";
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			if (shapes_map[i][j] == 10) {
				shapes_map[i][j] = 0;
			}

			output << shapes_map[i][j] << " ";
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << obstacle_map[i][j] << " ";
		}
	}

	//coins variables
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			output << c.intersection[i][j] << " ";
		}
	}
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			output << c.animation[i][j] << " ";
		}
	}

	//fallen coins
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			output << f_c[i][j].row << " " << f_c[i][j].column << " " << f_c[i][j].x << " " << f_c[i][j].y << " " << f_c[i][j].v_x << " " << f_c[i][j].v_y << " ";
		}
	}

	//crab
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << e[i][j].x << " " << e[i][j].y << " " << e[i][j].v_x << " " << e[i][j].v_y << " " << e[i][j].animation << " " << e[i][j].atc_cnt << " " << e[i][j].atc_animation << " " << e[i][j].animation << " " << e[i][j].attacking << " " << e[i][j].can_move << " ";
		}
	}

	//n7la
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			output << n7[i][j].x << " " << n7[i][j].y << " " << n7[i][j].v_x << " " << n7[i][j].v_y << " " << n7[i][j].animation << " " << n7[i][j].atc_cnt << " " << n7[i][j].atc_animation << " " << n7[i][j].animation << " " << n7[i][j].attacking << " " << n7[i][j].can_move << " ";

		}
	}

	//jumper
	for (int i = 0; i < tile_y; i++) {
		for (int v = 0; v < tile_x; v++) {
			output << j.animation_cnt[i][v] << " " << j.snt[i][v] << " " << j.animate[i][v] << " ";

		}
	}

	//bullet
	for (int i = 0; i < tile_x; i++) {
		output << b[i].x << " " << b[i].y << " " << b[i].v_x << " " << b[i].v_y << " " << b[i].angle << " " << b[i].fixed_v << " " << b[i].row << " " << b[i].column << " ";
	}


	output << s.x << " " << s.y << " " << s.v_x << " " << s.v_y << " " << s.a_x << " " << s.chrg_v << " " << s.width << " " << s.height << " " << s.av_x << " " << s.av_y << " " << s.angle << " ";
	output << s.animation << " " << s.jump_animation << " " << s.charge_animation << " " << s.column << " " << s.row << " " << s.loop_column << " " << s.loop_row << " " << s.a_cnt << " ";
	output << s.atk_time << " " << s.death_cnt << " " << s.revive_cnt << " " << s.second_jump2 << " " << s.gameOver_cnt << " " << s.gover_music << " " << s.finish_cnt << " ";
	output << s.moving << " " << s.can_jump << " " << s.in_curve << " " << s.down_curve << " " << s.user_control << " " << s.knock_out << " " << s.alive << " " << s.game_over << " " << s.won << " ";
	output << s.looped1 << " " << s.looped2 << " " << s.looped3 << " " << s.looped4 << " " << s.attacking << " " << s.draw << " " << s.second_jump << " " << s.infinish << " ";
	output << s.check_point << " ";

	output << c.column << " " << c.row << " ";

	output << " " << j.v_y << " " << j.cnt << " " << j.right << " " << j.left << " ";


	file2.close();
}

void load() {



	s.animation = 0, s.jump_animation = 0, s.charge_animation = 0, s.a_cnt = 0;
	s.atk_time = 0, s.death_cnt = 100, s.revive_cnt = 201, s.second_jump2 = 0, s.gameOver_cnt = 0;
	s.moving = false, s.can_jump = true, s.in_curve = false, s.down_curve = false, s.user_control = true, s.knock_out = false, s.alive = true;
	s.looped1 = false, s.looped2 = false, s.looped3 = false, s.looped4 = false, s.attacking = false, s.draw = true, s.second_jump = false, s.game_over = false;


	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			c.animation[i][j] = 0;
		}
	}
	for (int i = 0; i < tile_y; i++) {
		for (int v = 0; v < tile_x; v++) {

			if (i == 0) {
				bullet[v].setScale(0, 0);
				b[v].v_x = 0;
				b[v].v_y = 0;
			}

			j.animation_cnt[i][v] = 0;
			j.snt[i][v] = 0;
			j.animate[i][v] = 0;

			e[i][v].animation = 0;
			e[i][v].atc_cnt = 0;
			e[i][v].atc_animation = 0;
			e[i][v].attacking = 0;
			e[i][v].can_move = 1;

			n7[i][v].animation = 0;
			n7[i][v].atc_cnt = 0;
			n7[i][v].atc_animation = 0;
			n7[i][v].attacking = 0;
			n7[i][v].can_move = 1;
		}
	}

	j.cnt = 0;
	j.right = false, j.left = false;


	sonic.setPosition(s.x, s.y);


	fstream file("tiles.txt");

	ifstream input("tiles.txt");

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> tile_map[i][j];
		}
	}

	for (int i = 0; i < tile_y / 2; i++) {
		for (int j = 0; j < tile_x / 2; j++) {
			input >> loop_map[i][j];
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			input >> shapes_map[i][j];
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> obstacle_map[i][j];
		}
	}

	//coins variables
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			input >> c.intersection[i][j];
		}
	}

	//crab
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> e[i][j].x >> e[i][j].y >> e[i][j].v_x >> e[i][j].v_y;
			crab[i][j].setPosition(e[i][j].x, e[i][j].y);
		}
	}

	//n7la
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> n7[i][j].x >> n7[i][j].y >> n7[i][j].v_x >> n7[i][j].v_y;
			na7la[i][j].setPosition(n7[i][j].x, n7[i][j].y);
		}
	}


	input >> s.x >> s.y >> s.column >> s.row >> s.loop_column >> s.loop_row >> c.column >> c.row >> scr;
	sonic.setPosition(s.x, s.y);

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {

			//tree
			if (shapes_map[i][j * 3] == -3) {
				tree[i][j * 3].setScale(1.5, 4);
				tree[i][j * 3].setPosition(j * 3 * shapes_width, i * shapes_height + 52);
			}
			if (shapes_map[i][(j * 3) + 1] == -3) {
				tree[i][(j * 3) + 1].setScale(1.5, 4);
				tree[i][(j * 3) + 1].setPosition(((j * 3) + 1) * shapes_width, i * shapes_height + 52);
			}
			if (shapes_map[i][(j * 3) + 2] == -3) {
				tree[i][(j * 3) + 2].setScale(1.5, 4);
				tree[i][(j * 3) + 2].setPosition(((j * 3) + 2) * shapes_width, i * shapes_height + 52);
			}
			//coin
			if (shapes_map[i][j * 3] == 1) {
				coin[i][j * 3].setPosition(j * 3 * shapes_width, i * shapes_height + 100);
				coin[i][j * 3].setScale(0.3, 0.3);
			}
			if (shapes_map[i][(j * 3) + 1] == 1) {
				coin[i][(j * 3) + 1].setPosition(((j * 3) + 1) * shapes_width, i * shapes_height + 100);
				coin[i][(j * 3) + 1].setScale(0.3, 0.3);
			}
			if (shapes_map[i][(j * 3) + 2] == 1) {
				coin[i][(j * 3) + 2].setPosition(((j * 3) + 2) * shapes_width, i * shapes_height + 100);
				coin[i][(j * 3) + 2].setScale(0.3, 0.3);
			}


			//horizontal ground
			if (tile_map[i][j] == 1) {
				hor_ground[i][j].setPosition(j * tile_width, i * tile_height);
				hor_ground[i][j].setScale(1.1, 0.8);
			}
			// positive slope
			else if (tile_map[i][j] == 2) {
				slope[i][j].setPosition(j * tile_width, i * tile_height);
				slope[i][j].setScale(1, 1);
			}
			//negative slope
			else if (tile_map[i][j] == 3) {
				slope[i][j].setScale(-1, 1);
				slope[i][j].setOrigin(268, 0);
				slope[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//curve
			else if (tile_map[i][j] == 4) {
				curve[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//rest of curve
			else if (tile_map[i][j] == 5) {
				curve[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//spikes
			else if (tile_map[i][j] == 8) {
				spikes[i][j].setPosition(j * tile_width, i * tile_height + 77);
			}
			//loop
			else if (loop_map[i][j] == 6) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 7) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 8) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 9) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}

			//jumper
			if (obstacle_map[i][j] == 1) {
				jumper_h[i][j].setTextureRect(IntRect(103.7, 0, 103.7, 78));
				jumper_h[i][j].setPosition(j * tile_width + 134, i * tile_height + 74);
			}
			if (obstacle_map[i][j] == 2) {
				jumper[i][j].setTextureRect(IntRect(0, 0, 43, 51));
				jumper[i][j].setPosition(j * tile_width + 10, i * tile_height);
				jumper[i][j].setScale(1.5, 1.5);
			}
			if (obstacle_map[i][j] == 3) {
				jumper[i][j].setTextureRect(IntRect(0, 0, 43, 51));
				jumper[i][j].setPosition(j * tile_width + 234, i * tile_height);
				jumper[i][j].setScale(-1.5, 1.5);

			}

			//enemy
			if (obstacle_map[i][j] == -1) {
				crab[i][j].setPosition(j * tile_width, i * tile_height + 82);
				crab[i][j].setScale(1.8, 1.8);
			}
			else if (obstacle_map[i][j] == -2) {
				na7la[i][j].setPosition(j * tile_width + 30, i * tile_height + 100);
				na7la[i][j].setScale(-1.5, 1.5);
			}
		}
	}

}

void load_newgame() {

	scr = 0;

	fstream file2("newgame.txt");

	ifstream input("newgame.txt");

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> tile_map[i][j];
		}
	}

	for (int i = 0; i < tile_y / 2; i++) {
		for (int j = 0; j < tile_x / 2; j++) {
			input >> loop_map[i][j];
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			if (shapes_map[i][j] == 10) {
				shapes_map[i][j] = 0;
			}

			input >> shapes_map[i][j];
		}
	}

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> obstacle_map[i][j];
		}
	}

	//coins variables
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			input >> c.intersection[i][j];
		}
	}
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			input >> c.animation[i][j];
		}
	}

	//fallen coins
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x * 3; j++) {
			input >> f_c[i][j].row >> f_c[i][j].column >> f_c[i][j].x >> f_c[i][j].y >> f_c[i][j].v_x >> f_c[i][j].v_y;
		}
	}

	//crab
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> e[i][j].x >> e[i][j].y >> e[i][j].v_x >> e[i][j].v_y >> e[i][j].animation >> e[i][j].atc_cnt >> e[i][j].atc_animation >> e[i][j].animation >> e[i][j].attacking >> e[i][j].can_move;
			crab[i][j].setPosition(e[i][j].x, e[i][j].y);
		}
	}

	//n7la
	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {
			input >> n7[i][j].x >> n7[i][j].x >> n7[i][j].v_x >> n7[i][j].v_y >> n7[i][j].animation >> n7[i][j].atc_cnt >> n7[i][j].atc_animation >> n7[i][j].animation >> n7[i][j].attacking >> n7[i][j].can_move;
			na7la[i][j].setPosition(n7[i][j].x, n7[i][j].y);
		}
	}

	//jumper
	for (int i = 0; i < tile_y; i++) {
		for (int v = 0; v < tile_x; v++) {
			input >> j.animation_cnt[i][v] >> j.snt[i][v] >> j.animate[i][v];

		}
	}

	//bullet
	for (int i = 0; i < tile_x; i++) {
		input >> b[i].x >> b[i].y >> b[i].v_x >> b[i].v_y >> b[i].angle >> b[i].fixed_v >> b[i].row >> b[i].column;
	}


	input >> s.x >> s.y >> s.v_x >> s.v_y >> s.a_x >> s.chrg_v >> s.width >> s.height >> s.av_x >> s.av_y >> s.angle;
	input >> s.animation >> s.jump_animation >> s.charge_animation >> s.column >> s.row >> s.loop_column >> s.loop_row >> s.a_cnt;
	input >> s.atk_time >> s.death_cnt >> s.revive_cnt >> s.second_jump2 >> s.gameOver_cnt >> s.gover_music >> s.finish_cnt;
	input >> s.moving >> s.can_jump >> s.in_curve >> s.down_curve >> s.user_control >> s.knock_out >> s.alive >> s.game_over >> s.won;
	input >> s.looped1 >> s.looped2 >> s.looped3 >> s.looped4 >> s.attacking >> s.draw >> s.second_jump >> s.infinish;
	input >> s.check_point;

	sonic.setPosition(s.x, s.y);

	input >> c.column >> c.row;

	input >> j.v_y >> j.cnt >> j.right >> j.left;


	file2.close();

	for (int i = 0; i < tile_y; i++) {
		for (int j = 0; j < tile_x; j++) {

			//tree
			if (shapes_map[i][j * 3] == -3) {
				tree[i][j * 3].setScale(1.5, 4);
				tree[i][j * 3].setPosition(j * 3 * shapes_width, i * shapes_height + 52);
			}
			if (shapes_map[i][(j * 3) + 1] == -3) {
				tree[i][(j * 3) + 1].setScale(1.5, 4);
				tree[i][(j * 3) + 1].setPosition(((j * 3) + 1) * shapes_width, i * shapes_height + 52);
			}
			if (shapes_map[i][(j * 3) + 2] == -3) {
				tree[i][(j * 3) + 2].setScale(1.5, 4);
				tree[i][(j * 3) + 2].setPosition(((j * 3) + 2) * shapes_width, i * shapes_height + 52);
			}
			//coin
			if (shapes_map[i][j * 3] == 1) {
				coin[i][j * 3].setPosition(j * 3 * shapes_width, i * shapes_height + 100);
				coin[i][j * 3].setScale(0.3, 0.3);
			}
			if (shapes_map[i][(j * 3) + 1] == 1) {
				coin[i][(j * 3) + 1].setPosition(((j * 3) + 1) * shapes_width, i * shapes_height + 100);
				coin[i][(j * 3) + 1].setScale(0.3, 0.3);
			}
			if (shapes_map[i][(j * 3) + 2] == 1) {
				coin[i][(j * 3) + 2].setPosition(((j * 3) + 2) * shapes_width, i * shapes_height + 100);
				coin[i][(j * 3) + 2].setScale(0.3, 0.3);
			}


			//horizontal ground
			if (tile_map[i][j] == 1) {
				hor_ground[i][j].setPosition(j * tile_width, i * tile_height);
				hor_ground[i][j].setScale(1.1, 0.8);
			}
			// positive slope
			else if (tile_map[i][j] == 2) {
				slope[i][j].setPosition(j * tile_width, i * tile_height);
				slope[i][j].setScale(1, 1);
			}
			//negative slope
			else if (tile_map[i][j] == 3) {
				slope[i][j].setScale(-1, 1);
				slope[i][j].setOrigin(268, 0);
				slope[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//curve
			else if (tile_map[i][j] == 4) {
				curve[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//rest of curve
			else if (tile_map[i][j] == 5) {
				curve[i][j].setPosition(j * tile_width, i * tile_height);
			}
			//spikes
			else if (tile_map[i][j] == 8) {
				spikes[i][j].setPosition(j * tile_width, i * tile_height + 77);
			}
			//loop
			else if (loop_map[i][j] == 6) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 7) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 8) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}
			else if (loop_map[i][j] == 9) {
				loop[i][j].setPosition(j * loop_width, i * loop_height);

			}

			//jumper
			if (obstacle_map[i][j] == 1) {
				jumper_h[i][j].setTextureRect(IntRect(103.7, 0, 103.7, 78));
				jumper_h[i][j].setPosition(j * tile_width + 134, i * tile_height + 74);
			}
			if (obstacle_map[i][j] == 2) {
				jumper[i][j].setTextureRect(IntRect(0, 0, 43, 51));
				jumper[i][j].setPosition(j * tile_width + 10, i * tile_height);
				jumper[i][j].setScale(1.5, 1.5);
			}
			if (obstacle_map[i][j] == 3) {
				jumper[i][j].setTextureRect(IntRect(0, 0, 43, 51));
				jumper[i][j].setPosition(j * tile_width + 234, i * tile_height);
				jumper[i][j].setScale(-1.5, 1.5);

			}

			//enemy
			if (obstacle_map[i][j] == -1) {
				crab[i][j].setPosition(j * tile_width, i * tile_height + 82);
				crab[i][j].setScale(1.8, 1.8);
			}
			else if (obstacle_map[i][j] == -2) {
				na7la[i][j].setPosition(j * tile_width + 30, i * tile_height + 100);
				na7la[i][j].setScale(-1.5, 1.5);
			}
		}
	}

}

void checkPoint() {
	if (s.x > 8000 && !s.check_point && tile_map[s.row][s.column] == 1) {
		save();
		s.check_point = true;
	}
}

void finish_() {
	if (sonic.getGlobalBounds().intersects(finish.getGlobalBounds())) {
		s.infinish = true;
		s.v_x = 30;
	}
	if (s.infinish) {

		if (s.finish_cnt == 0) {
			finish.setTextureRect(IntRect(15, 0, 109, 115));
		}
		else if (s.finish_cnt == 14) {
			finish.setTextureRect(IntRect(723, 0, 135, 115));
		}
		else if (s.finish_cnt >= 16) {
			finish.setTextureRect(IntRect(862, 0, 135, 115));
		}
		else if (s.finish_cnt == 2) {
			finish.setTextureRect(IntRect(145, 0, 124, 115));

		}
		else if (s.finish_cnt == 12) {
			finish.setTextureRect(IntRect(600, 0, 124, 115));
		}

		else if (s.finish_cnt == 4) {
			finish.setTextureRect(IntRect(270, 0, 111, 115));
		}
		else if (s.finish_cnt == 6) {
			finish.setTextureRect(IntRect(387, 0, 76, 115));
		}
		else if (s.finish_cnt == 8) {
			finish.setTextureRect(IntRect(453, 0, 56, 115));
		}
		else if (s.finish_cnt == 10) {
			finish.setTextureRect(IntRect(509, 0, 93, 115));
		}

		s.finish_cnt++;
		s.finish_cnt %= 9;
	}

	if (s.x >= 18492) {
		sonic.setPosition(18462, 637);
		s.won = true;
	}

}

void mainmenu(RenderWindow& window) {

	if (cnt == 0 && cnt1 == 0 && cnt3 == 0) {
		window.draw(main_menu);
		window.draw(katkot);
		ms.stop();
		gover.stop();
		window.display();
		view.setCenter(960, 538);
		view.setSize(window_x + 35, window_y + 120);
		window.setView(view);
	}


	//katkot_animation
	katkot.setTextureRect(IntRect((op_animation / 10) * 39, 0, 39, 47));
	op_animation++;
	op_animation %= 70;


	Vector2i mp = Mouse::getPosition(window);
	if (cnt == 0) {
		//a7mr
		if (mp.x > 575 && mp.x < 789 && mp.y>225 && mp.y < 278) {

			cnt1 = 5;
			cnt3 = 0;
		}
		else if (mp.x > 530 && mp.x < 837 && mp.y>352 && mp.y < 402) {

			cnt1 = 6;
			cnt3 = 0;
		}
		else if (mp.x > 529 && mp.x < 826 && mp.y> 487 && mp.y < 540) {
			cnt3 = 0;
			cnt1 = 7;
		}
		else if (mp.x > 605 && mp.x < 768 && mp.y> 614 && mp.y < 666) {
			cnt3 = 0;
			cnt1 = 8;
		}
		else{
			cnt1 = 0;
		}
		//dos
		if (Mouse::isButtonPressed(Mouse::Left)){
			if (mp.x > 575 && mp.x < 789 && mp.y>225 && mp.y < 278){
				cnt = 1;
				cnt1 = 1;
				ms.play();

			}
			else if (mp.x > 530 && mp.x < 837 && mp.y>352 && mp.y < 402){
				cnt = 2;
				cnt1 = 2;
			}
			else if (mp.x > 529 && mp.x < 826 && mp.y> 487 && mp.y < 540){
				cnt = 3;
				cnt1 = 3;
			}
			else if (mp.x > 605 && mp.x < 768 && mp.y> 614 && mp.y < 666){
				cnt = 4;
				cnt1 = 4;
			}
		}
		//keyboard
		if (Keyboard::isKeyPressed(Keyboard::Key::Down) && cvp == false) {
			cnt3++;
			if (cnt3 > 4) {
				cnt3 = 1;
			}
			cvp = true;
		}
		else if (!Keyboard::isKeyPressed(Keyboard::Key::Down) && cvp == true && !Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			cvp = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && cvp == false) {
			cnt3--;
			if (cnt3 < 1) {
				cnt3 = 4;
			}
			cvp = true;
		}
		else if (!Keyboard::isKeyPressed(Keyboard::Key::Up) && cvp == false && !Keyboard::isKeyPressed(Keyboard::Key::Down)) {
			cvp = false;
		}
		//keyboard_click
		if (cnt3 == 1) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
				cnt = 1;
				cnt3 = 5;
				ms.play();

			}
		}
		else if (cnt3 == 2) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
				cnt = 2;
				cnt3 = 6;
			}
		}
		else if (cnt3 == 3) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
				cnt = 3;
				cnt3 = 7;
			}
		}
		else if (cnt3 == 4) {
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
				cnt = 4;
				cnt3 = 8;
			}
		}
	}

	//a7mr
	if (cnt == 4) {
		window.close();
	}
	if (cnt1 == 5 || cnt3 == 1)
	{

		window.draw(play);
		window.draw(katkot);
		window.display();

	}
	if (cnt1 == 6 || cnt3 == 2)
	{

		window.draw(options);
		window.draw(katkot);
		window.display();

	}
	if (cnt1 == 7 || cnt3 == 3)
	{
		window.draw(credits);
		window.draw(katkot);
		window.display();
	}
	if (cnt1 == 8 || cnt3 == 4)
	{
		window.draw(quit);
		window.draw(katkot);
		window.display();
	}
	if ((cnt == 1) && (cnt1 == 1 || cnt3 == 5))
	{
		//view and score position

		if ((s.y + s.v_y) - view.getCenter().y > 200) {

			if (sonic.getPosition().x >= 17456) {
				view.setCenter(17456, view.getCenter().y);
				background.setPosition(view.getCenter().x, view.getCenter().y);

			}
			else if (sonic.getPosition().x <= 1000) {
				view.setCenter(1000, (s.y + s.v_y) - 200);
				score.setPosition(75, view.getCenter().y - 425);
				background.setPosition(view.getCenter().x, view.getCenter().y);

			}
			else {
				view.setCenter(s.x, (s.y + s.v_y) - 200);

				score.setPosition(s.x - 900, view.getCenter().y - 425);
				background.setPosition(view.getCenter().x, view.getCenter().y);
			}
		}

		else if ((s.y + s.v_y) - view.getCenter().y < -200) {

			if (sonic.getPosition().x >= 17456) {
				view.setCenter(17456, view.getCenter().y);
				background.setPosition(view.getCenter().x, view.getCenter().y);

			}
			else if (sonic.getPosition().x <= 1000) {
				view.setCenter(1000, (s.y + s.v_y) + 200);
				score.setPosition(75, view.getCenter().y - 425);
				background.setPosition(view.getCenter().x, view.getCenter().y);

			}
			else {

				view.setCenter(s.x, (s.y + s.v_y) + 200);
				score.setPosition(s.x - 900, view.getCenter().y - 425);
				background.setPosition(view.getCenter().x, view.getCenter().y);
			}
		}

		else {

			if (sonic.getPosition().x >= 17456) {
				view.setCenter(17456, view.getCenter().y);
				background.setPosition(view.getCenter().x, view.getCenter().y);

			}
			else if (sonic.getPosition().x <= 1000) {
				view.setCenter(1000, view.getCenter().y + (s.y - view.getCenter().y) / 50);
				score.setPosition(75, view.getCenter().y - 425);
				background.setPosition(view.getCenter().x, view.getCenter().y);

			}
			else {
				view.setCenter(s.x, view.getCenter().y + (s.y - view.getCenter().y) / 50);

				if ((s.y - view.getCenter().y) < 5) {
					view.setCenter(s.x, s.y);
				}
				background.setPosition(view.getCenter().x, view.getCenter().y);
				score.setPosition(s.x - 900, view.getCenter().y - 425);
			}
		}
		view.setSize(window_x, window_y);
		//view.move(50, 300);
		window.setView(view);



		key_pressed();
		sonic_aninmation();
		sonic_move();
		Ground();
		obstacle();
		ground_collisions();
		coins();
		enemy_collision();
		sonic_attack();
		after_hit();
		sonic_death();
		checkPoint();
		finish_();
		window.setView(view);
		window.clear();
		window.draw(background);
		//to draw sonic above this loop part


		for (int i = 0; i < tile_y; i++) {
			for (int v = 0; v < tile_x; v++) {

				//fallen coins
				if (shapes_map[i][v * 3] == 10) {
					coin[i][v * 3].setTextureRect(IntRect((c.animation[i][v * 3] / 3) * 134, 0, 134, 134));
					c.animation[i][v * 3]++;
					c.animation[i][v * 3] %= 30;
					coin_movement(i, v * 3);
					if (s.revive_cnt > 150) {
						if (s.draw) {
							window.draw(coin[i][v * 3]);
						}
					}
					else {
						window.draw(coin[i][v * 3]);
					}
				}


				if (shapes_map[i][v * 3 + 1] == 10) {
					coin[i][v * 3 + 1].setTextureRect(IntRect((c.animation[i][v * 3 + 1] / 3) * 134, 0, 134, 134));
					c.animation[i][v * 3 + 1]++;
					c.animation[i][v * 3 + 1] %= 30;

					coin_movement(i, v * 3 + 1);
					if (s.revive_cnt > 150) {
						if (s.draw) {
							window.draw(coin[i][v * 3 + 1]);
						}
					}
					else {
						window.draw(coin[i][v * 3 + 1]);
					}
				}


				if (shapes_map[i][v * 3 + 2] == 10) {
					coin[i][v * 3 + 2].setTextureRect(IntRect((c.animation[i][v * 3 + 2] / 3) * 134, 0, 134, 134));
					c.animation[i][v * 3 + 2]++;
					c.animation[i][v * 3 + 2] %= 30;
					coin_movement(i, v * 3 + 2);
					if (s.revive_cnt > 150) {
						if (s.draw) {
							window.draw(coin[i][v * 3 + 2]);
						}
					}
					else {
						window.draw(coin[i][v * 3 + 2]);
					}
				}

				//tree
				if (shapes_map[i][v * 3] == -3) {
					window.draw(tree[i][v * 3]);
				}
				if (shapes_map[i][v * 3 + 1] == -3) {
					window.draw(tree[i][v * 3 + 1]);
				}
				if (shapes_map[i][v * 3 + 2] == -3) {
					window.draw(tree[i][v * 3 + 2]);
				}

				//coins
				if (shapes_map[i][v * 3] == 1) {
					coin[i][v * 3].setTextureRect(IntRect((c.animation[i][v * 3] / 3) * 134, 0, 134, 134));

					c.animation[i][v * 3]++;
					c.animation[i][v * 3] %= 30;
					window.draw(coin[i][v * 3]);
				}
				if (shapes_map[i][v * 3 + 1] == 1) {
					coin[i][v * 3 + 1].setTextureRect(IntRect((c.animation[i][v * 3 + 1] / 3) * 134, 0, 134, 134));

					c.animation[i][v * 3 + 1]++;
					c.animation[i][v * 3 + 1] %= 30;
					window.draw(coin[i][v * 3 + 1]);
				}
				if (shapes_map[i][v * 3 + 2] == 1) {
					coin[i][v * 3 + 2].setTextureRect(IntRect((c.animation[i][v * 3 + 2] / 3) * 134, 0, 134, 134));

					c.animation[i][v * 3 + 2]++;
					c.animation[i][v * 3 + 2] %= 30;
					window.draw(coin[i][v * 3 + 2]);
				}

				//el bullet
				if (i == 0) {
					bullet_collision(i, v);
					window.draw(bullet[v]);
				}

				if (tile_map[i][v] == 1) {
					window.draw(hor_ground[i][v]);
				}
				else if (tile_map[i][v] == 2 || tile_map[i][v] == 3) {
					window.draw(slope[i][v]);
				}
				else if (tile_map[i][v] == 4) {
					window.draw(curve[i][v]);
				}
				else if (tile_map[i][v] == 5) {
					window.draw(curve[i][v]);
				}
				else if (tile_map[i][v] == 8) {
					window.draw(spikes[i][v]);
				}
				else if (loop_map[i][v] == 6) {
					window.draw(loop[i][v]);
				}
				else if (loop_map[i][v] == 7) {
					window.draw(loop[i][v]);
				}
				else if (loop_map[i][v] == 8) {
					window.draw(loop[i][v]);
				}
				else if (loop_map[i][v] == 9) {
					window.draw(loop[i][v]);
				}

				if (obstacle_map[i][v] == 2 || obstacle_map[i][v] == 3) {

					/*if (j.animate[i][v]) {
					jumper[i][v].setTextureRect(IntRect((j.animation_cnt[i][v] / 10) * 43, 0, 43, 51));
					j.animation_cnt[i][v]++;
					if (j.animation_cnt[i][v] == 50) {
					j.snt[i][v]++;
					}
					j.animation_cnt[i][v] %= 50;

					if (j.snt[i][v] == 2) {
					j.animate[i][v] = false;
					j.animation_cnt[i][v] = 0;
					j.snt[i][v] = 0;
					jumper[i][v].setTextureRect(IntRect(0, 0, 43, 51));
					}
					}*/
					window.draw(jumper[i][v]);
				}
				else if (obstacle_map[i][v] == 1)
				{
					if (j.animate[i][v]) {
						jumper_h[i][v].setTextureRect(IntRect((j.animation_cnt[i][v] / 5) * 103.7, 0, 103.7, 78));
						j.animation_cnt[i][v]++;
						if (j.animation_cnt[i][v] == 35) {
							j.snt[i][v]++;
						}
						j.animation_cnt[i][v] %= 35;

						if (j.snt[i][v] == 1) {
							j.animate[i][v] = false;
							j.animation_cnt[i][v] = 0;
							j.snt[i][v] = 0;

							jumper_h[i][v].setTextureRect(IntRect(0, 0, 103.7, 78));
						}
					}
					window.draw(jumper_h[i][v]);
				}

				else if (obstacle_map[i][v] == -1) {
					window.draw(crab[i][v]);
					crabs(i, v);
				}
				else if (obstacle_map[i][v] == -2) {

					window.draw(na7la[i][v]);

					if (n7[i][v].atc_animation > 21) {
						bee(i, v);
					}
					enemy_attack(i, v);
				}
			}
		}
		window.draw(loop[1][1]);
		window.draw(score);

		window.draw(finish);
		if (s.draw) {
			window.draw(sonic);
		}
		//game over
		if (s.game_over) {

			gameOver.setPosition(view.getCenter().x + 5, view.getCenter().y + 11);
			gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
			opm.stop();
			ms.stop();
			window.draw(gameOver);
			//cout << mp.x << " " << mp.y << endl;
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mp.x > 40 && mp.x < 442 && mp.y>37 && mp.y < 102) {
					scov = 1;
					ms.play();
					ms.setLoop(true);
				}
				else if (mp.x > 93 && mp.x < 323 && mp.y>178 && mp.y < 242) {
					scov = 2;
					ms.play();
					ms.setLoop(true);
				}
				else if (mp.x > 132 && mp.x < 297 && mp.y>304 && mp.y < 366) {
					cnt = 4;
				}

			}
			if (scov == 1) {
				load_newgame();
			}
			else if (scov == 2) {
				load();
			}
		}

		window.display();
		opm.stop();

		if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace)) {
			//window.clear();
			cnt = 0;
			cnt1 = 0;
			cnt3 = 0;
			ms.stop();
			gover.stop();
			view.setCenter(960, 538);
			view.setSize(window_x + 35, window_y + 120);
			window.setView(view);
			opm.play();
		}

	}
	else if ((cnt == 2) && (cnt1 == 2 || cnt3 == 6))
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && cvm == false) {
			if (cv < 100) {
				cv += 25;
				if (cv2 < 5) {
					cv2 += 1;
				}
			}
			cvm = true;
		}
		else if (!Keyboard::isKeyPressed(Keyboard::Key::Right) && cvm == true && !Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			cvm = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && cvm == false) {
			if (cv > 0) {
				cv -= 25;

				if (cv2 > 0) {
					cv2 -= 1;
				}
			}
			cvm = true;
		}
		else if (!Keyboard::isKeyPressed(Keyboard::Key::Left) && cvm == true && !Keyboard::isKeyPressed(Keyboard::Key::Right)) {
			cvm = false;
		}

		opm.setVolume(cv / 2);
		ms.setVolume(cv / 2);
		scv.setVolume(cv / 2);
		gover.setVolume(cv / 2);
		jps.setVolume(cv);
		death.setVolume(cv);
		sh.setVolume(cv / 2);

		if (Mouse::isButtonPressed(Mouse::Left)) {

			if (mp.x > 389 && mp.x < 402 && mp.y > 363 && mp.y < 389)
			{
				cv2 = 1;
				cv = 0;
			}
			else if (mp.x > 402 && mp.x < 581 && mp.y > 363 && mp.y < 389)
			{
				cv2 = 2;
				cv = 25;
			}
			else if (mp.x > 589 && mp.x < 777 && mp.y > 363 && mp.y < 389)
			{
				cv2 = 3;
				cv = 50;
			}
			else if (mp.x > 783 && mp.x < 966 && mp.y > 363 && mp.y < 389)
			{
				cv2 = 4;
				cv = 75;
			}
			else if (mp.x > 975 && mp.x < 1164 && mp.y > 363 && mp.y < 389)
			{
				cv2 = 5;
				cv = 100;
			}
		}
		if (cv == 0 || cv2 == 1) {
			window.draw(zeroo);
			window.display();
		}
		else if (cv == 25 || cv2 == 2) {
			window.draw(twoo);
			window.display();
		}
		else if (cv == 50 || cv2 == 3) {
			window.draw(threee);
			window.display();
		}
		else if (cv == 75 || cv2 == 4)
		{
			window.draw(four);
			window.display();
		}
		else if (cv == 100 || cv2 == 5) {
			window.draw(five);
			window.display();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace)) {
			cnt = 0;
			cnt1 = 0;
			cnt3 = 0;
		}

	}
	else if ((cnt == 3) && (cnt1 == 3 || cnt3 == 7)) {
		window.draw(pic_credits);
		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace)) {
			cnt = 0;
			cnt1 = 0;
			cnt3 = 0;
			ms.stop();
			gover.stop();
			opm.play();
		}
	}
}

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include <cstdlib>
#include <vector>
#include "Tile.h"
#include <fstream>
#include "Random.h"
using namespace std;

class Board {
    int columns;
    int rows;
    int width;
    int height;
    int minesConfig;
    int mines;
    int flagged = 0;
    bool debug = false;
    bool debugStored = false;
    bool gameOver = false;
    bool gameWon = false;
    map<string, sf::Sprite*> spriteLayer1;
    map<string, sf::Sprite*> spriteLayer2;
    map<string, sf::Sprite*> spriteLayer3;
    map<string, Tile*> tiles;
    map<string, sf::Texture*> textures;
public:
    Board(int columns, int rows, int mines);
    ~Board();
    void CreateBoard();
    void CreateBoard(string BoardName);
    void DeleteMaps();
    void ReadTextures();
    void DrawWindow();
    void ConstantSprites();
    void DrawSprites(sf::RenderWindow &window);
    void FaceSprite();
    void RemainingSprite();
    void ShowBoard();
    void UpdateAllSprites();
    void MouseLeftEvent(int x, int y);
    void MouseRightEvent(int x, int y);
    void Defeat();
    void Victory();
    void Restart();
    void Debug();
    void Test_1();
    void Test_2();
    void Test_3();
    void LotsOfMines();
    void RecursionTest();
};
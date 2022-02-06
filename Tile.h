#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

class Tile {
    int xColumn;
    int yColumn;
    bool mine = false;
    bool flagged = false;
    map<string, Tile*> neighbors;
    int numNeighborMines = 0;
    bool clicked = false;
public:
    void SetLocation(int x, int y);
    void SetMine();
    bool CheckMine();
    void SetNeighbors(const map<string, Tile*> &tiles);
    void DrawState(bool debugSetting, const map<string, sf::Texture*> &textures, map<string, sf::Sprite*> &sprites1, map<string, sf::Sprite*> &sprites2, map<string, sf::Sprite*> &sprites3);
    void Flag(int &flagged);
    bool Click(bool override = false);
    bool GetClicked();
    bool GetFlag();
};
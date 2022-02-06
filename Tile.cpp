#include "Tile.h"
void Tile::SetLocation(int x, int y) {
    this->xColumn = x;
    this->yColumn = y;
    this->mine = false;
}

void Tile::SetMine() {
    mine = true;
}

bool Tile::CheckMine() {
    return mine;
}

void Tile::SetNeighbors(const map<string, Tile*> &tiles) {
    for (int i = -1; i < 2; i++) {
        if (tiles.find(to_string(xColumn) + ":" + to_string(yColumn + i)) != tiles.end()) {
            for (int j = -1; j < 2; j++) {
                if (tiles.find(to_string(xColumn + j) + ":" + to_string(yColumn)) != tiles.end()) {
                    Tile* tile = tiles.find(to_string(xColumn + j) + ":" + to_string(yColumn + i))->second;
                    if (tile->CheckMine()) {
                        numNeighborMines++;
                    }
                    delete neighbors[to_string(xColumn + j) + ":" + to_string(yColumn + i)];
                    neighbors[to_string(xColumn + j) + ":" + to_string(yColumn + i)] = tile;
                }
            }
        }
    }
}

void Tile::DrawState(bool debugSetting, const map<string, sf::Texture*> &textures, map<string, sf::Sprite*> &sprites1, map<string, sf::Sprite*> &sprites2, map<string, sf::Sprite*> &sprites3) {
    sf::Sprite* spriteTile;
    sf::Sprite* result;
    sf::Sprite* flag;
    sf::Sprite* debug;
    if (clicked) {
        spriteTile = new sf::Sprite(*textures.find("tile_revealed")->second);
        if (numNeighborMines > 0 || mine) {
            if (mine) {
                result = new sf::Sprite(*textures.find("mine")->second);
                result->setPosition(xColumn * 32, yColumn * 32);
                if (sprites3.find("result_mine " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites3.end()) {
                    delete sprites3["result_mine " + to_string(xColumn) + ":" + to_string(yColumn)];
                }
                sprites3["result_mine " + to_string(xColumn) + ":" + to_string(yColumn)] = result;
            } else {
                result = new sf::Sprite(*textures.find("number_" + to_string(numNeighborMines))->second);
                result->setPosition(xColumn * 32, yColumn * 32);
                if (sprites2.find("result_num " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites2.end()) {
                    delete sprites2["result_num " + to_string(xColumn) + ":" + to_string(yColumn)];
                }
                sprites2["result_num " + to_string(xColumn) + ":" + to_string(yColumn)] = result;
            }
        }
    }
    else {
        spriteTile = new sf::Sprite(*textures.find("tile_hidden")->second);
        if (flagged) {
            flag = new sf::Sprite(*textures.find("flag")->second);
            flag->setPosition(xColumn * 32, yColumn * 32);
            if (sprites2.find("flag " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites2.end()) {
                delete sprites2["flag " + to_string(xColumn) + ":" + to_string(yColumn)];
            }
            sprites2["flag " + to_string(xColumn) + ":" + to_string(yColumn)] = flag;
        }
        else {
            if (sprites2.find("flag " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites2.end()) {
                delete sprites2["flag " + to_string(xColumn) + ":" + to_string(yColumn)];
                sprites2.erase("flag " + to_string(xColumn) + ":" + to_string(yColumn));
            }
        }
    }
    spriteTile->setPosition(xColumn * 32, yColumn * 32);
    if (sprites1.find("tile " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites1.end()) {
        delete sprites1["tile " + to_string(xColumn) + ":" + to_string(yColumn)];
    }
    sprites1["tile " + to_string(xColumn) + ":" + to_string(yColumn)] = spriteTile;

    if (mine) {
        if (debugSetting) {
            debug = new sf::Sprite(*textures.find("mine")->second);
            debug->setPosition(xColumn * 32, yColumn * 32);
            if (sprites3.find("debug + " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites3.end()) {
                delete sprites3["debug + " + to_string(xColumn) + ":" + to_string(yColumn)];
            }
            sprites3["debug + " + to_string(xColumn) + ":" + to_string(yColumn)] = debug;
        } else if (sprites3.find("debug + " + to_string(xColumn) + ":" + to_string(yColumn)) != sprites3.end()) {
            delete sprites3.find("debug + " + to_string(xColumn) + ":" + to_string(yColumn))->second;
            sprites3.erase("debug + " + to_string(xColumn) + ":" + to_string(yColumn));
        }
    }
}

void Tile::Flag(int &flagged) {
    if (this->flagged) {
        this->flagged = false;
        flagged--;
    }
    else if (!clicked) {
        this->flagged = true;
        flagged++;
    }
}

bool Tile::Click(bool override) {
    bool flagCheck = flagged;
    if (override) {
        flagCheck = false;
    }
    if (!flagCheck && !clicked) {
        clicked = true;
        if (mine) {
            return false;
        }
        else if (numNeighborMines == 0) {
            for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
                iter->second->Click();
            }
        }
        else {
            return true;
        }
    }
    return true;
}

bool Tile::GetClicked() {
    return clicked;
}

bool Tile::GetFlag() {
    return flagged;
}
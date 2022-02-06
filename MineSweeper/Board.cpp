#include "Board.h"
using namespace std;

Board::Board(int columns, int rows, int mines) {
    this->columns = columns;
    this->rows = rows;
    this->minesConfig = mines;
    this->width = this->columns * 32;
    this->height = this->rows * 32 + 88;

    ReadTextures();

    ConstantSprites();


    /* Make CreateBoard() a comment and delete the // in front of either LotsOfMines() or RecursionTest() to use it as the starting board */
    //LotsOfMines();

    //RecursionTest();

    CreateBoard();

    DrawWindow();

}

Board::~Board() {
    for (auto iter = textures.begin(); iter != textures.end(); iter++) {
        delete iter->second;
    }
    textures.clear();

    for (auto iter = spriteLayer1.begin(); iter != spriteLayer1.end(); iter++) {
        delete iter->second;
    }
    spriteLayer1.clear();

    DeleteMaps();
}

void Board::ReadTextures() {
    sf::Texture* debug = new sf::Texture();
    debug->loadFromFile("images/debug.png");
    textures.emplace("debug", debug);

    sf::Texture* digits = new sf::Texture();
    digits->loadFromFile("images/digits.png");
    textures.emplace("digits", digits);

    sf::Texture* face_happy = new sf::Texture();
    face_happy->loadFromFile("images/face_happy.png");
    textures.emplace("face_happy", face_happy);

    sf::Texture* face_lose = new sf::Texture();
    face_lose->loadFromFile("images/face_lose.png");
    textures.emplace("face_lose", face_lose);

    sf::Texture* face_win = new sf::Texture();
    face_win->loadFromFile("images/face_win.png");
    textures.emplace("face_win", face_win);

    sf::Texture* flag = new sf::Texture();
    flag->loadFromFile("images/flag.png");
    textures.emplace("flag", flag);

    sf::Texture* mine = new sf::Texture();
    mine->loadFromFile("images/mine.png");
    textures.emplace("mine", mine);

    sf::Texture* number_1 = new sf::Texture();
    number_1->loadFromFile("images/number_1.png");
    textures.emplace("number_1", number_1);

    sf::Texture* number_2 = new sf::Texture();
    number_2->loadFromFile("images/number_2.png");
    textures.emplace("number_2", number_2);

    sf::Texture* number_3 = new sf::Texture();
    number_3->loadFromFile("images/number_3.png");
    textures.emplace("number_3", number_3);

    sf::Texture* number_4 = new sf::Texture();
    number_4->loadFromFile("images/number_4.png");
    textures.emplace("number_4", number_4);

    sf::Texture* number_5 = new sf::Texture();
    number_5->loadFromFile("images/number_5.png");
    textures.emplace("number_5", number_5);

    sf::Texture* number_6 = new sf::Texture();
    number_6->loadFromFile("images/number_6.png");
    textures.emplace("number_6", number_6);

    sf::Texture* number_7 = new sf::Texture();
    number_7->loadFromFile("images/number_7.png");
    textures.emplace("number_7", number_7);

    sf::Texture* number_8 = new sf::Texture();
    number_8->loadFromFile("images/number_8.png");
    textures.emplace("number_8", number_8);

    sf::Texture* test_1 = new sf::Texture();
    test_1->loadFromFile("images/test_1.png");
    textures.emplace("test_1", test_1);

    sf::Texture* test_2 = new sf::Texture();
    test_2->loadFromFile("images/test_2.png");
    textures.emplace("test_2", test_2);

    sf::Texture* test_3 = new sf::Texture();
    test_3->loadFromFile("images/test_3.png");
    textures.emplace("test_3", test_3);

    sf::Texture* tile_hidden = new sf::Texture();
    tile_hidden->loadFromFile("images/tile_hidden.png");
    textures.emplace("tile_hidden", tile_hidden);

    sf::Texture* tile_revealed = new sf::Texture();
    tile_revealed->loadFromFile("images/tile_revealed.png");
    textures.emplace("tile_revealed", tile_revealed);
}

void Board::ConstantSprites() {
    sf::Sprite* debug = new sf::Sprite(*textures.find("debug")->second);
    debug->setPosition(width - (4 * 64), height - 88);
    spriteLayer1.emplace("debug", debug);

    sf::Sprite* test_1 = new sf::Sprite(*textures.find("test_1")->second);
    test_1->setPosition(width - (3 * 64), height - 88);
    spriteLayer1.emplace("test_1", test_1);

    sf::Sprite* test_2 = new sf::Sprite(*textures.find("test_2")->second);
    test_2->setPosition(width - (2 * 64), height - 88);
    spriteLayer1.emplace("test_2", test_2);

    sf::Sprite* test_3 = new sf::Sprite(*textures.find("test_3")->second);
    test_3->setPosition(width - (1 * 64), height - 88);
    spriteLayer1.emplace("test_3", test_3);
}

void Board::FaceSprite() {
    if (gameWon) {
        sf::Sprite* face_win = new sf::Sprite(*textures.find("face_win")->second);
        face_win->setPosition(width / 2 - 32, height - 88);
        if (spriteLayer1.find("face") != spriteLayer1.end()) {
            delete spriteLayer1["face"];
        }
        spriteLayer1["face"] = face_win;
    }
    else if (gameOver) {
        sf::Sprite* face_lose = new sf::Sprite(*textures.find("face_lose")->second);
        face_lose->setPosition(width / 2 - 32, height - 88);
        if (spriteLayer1.find("face") != spriteLayer1.end()) {
            delete spriteLayer1["face"];
        }
        spriteLayer1["face"] = face_lose;
    }
    else {
        sf::Sprite* face_happy = new sf::Sprite(*textures.find("face_happy")->second);
        face_happy->setPosition(width / 2 - 32, height - 88);
        if (spriteLayer1.find("face") != spriteLayer1.end()) {
            delete spriteLayer1["face"];
        }
        spriteLayer1["face"] = face_happy;
    }
}

void Board::DrawWindow() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    MouseLeftEvent(event.mouseButton.x, event.mouseButton.y);
                }
                else {
                    MouseRightEvent(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        window.clear(sf::Color(190, 190, 190, 255));
        UpdateAllSprites();
        DrawSprites(window);
        window.display();

    }
}

void Board::DrawSprites(sf::RenderWindow &window) {
    for (auto iter = spriteLayer1.begin(); iter != spriteLayer1.end(); iter++) {
        sf::Sprite* sprite = iter->second;
        window.draw(*sprite);
    }

    for (auto iter = spriteLayer2.begin(); iter != spriteLayer2.end(); iter++) {
        sf::Sprite* sprite = iter->second;
        window.draw(*sprite);
    }

    for (auto iter = spriteLayer3.begin(); iter != spriteLayer3.end(); iter++) {
        sf::Sprite* sprite = iter->second;
        window.draw(*sprite);
    }
}

void Board::RemainingSprite() {
    int remaining = mines - flagged;
    bool negative = remaining < 0;
    int remainRight = remaining % 10;
    int remainMiddle = remaining / 10 % 10;
    int remainLeft = remaining / 100 % 10;

    if (negative) {
        remainRight *= -1;
        remainMiddle *= -1;
        remainLeft *= -1;
    }

    sf::Sprite* remainSpriteRight = new sf::Sprite(*textures.find("digits")->second);
    remainSpriteRight->setTextureRect(sf::Rect<int>(remainRight * 21, 0, 21, 32));
    remainSpriteRight->setPosition(3 * 21, height - 88);
    if (spriteLayer1.find("remainSpriteRight") != spriteLayer1.end()) {
        delete spriteLayer1["remainSpriteRight"];
    }
    spriteLayer1["remainSpriteRight"] = remainSpriteRight;

    sf::Sprite* remainSpriteMiddle = new sf::Sprite(*textures.find("digits")->second);
    remainSpriteMiddle->setTextureRect(sf::Rect<int>(remainMiddle * 21, 0, 21, 32));
    remainSpriteMiddle->setPosition(2 * 21, height - 88);
    if (spriteLayer1.find("remainSpriteMiddle") != spriteLayer1.end()) {
        delete spriteLayer1["remainSpriteMiddle"];
    }
    spriteLayer1["remainSpriteMiddle"] = remainSpriteMiddle;

    sf::Sprite* remainSpriteLeft = new sf::Sprite(*textures.find("digits")->second);
    remainSpriteLeft->setTextureRect(sf::Rect<int>(remainLeft * 21, 0, 21, 32));
    remainSpriteLeft->setPosition(1 * 21, height - 88);
    if (spriteLayer1.find("remainSpriteLeft") != spriteLayer1.end()) {
        delete spriteLayer1["remainSpriteLeft"];
    }
    spriteLayer1["remainSpriteLeft"] = remainSpriteLeft;

    auto iter = spriteLayer1.find("remainSpriteNegative");

    if (iter != spriteLayer1.end() && !negative) {
        delete iter->second;
        spriteLayer1.erase(iter);
    }
    else if (negative) {
        sf::Sprite* remainSpriteNegative = new sf::Sprite(*textures.find("digits")->second);
        remainSpriteNegative->setTextureRect(sf::Rect<int>(10 * 21, 0, 21, 32));
        remainSpriteNegative->setPosition(0 * 21, height - 88);
        if (spriteLayer1.find("remainSpriteNegative") != spriteLayer1.end()) {
            delete spriteLayer1["remainSpriteNegative"];
        }
        spriteLayer1["remainSpriteNegative"] = remainSpriteNegative;
    }
}

void Board::ShowBoard() {
    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        iter->second->DrawState(debug, textures, spriteLayer1, spriteLayer2, spriteLayer3);
    }
}

void Board::UpdateAllSprites() {
    FaceSprite();

    RemainingSprite();

    ShowBoard();
}

void Board::MouseLeftEvent(int x, int y) {
    if (y < height - 88) {
        if (!gameOver && !gameWon) {
            if (!tiles.find(to_string(x / 32) + ":" + to_string(y / 32))->second->Click()) {
                Defeat();
            } else {
                bool done = true;
                for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
                    if (!iter->second->GetClicked() && !iter->second->CheckMine()) {
                        done = false;
                        break;
                    }
                }
                if (done) {
                    Victory();
                }
            }
        }
    }
    else if (!(y > height - 24)) {
        if (x >= width / 2 - 32 && x < width / 2 + 32) {
            Restart();
        }
        else if (x >= (width - (64 * 4)) && x < (width - (64 * 3)) && !gameOver && !gameWon) {
            Debug();
        }
        else if (x >= (width - (64 * 3)) && x < (width - (64 * 2))) {
            Test_1();
        }
        else if (x >= (width - (64 * 2)) && x < (width - (64 * 1))) {
            Test_2();
        }
        else if (x >= (width - (64 * 1)) && x < (width - (64 * 0))) {
            Test_3();
        }
    }

}

void Board::MouseRightEvent(int x, int y) {
    if (y < height - 88 && !gameOver && !gameWon) {
        tiles.find(to_string(x / 32) + ":" + to_string(y / 32))->second->Flag(flagged);
    }
}

void Board::Defeat() {
    debugStored = debug;
    debug = false;
    gameOver = true;

    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        if (iter->second->CheckMine()) {
            iter->second->Click(true);
        }
    }
}

void Board::Victory() {
    debugStored = debug;
    debug = false;
    gameWon = true;

    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        if (iter->second->CheckMine() && !iter->second->GetFlag()) {
            iter->second->Flag(flagged);
        }
    }
}

void Board::Restart() {
    CreateBoard();
}

void Board::Debug() {
    if (debug) {
        debug = false;
    }
    else {
        debug = true;
    }
}

void Board::Test_1() {
    CreateBoard("testboard1");
}

void Board::Test_2() {
    CreateBoard("testboard2");
}

void Board::Test_3() {
    CreateBoard("testboard3");
}

void Board::CreateBoard() {
    DeleteMaps();

    if (!gameWon && !gameOver) {
        debugStored = debug;
    }

    debug = debugStored;

    flagged = 0;
    gameOver = false;
    gameWon = false;
    mines = minesConfig;

    //Create Tiles
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            Tile* tile = new Tile();
            tile->SetLocation(j, i);
            if (tiles.find(to_string(j) + ":" + to_string(i)) != tiles.end()) {
                delete tiles[to_string(j) + ":" + to_string(i)];
            }
            tiles[to_string(j) + ":" + to_string(i)] = tile;
        }
    }

    //Set Tiles as Mines
    vector<Tile*> remaining(tiles.size());
    unsigned int index = 0;
    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        remaining.at(index++) = iter->second;
    }
    int minesSet = 0;
    while (minesSet < mines) {
        int randomIndex = Random::RandomNum(remaining.size() - 1);
        Tile* tile = remaining.at(randomIndex);
        tile->SetMine();
        minesSet++;
        remaining[randomIndex] = remaining[remaining.size() - 1];
        remaining.pop_back();
    }

    //Set Neighbors of Each Tile
    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        Tile* tile = iter->second;
        tile->SetNeighbors(tiles);
    }
}

void Board::DeleteMaps() {
    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        delete iter->second;
    }
    tiles.clear();

    for (auto iter = spriteLayer2.begin(); iter != spriteLayer2.end(); iter++) {
        delete iter->second;
    }
    spriteLayer2.clear();

    for (auto iter = spriteLayer3.begin(); iter != spriteLayer3.end(); iter++) {
        delete iter->second;
    }
    spriteLayer3.clear();
}

void Board::CreateBoard(string BoardName) {
    DeleteMaps();

    if (!gameWon && !gameOver) {
        debugStored = debug;
    }

    debug = debugStored;

    flagged = 0;
    gameOver = false;
    gameWon = false;

    //Create Tiles
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            Tile* tile = new Tile();
            tile->SetLocation(j, i);
            if (tiles.find(to_string(j) + ":" + to_string(i)) != tiles.end()) {
                delete tiles[to_string(j) + ":" + to_string(i)];
            }
            tiles[to_string(j) + ":" + to_string(i)] = tile;
        }
    }

    //Set Tiles as Mines
    ifstream file("boards/" + BoardName + ".brd");
    string tileRow;
    int mineCount = 0;
    int tileStatus;
    for (unsigned int i = 0; i < rows; i++) {
        getline(file, tileRow);
        for (unsigned int j = 0; j < columns; j++) {
            tileStatus = stoi(tileRow.substr(j, 1));
            if (tileStatus == 1) {
                mineCount++;
                tiles.find(to_string(j) + ":" + to_string(i))->second->SetMine();
            }
        }
    }
    file.close();

    mines = mineCount;

    //Set Neighbors of Each Tile
    for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
        Tile* tile = iter->second;
        tile->SetNeighbors(tiles);
    }
}

void Board::LotsOfMines() {
    CreateBoard("lots_o_mines");
}

void Board::RecursionTest() {
    CreateBoard("recursion_test");
}

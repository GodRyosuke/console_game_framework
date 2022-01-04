#include "Game.hpp"

Game::Game()
    :MazeWidth(0),
    MazeHeight(0)
{
    // GameFiledDataの初期化
    CellAA = new char* [NUM_CELL_DATA];
    for (int i = 0; i < NUM_CELL_DATA; i++) {
        char* temp_cell = new char[3];
    }
    CellAA[0] = "　";
    CellAA[1] = "■";
    CellAA[2] = "〇";
    CellAA[3] = "・";

    MonsterAA = new char*[NUM_MONSTER_TYPE];
    for (int i = 0; i < NUM_MONSTER_TYPE; i++) {
        MonsterAA[i] = new char[3];
    }
    MonsterAA[0] = "◎";
    MonsterAA[1] = "赤";
    MonsterAA[2] = "青";
    MonsterAA[3] = "桃";
    MonsterAA[4] = "橙";
}

std::string Game::ReadFile(std::string file_name)
{
	std::ifstream file;
	file.open(file_name, std::ios::in);
	std::stringstream contents;

	if (!file.fail()) {
		contents << file.rdbuf();
	}

	return contents.str();
}

void get_pos(int cell_count, const int MazeWidth, int& x, int& y)
{
    y = cell_count / MazeWidth;
    x = cell_count % MazeWidth;
}

void Game::LoadFieldData()
{
    // Field Dataの取得
    FILE* fp;
    if ((fp = fopen("GameData/GameField.txt", "r")) == NULL) { 
        std::cout << "file open error\a" << std::endl;
        exit(1);
    }
    char c;
    bool first_line = true;
    int cell_count = 0;
    std::vector<CellData> cell_type_vec;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            MazeHeight++;
            if (first_line) {
                first_line = false;
            }
            continue;
        }
        if (first_line) {
            MazeWidth++;
        }
        //putchar(c);
        CellData cell_data;
        switch (c) { // game field data
            case '#':
                cell_data = CELL_TYPE_WALL;
                break;
            case '*':
                cell_data = CELL_TYPE_DOT;
                break;
            case '0':
                cell_data = CELL_TYPE_POWER;
                break;
            case ' ':
                cell_data = CELL_TYPE_NONE;
                break;
            default:
                cell_data = CELL_TYPE_MONSTER;
                int x, y;
                MonsterPos mp;
                MonsterData monster_name;
                switch (c) { // monster data
                    case 'b':
                        get_pos(cell_count, MazeWidth, x, y);
                        mp.x = x;
                        mp.y = y;
                        monster_name = MONSTER_TYPE_BLUE;
                        break;
                    case 'r':
                        get_pos(cell_count, MazeWidth, x, y);
                        mp.x = x;
                        mp.y = y;
                        monster_name = MONSTER_TYPE_RED;
                        break;
                    case 'p':
                        get_pos(cell_count, MazeWidth, x, y);
                        mp.x = x;
                        mp.y = y;
                        monster_name = MONSTER_TYPE_PINK;
                        break;
                    case 'y':
                        get_pos(cell_count, MazeWidth, x, y);
                        mp.x = x;
                        mp.y = y;
                        monster_name = MONSTER_TYPE_ORANGE;
                        break;
                    case '@':
                        get_pos(cell_count, MazeWidth, x, y);
                        mp.x = x;
                        mp.y = y;
                        monster_name = MONSTER_TYPE_PAC;
                        break;
                }
                MonsterPosMap.insert(std::make_pair(monster_name, mp));
        }
        cell_type_vec.push_back(cell_data);
        cell_count++;
    }


    CellTypeData.resize(cell_count);
    for (int i = 0; i < cell_count; i++) {
        CellTypeData[i] = cell_type_vec[i];
    }
}

void Game::Display()
{
    if (MazeHeight == 0 || MazeWidth == 0) {
        printf("Field Data has not yet loaded\n");
        exit(0);
    }

    std::system("cls");
    //system("cls");
    for (int y = 0; y < MazeHeight; y++) {
        for (int x = 0; x < MazeWidth; x++) {
            CellData cell_data = CellTypeData[y * MazeWidth + x];
            if (cell_data == CELL_TYPE_MONSTER) { // モンスター描画
                MonsterData monster_data;
                for (auto itr = MonsterPosMap.begin(); itr != MonsterPosMap.end(); itr++) {
                    if ((itr->second.x == x) && (itr->second.y == y)) {
                        monster_data = itr->first;
                    }
                }
                std::cout << MonsterAA[monster_data];
            }
            else { // フィールド描画
                std::cout << CellAA[CellTypeData[y * MazeWidth + x]];
            }
            //printf(CellAA[CellTypeData[y * MazeWidth + x]]);
            //int monster = getMonster(x, y);
            //if (monster >= 0) { // モンスターがいれば、モンスターを表示
            //    printf(monsterAA[monster]);
            //}
          /*  else {
                printf(cellAA[cells[y * MAZE_WIDTH + x]]);
            }*/
        }
        //printf("\n");
        std::cout << std::endl;
    }

}

void Game::Run()
{
    LoadFieldData();

    while (true) {
        Display();

        // パックマンの座標の更新
        {
            int x = MonsterPosMap[MONSTER_TYPE_PAC].x;
            int y = MonsterPosMap[MONSTER_TYPE_PAC].y;
            int previous_x = x;
            int previous_y = y;
            char c = _getch();
            switch (c) {
            case 'w': y--; break;
            case 'd': x++; break;
            case 's': y++; break;
            case 'a': x--; break;
            }

            // 移動先が壁か否か
            if ((y * MazeWidth + x) >= CellTypeData.size()) {
                std::cout << "error: you cannnot move out of maze" << std::endl;
                exit(1);
            }
            if (CellTypeData[y * MazeWidth + x] == CELL_TYPE_WALL) {
                // 壁なら更新しない
            }
            else {
                // パックマンがドットを食べる
                CellTypeData[y * MazeWidth + x] = CELL_TYPE_MONSTER;
                // パックマン移動
                MonsterPosMap[MONSTER_TYPE_PAC].x = x;
                MonsterPosMap[MONSTER_TYPE_PAC].y = y;
                // 元居た場所はCELL_TYPE_NONEにする
                CellTypeData[previous_y * MazeWidth + previous_x] = CELL_TYPE_NONE;
            }


        }
    }

}
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
    for (int i = 0; i < NUM_CELL_DATA; i++) {
        CellAA[i] = "　";
    }
    CellAA[0] = "　";
    CellAA[1] = "■";
    CellAA[2] = "〇";
    CellAA[3] = "・";
    CellAA[4] = "◎";
    CellAA[5] = "赤";
    CellAA[6] = "青";
    CellAA[7] = "桃";
    CellAA[8] = "橙";
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
                switch (c) { // monster data
                    case 'b':
                        cell_data = MONSTER_TYPE_BLUE;
                        break;
                    case 'r':
                        cell_data = MONSTER_TYPE_RED;
                        break;
                    case 'p':
                        cell_data = MONSTER_TYPE_PINK;
                        break;
                    case 'y':
                        cell_data = MONSTER_TYPE_ORANGE;
                        break;
                    case '@':
                        cell_data = MONSTER_TYPE_PAC;
                        break;
            }
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
            std::cout << CellAA[CellTypeData[y * MazeWidth + x]];
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
        int x = 0;
        int y = 0;
        char c = _getch();
        switch (c) {
        case 'w': y--; break;
        case 'd': x++; break;
        case 's': y++; break;
        case 'a': x--; break;
        }
    }

}
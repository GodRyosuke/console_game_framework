#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <conio.h>

class Game {
public:
	Game();
	void Run();

private:
	enum CellData{
		CELL_TYPE_NONE,
		CELL_TYPE_WALL,
		CELL_TYPE_POWER,
		CELL_TYPE_DOT,
		MONSTER_TYPE_PAC,
		MONSTER_TYPE_RED,
		MONSTER_TYPE_BLUE,
		MONSTER_TYPE_PINK,
		MONSTER_TYPE_ORANGE,
		NUM_CELL_DATA
	};


	std::string ReadFile(std::string file_name);
	void LoadFieldData();
	void Display(); // �`�悷��

	int MazeWidth;
	int MazeHeight;

	char** CellAA; // CellType�ƕ`����Ƃ̑Ή��t��

	std::vector<CellData> CellTypeData;
};
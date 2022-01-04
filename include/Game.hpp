#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <conio.h>

class Game {
public:
	Game();
	void Run();

private:
	struct MonsterPos {
		int x;
		int y;
	};

	enum CellData{
		CELL_TYPE_NONE,
		CELL_TYPE_WALL,
		CELL_TYPE_POWER,
		CELL_TYPE_DOT,
		CELL_TYPE_MONSTER,
		NUM_CELL_DATA
	};


	enum MonsterData {
		MONSTER_TYPE_PAC,
		MONSTER_TYPE_RED,
		MONSTER_TYPE_BLUE,
		MONSTER_TYPE_PINK,
		MONSTER_TYPE_ORANGE,
		NUM_MONSTER_TYPE
	};

	std::string ReadFile(std::string file_name);
	void LoadFieldData();
	void Display(); // ï`âÊÇ∑ÇÈ

	int MazeWidth;
	int MazeHeight;

	char** CellAA; // CellTypeÇ∆ï`âÊèÓïÒÇ∆ÇÃëŒâûïtÇØ
	char** MonsterAA;

	std::vector<CellData> CellTypeData;
	std::map <MonsterData, MonsterPos> MonsterPosMap;
};
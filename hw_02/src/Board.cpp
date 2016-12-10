#include "Board.h"

Board::Board(int h, int w) {
	if (h < 5)
		h = 5;
	if (w < 5)
		w = 5;

	board = new cell_status*[h];
	board[0] = new cell_status[h * w];
	std::fill(board[0], board[0] + h * w, cell_free);
	for (int i = 0; i < h; i++)
		board[i] = board[0] + i * w;

	result = new res*[h];
	result[0] = new res[h * w];
	std::fill(result[0], result[0] + h * w, 0);
	for (int i = 0; i < h; i++)
		result[i] = result[0] + i * w;

	height = h;
	widgth = w;
}

Board::~Board() {
	delete[] board[0];
	delete[] board;

	delete[] result[0];
	delete[] result;
}

void Board::move(int x, int y, cell_status sign) {
	board[y][x] = sign;
	result[y][x].h  = 1; 
	result[y][x].v  = 1; 
	result[y][x].d1 = 1; 
	result[y][x].d2 = 1; 
}

bool Board::can_move(int x, int y, cell_status sign) const {
	bool all_is_ok = true;
	if (sign == cell_free)
		all_is_ok = false;

	if (x >= this->get_widgth() || x < 0 ||
		y >= this->get_height() || y < 0)
		all_is_ok = false;

	if (board[y][x] != cell_free)
		all_is_ok = false;

	if (all_is_ok)
		return true;
	return false;

}

game_status Board::is_win() {
	bool draw = 1;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < widgth; j++) {
			if (board[i][j] == cell_free) {
				draw = 0;
				continue;
			}

			if (i > 0 && board[i - 1][j] == board[i][j] 
				&& result[i - 1][j].v >= result[i][j].v)
				result[i][j].v = result[i - 1][j].v +1;

			if (j > 0 && board[i][j - 1] == board[i][j] 
				&& result[i][j - 1].h >= result[i][j].h)
				result[i][j].h = result[i][j - 1].h +1;

			if (i > 0 && j > 0 && board[i - 1][j - 1] == board[i][j]
				&& result[i - 1][j - 1].d1 >= result[i][j].d1)
				result[i][j].d1 = result[i - 1][j - 1].d1 +1;

			if (i > 0 && j < height-1 && board[i - 1][j + 1] == board[i][j]
				&& result[i - 1][j + 1].d2 >= result[i][j].d2)
				result[i][j].d2 = result[i - 1][j + 1].d2 +1;

			if (result[i][j].h >= 5 || result[i][j].v >=5 ||
				result[i][j].d1 >= 5 || result[i][j].d2 >=5)
				return game_win;
		}

	if (draw)
		return game_draw;

	return game_in_progress;
}

cell_status Board::get_cell(int x, int y) const {
	return board[x][y];
}

int Board::get_widgth() const {
	return widgth;
}

int Board::get_height() const {
	return height;
}
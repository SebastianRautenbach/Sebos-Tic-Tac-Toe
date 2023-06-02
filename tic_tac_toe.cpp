#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#define _AI 0
#define _PLAYER 1
#define _INVALID_PLAYER -1


/*
							    ____                              _
							   / __ \__  ______  ____ _____ ___  (_)____
							  / / / / / / / __ \/ __ `/ __ `__ \/ / ___/
							 / /_/ / /_/ / / / / /_/ / / / / / / / /__
							/_____/\__, /_/ /_/\__,_/_/ /_/ /_/_/\___/
							      /____/
							 _______       ______           ______
							/_  __(_)___  /_  __/__ _____  /_  __/__  ___
							 / / / / __/   / / / _ `/ __/   / / / _ \/ -_)
							/_/ /_/\__/   /_/  \_,_/\__/   /_/  \___/\__/

								 _ __  __      ___     ____
							 _    __(_) /_/ /     / _ |   /  _/
							| |/|/ / / __/ _ \   / __ |_ _/ /
							|__,__/_/\__/_//_/  /_/ |_(_)___/
*/




/*

  This is a simple Tic Tac Toe game with simple checks but
  it has one feature that not a lot of tic tac toe's do,
  it has AI lol.

  JUST TO CLARIFY I SHOULD OF USED A ENUM FOR THE PLAYER AND AI :(
  but defining it is also viable.

  This was created by Sebastian R. with no outside help, this
  was to test my skill and yes there can be major improvements made
  my next goal would be to make this AI learn from past play troughs 

*/

//  r|c r|c r|c
//  ___________
//  0|0 1|0 2|0 ...
//  0|1 1|1 2|1 ...
//  0|2 1|2 2|2	...
//  ... ... ...

class tile { // this class is self explanatory 
public:
	bool checked = false;
	int player_chose = -1;
};



class grid { // the grid is a collection of a 2 Dimensional array of tiles
public:
	size_t grid_size = 3;
	tile** m_tile_layout;

	grid() // this sets up the grid and nulls out any null values in the grid
	{
		std::cout << "please select grid size:";
		std::cin >> grid_size;
		system("cls");

		resize_grid_arr(grid_size);
		for (int row = 0; row < grid_size; row++)
		{
			for (int col = 0; col < grid_size; col++)
			{
				m_tile_layout[row][col].checked = false;
				m_tile_layout[row][col].player_chose = _INVALID_PLAYER;
			}
		}
	}
	~grid() {
		delete_grid();
	}
	bool choose_block(int player, int row, int col) // setting info in a tile and checking if its taken or not
	{
		if(m_tile_layout[row][col].player_chose != _INVALID_PLAYER)
		{ 
			std::cout << "tile already took. row:" << row << " col:" << col << std::endl;
			return false; 
		}
		{
			m_tile_layout[row][col].checked = true;
			m_tile_layout[row][col].player_chose = player;
			std::cout << "tile took. row:" << row << " col:" << col << std::endl;
			return true;
		}
	}
	// the grid needs to be removed from the heap
	void inline delete_grid() {
		for (int i = 0; i < grid_size; i++)
			delete[] m_tile_layout[i];
	}
	// this is to resize the grid dynamically 
	void resize_grid_arr(size_t arr_size = 3) {
		m_tile_layout = new tile * [arr_size];
		for (int i = 0; i < arr_size; i++)
		{
			m_tile_layout[i] = new tile[arr_size];
		}
	}
	// this checks for matching tiles with the same player ID in a vertical and horizontal orientation 
	int grid_row_col_check(int check_sequence, int stationary_sequence, int max_size = 2) // This will get the job done to check for any defined number sequential patterns
	{
		size_t incremented_grid_win = 0, max_left = 0, max_right= 0;
		int last_player_id = -1;
		
		
		
		// do right jump to find max block so that a null array element cant be called
		for (int i = check_sequence; i < check_sequence + max_size; i++)
		{
			if (i < grid_size - 1)
			{
				max_right++;
			}
		}

		// do left jump to find max block so that a null array element cant be called
		for (int i = check_sequence; i > check_sequence - max_size; i--)
		{
 			if (i > 0) // correct
 			{
				max_left++;
			}
			
		}

		//do a check to see in the range we obtained from the last two loops if there is three in a row or column
		for (int i = check_sequence - max_left; i < check_sequence + max_right + 1; i ++) {
			if (m_tile_layout[stationary_sequence][i].player_chose == last_player_id && last_player_id != _INVALID_PLAYER)
			{
				incremented_grid_win++;
			}
			else
			{
				incremented_grid_win = 0;
				last_player_id = m_tile_layout[stationary_sequence][i].player_chose;
			}
			if (incremented_grid_win > 1)
			{
				return last_player_id;
			}
		}
		return _INVALID_PLAYER;
	}
	// this checks for matching tiles with the same player ID in a diagonal orientation 
	int grid_diagonal_check(int row, int col, int max_size_up = 1, int max_size_down = 1) {
		
		size_t  max_left = 0, max_right = 0, max_up = 0, max_down = 0;


		// these few if statements is there just to avoid null indexes
		if (row - 1 > 0)
			max_left = row - 1;
		if (row + 1 < grid_size)
			max_right = row + 1;
		if (col - max_size_up > 0)
			max_up = col - max_size_up;
		if (col + max_size_down < grid_size)
			max_down = col + max_size_down;


		// check for any aligning diagonals from a player  
		if (m_tile_layout[max_left][max_up].player_chose == m_tile_layout[max_right][max_down].player_chose &&
			m_tile_layout[max_right][max_down].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[max_right][max_down].player_chose;
		}
		if (m_tile_layout[max_left][max_down].player_chose == m_tile_layout[max_right][max_up].player_chose &&
			m_tile_layout[max_left][max_down].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[max_left][max_down].player_chose;
		}

		return _INVALID_PLAYER;
	}

	int check_for_win()

	{
		for (int col = 0; col < grid_size; col++)
		{
			for (int row = 0; row < grid_size; row++)
			{
				if (m_tile_layout[row][col].player_chose != -1)
				{
					std::cout << grid_diagonal_check(row, col) << std::endl;
					std::cout << grid_row_col_check(col, row) << std::endl;
					std::cout << grid_row_col_check(row,col) << std::endl;
				}
			}
		}


		// This part of the program checks if all tiles are filled
		bool all_tiles_taken = true;
		
		for (int col = 0; col < grid_size; col++)
		{
			for (int row = 0; row < grid_size; row++)
			{
				if (!m_tile_layout[row][col].checked)
				{
					all_tiles_taken = false;
				}
			}
		}
		if (all_tiles_taken)
		{
			return 2;
		}
		
		return -1;
	}
	
	std::string get_grid_infromat() {
		std::string final_data_fromat;
		for (int row = 0; row < grid_size; row++)
		{
			for (int col = 0; col < grid_size; col++)
			{
				if (m_tile_layout[row][col].player_chose == _PLAYER)
				{
					final_data_fromat += "x";
				}
				if (m_tile_layout[row][col].player_chose == _INVALID_PLAYER)
				{
					final_data_fromat += "~";
				}
				if (m_tile_layout[row][col].player_chose == _AI)
				{
					final_data_fromat += "o";
				}
				
			}
			final_data_fromat += ",";
		}
		return final_data_fromat;
	}
};

class super_AI {
public:
	grid* m_grid;
	super_AI(grid& grid_ref)
		:m_grid(&grid_ref)
	{
		
	}
	~super_AI() {}
	void make_move()
	// this is basically the AI XD, working down from most important to least important 
	// move
	{
		if (check_tiles_for_AI())
		{
			return;
		}
		if (check_tiles_for_player())
		{
			return;
		}
 		if (check_tile_patterns())
 		{
 			return;
 		}
	}

	bool check_tiles_for_player() {
		
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				if (m_grid->m_tile_layout[row][col].player_chose == 1)
				{
					if (check_next_tiles(_PLAYER, _AI ,row, col))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool check_tiles_for_AI() {
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				if (m_grid->m_tile_layout[row][col].player_chose == 0)
				{
					if (check_next_tiles(_AI, _AI, row, col)) // time to change this
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool check_next_tiles(int opp_plr_id, int player_id, int row, int col) // gonna needa change this 
	{

		{	// Diagonal Check
			if (row == 0 && col == 0)
			{
				if (m_grid->m_tile_layout[1][1].player_chose == opp_plr_id && m_grid->m_tile_layout[2][2].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 2, 2))
						return true;
				}
				if (m_grid->m_tile_layout[2][2].player_chose == opp_plr_id && m_grid->m_tile_layout[1][1].player_chose != player_id)
				{
					if (m_grid->choose_block(player_id, 1, 1))
						return true;
				}
			}
			if (row == 2 && col == 0)
			{
				if (m_grid->m_tile_layout[1][1].player_chose == opp_plr_id && m_grid->m_tile_layout[0][2].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 0, 2))
						return true;
				}
				else if (m_grid->m_tile_layout[0][2].player_chose == opp_plr_id && m_grid->m_tile_layout[1][1].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 1, 1))
						return true;
				}
			}
		}
		{	//Horizontal && vertical check

			/*
					This check works by getting the row or column value that the player_id is found at, then doing a check to see if
					any other tile that is selected by the player_id will allow a win
			
			*/

			// Vertical
			switch (row)
			{
			case 0:
				if (m_grid->m_tile_layout[1][col].player_chose == opp_plr_id && m_grid->m_tile_layout[2][col].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 2, col))
						return true;
				}
				if (m_grid->m_tile_layout[2][col].player_chose == opp_plr_id && m_grid->m_tile_layout[1][col].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 1, col))
						return true;
				}
				break;
			
			case 1:
				if (m_grid->m_tile_layout[0][col].player_chose == opp_plr_id && m_grid->m_tile_layout[2][col].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 2, col))
						return true;
				}
				if (m_grid->m_tile_layout[2][col].player_chose == opp_plr_id && m_grid->m_tile_layout[0][col].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 0, col))
						return true;
				}
				break;
			
			case 2:
				if (m_grid->m_tile_layout[0][col].player_chose == opp_plr_id && m_grid->m_tile_layout[1][col].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 1, col))
						return true;
				}
				if (m_grid->m_tile_layout[1][col].player_chose == opp_plr_id && m_grid->m_tile_layout[0][col].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, 0, col))
						return true;
				}
				break;
			}
			
			
			
			//Horizontal              
			switch (col)
			{
			case 0:
				if (m_grid->m_tile_layout[row][1].player_chose == opp_plr_id && m_grid->m_tile_layout[row][2].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, row, 2))
						return true;
				}
				if (m_grid->m_tile_layout[row][2].player_chose == opp_plr_id && m_grid->m_tile_layout[row][1].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, row, 1))
						return true;
				}
				break;
			
			case 1:
				if (m_grid->m_tile_layout[row][0].player_chose == opp_plr_id && m_grid->m_tile_layout[row][2].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, row, 2))
						return true;
				}
				if (m_grid->m_tile_layout[row][2].player_chose == opp_plr_id && m_grid->m_tile_layout[row][0].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, row, 0))
						return true;
				}
				break;
			
			case 2:
				if (m_grid->m_tile_layout[row][0].player_chose == opp_plr_id && m_grid->m_tile_layout[row][1].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, row, 1))
						return true;
				}
				if (m_grid->m_tile_layout[row][1].player_chose == opp_plr_id && m_grid->m_tile_layout[row][0].player_chose != player_id)
				{
					if(m_grid->choose_block(player_id, row, 0))
						return true;
				}
				break;
			}
		}
		return false;
	}
	bool check_tile_patterns() {
		if (side_pattern())
			return true;
		if (seq_pattern())
			return true;
		return false;
	
	}
	bool side_pattern() {
		if (!m_grid->m_tile_layout[0][0].checked)
		{
			if(m_grid->choose_block(_AI, 0, 0))
				return true;
		}
		if (!m_grid->m_tile_layout[2][2].checked)
		{
			if(m_grid->choose_block(_AI, 2, 2))
				return true;
		}
		if (!m_grid->m_tile_layout[0][2].checked)
		{
			if(m_grid->choose_block(_AI, 0, 2))
				return true;
		}
		if (!m_grid->m_tile_layout[2][0].checked)
		{
			if(m_grid->choose_block(_AI, 0, 2))
				return true;
		}
		return false;
	}
	bool seq_pattern() {
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				if (!m_grid->m_tile_layout[row][col].checked)
				{
					if(m_grid->choose_block(_AI, row, col))
						return true;
				}
			}
		}
		return false;
	}
	void find_pattern()
	{
 		std::string _get_line, _file_data;
 		std::fstream data_file("C:/Users/sebog/Desktop/file_test/1.txt");
		std::string grid_fromat = m_grid->get_grid_infromat(); //get layout of current game
 
 		while (std::getline(data_file, _get_line)) {
 			_file_data += _get_line;
 			_file_data += '\n';
 		}
		


	}
	// will add other patterns some other time
};

class player_console {
public:
	void clear_console() //clears the console
	{
		//system("cls");
	}
	void draw_grid_debug(grid& m_grid) //just loops through every array index and draws its state
	{
		for (int i = 0; i < m_grid.grid_size; i++)
		{
			for (int y = 0; y < m_grid.grid_size; y++)
			{
				std::cout << " {row:" << y << " col:" << i << " player_val:" << m_grid.m_tile_layout[y][i].player_chose << "}";
			}
			std::cout << "" << std::endl;
		}
	}
	void draw_grid_simple(grid& m_grid) //just loops through every array index and draws its state
	{
		for (int i = 0; i < m_grid.grid_size; i++)
		{
			for (int y = 0; y < m_grid.grid_size; y++)
			{
				if (m_grid.m_tile_layout[y][i].player_chose == 1)
				{
					std::cout << "[X]";
				}
				if (m_grid.m_tile_layout[y][i].player_chose == 0)
				{
					std::cout << "[O]";
				}
				if (m_grid.m_tile_layout[y][i].player_chose == -1)
				{
					std::cout << "[ ]";
				}

			}
			std::cout << "" << std::endl;
		}
	}

	void draw_text(std::string text, bool clr_screen) // draws text but you can clear the screen
	{
		if (clr_screen)
			clear_console();
		std::cout << text << std::endl;
	}
};
class player {
private:
	grid* m_grid;
	player_console console;
public:
	player(grid& grid_ref)
		:m_grid(&grid_ref)
	{
	}
	void promt_block_choose() {
		std::string the_chosen_one, row, col;

		console.draw_text("choose a block, remember only 2 whole numbers \n", false);
		std::cin >> the_chosen_one;

		if (the_chosen_one.size() != 2)
		{
			console.clear_console();
			console.draw_text("remember 2 numbers with no space! \n", false);
			promt_block_choose();
			return; // this prevents the first recursion of the function to continue
		}

		row += the_chosen_one[0];
		col += the_chosen_one[1];

		if (stoi(row) > m_grid->grid_size || stoi(col) > m_grid->grid_size)
		{
			console.clear_console();
			console.draw_text("numbers should not exceed grid size! \n", false);
			promt_block_choose();
			return; // this prevents the first recursion of the function to continue
		}

		if (!m_grid->choose_block(_PLAYER, stoi(row), stoi(col))) {
			console.clear_console();
			console.draw_text("Tile already selected! \n", false);
			promt_block_choose();
			return; // this prevents the first recursion of the function to continue
		}

		console.clear_console();
	}
};


int main() {
	



	grid* m_grid = new grid;
	super_AI m_AI(*m_grid);
	player m_player(*m_grid);
	player_console console;
	bool someone_won = false;


	while (!someone_won)
	{
		m_player.promt_block_choose();
		if (m_grid->check_for_win() != _INVALID_PLAYER && m_grid->check_for_win() != 2)
		{
			std::cout << "Player:" << m_grid->check_for_win() << " WON!!" << std::endl;
			someone_won = true;
			break;
		}
		else if (m_grid->check_for_win() == 2)
		{
			std::cout << "No one won!" << std::endl;
			std::cout << "Life is a loosing game :(" << std::endl;
			someone_won = true;
			break;
		}

		m_AI.make_move();
		console.clear_console();
		console.draw_grid_simple(*m_grid);
		if (m_grid->check_for_win() != _INVALID_PLAYER && m_grid->check_for_win() != 2)
		{
			std::cout << "Player:" << m_grid->check_for_win() << " WON!!" << std::endl;
			someone_won = true;
			break;
		}
		else if (m_grid->check_for_win() == 2)
		{
			std::cout << "No one won!" << std::endl;
			std::cout << "Life is a loosing game :(" << std::endl;
			someone_won = true;
			break;
		}
	}
	system("pause");
	
	return 0;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#define _AI 0
#define _PLAYER 1
#define _INVALID_PLAYER -1


/*
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
//  0|0 1|0 2|0
//  0|1 1|1 2|1
//  0|2 1|2 2|2

class tile { // this class is self explanatory 
public:
	bool checked = false;
	int player_chose = -1;
};



class grid { // the grid is a collection of a 2 Dimensional array of tiles
public://              r  c  
	tile m_tile_layout[3][3];

	grid() // this sets up the grid and nulls out any null values in the grid
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				m_tile_layout[row][col].checked = false;
				m_tile_layout[row][col].player_chose = _INVALID_PLAYER;
			}
		}
	}
	~grid() {
		delete[] m_tile_layout;
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
	int check_for_win() // lucky there is only 8 win combos XD so I might as well write all of them
	{

		if (m_tile_layout[0][0].player_chose == m_tile_layout[0][1].player_chose && m_tile_layout[0][0].player_chose == m_tile_layout[0][2].player_chose && m_tile_layout[0][2].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[0][0].player_chose;
		}
		if (m_tile_layout[1][0].player_chose == m_tile_layout[1][1].player_chose && m_tile_layout[1][0].player_chose == m_tile_layout[1][2].player_chose && m_tile_layout[1][2].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[1][0].player_chose;
		}
		if (m_tile_layout[2][0].player_chose == m_tile_layout[2][1].player_chose && m_tile_layout[2][0].player_chose == m_tile_layout[2][2].player_chose && m_tile_layout[2][2].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[2][0].player_chose;
		}
		if (m_tile_layout[0][0].player_chose == m_tile_layout[1][0].player_chose && m_tile_layout[0][0].player_chose == m_tile_layout[2][0].player_chose && m_tile_layout[2][0].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[0][0].player_chose;
		}
		if (m_tile_layout[0][1].player_chose == m_tile_layout[1][1].player_chose && m_tile_layout[0][1].player_chose == m_tile_layout[2][1].player_chose && m_tile_layout[2][1].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[0][1].player_chose;
		}
		if (m_tile_layout[0][2].player_chose == m_tile_layout[1][2].player_chose && m_tile_layout[0][2].player_chose == m_tile_layout[2][2].player_chose && m_tile_layout[2][2].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[0][2].player_chose;
		}
		if (m_tile_layout[0][0].player_chose == m_tile_layout[1][1].player_chose && m_tile_layout[0][0].player_chose == m_tile_layout[2][2].player_chose && m_tile_layout[2][2].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[0][0].player_chose;
		}
		if (m_tile_layout[2][0].player_chose == m_tile_layout[1][1].player_chose && m_tile_layout[2][0].player_chose == m_tile_layout[0][2].player_chose && m_tile_layout[0][2].player_chose != _INVALID_PLAYER)
		{
			return m_tile_layout[0][0].player_chose;
		}
		

		// This part of the program checks if all tiles are filled
		bool all_tiles_taken = true;
		
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
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
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
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

	int int_to_str(const char* _Ptr, size_t* _Idx = nullptr, int _Base = 10) 
	{
	
			int& _Errno_ref = errno; // Nonzero cost, pay it once
			char* _Eptr;
			_Errno_ref = 0;
			const long _Ans = _CSTD strtol(_Ptr, &_Eptr, _Base);

			if (_Ptr == _Eptr) {
				/*_Xinvalid_argument("invalid stoi argument");*/
			}

			if (_Errno_ref == ERANGE) {
				/*_Xout_of_range("stoi argument out of range");*/
			}

			if (_Idx) {
				*_Idx = static_cast<size_t>(_Eptr - _Ptr);
			}

			return static_cast<int>(_Ans);
		
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
					if (check_next_tiles(_AI, _AI, row, col))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	bool check_next_tiles(int opp_plr_id, int player_id, int row, int col)
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
		//going to compare crnt game with past games
		//still dont know how i am gonna achieve it but hey :)


	}
	// will add other patterns some other time
};

class player_console {
public:
	void clear_console() //clears the console
	{
		system("cls");
	}
	void draw_grid_debug(grid& m_grid) //just loops through every array index and draws its state
	{
		for (int i = 0; i < 3; i++)
		{
			for (int y = 0; y < 3; y++)
			{
				std::cout << " {row:" << y << " col:" << i << " player_val:" << m_grid.m_tile_layout[y][i].player_chose << "}";
			}
			std::cout << "" << std::endl;
		}
	}
	void draw_grid_simple(grid& m_grid) //just loops through every array index and draws its state
	{
		for (int i = 0; i < 3; i++)
		{
			for (int y = 0; y < 3; y++)
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

		if (stoi(row) > 2 || stoi(col) > 2)
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

#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include <stdio.h>      
#include <stdlib.h>    
#include "engimon.hpp"
#include "skill.hpp"
#include "tile.hpp"
using namespace std;

#define start_seed 1357

int tile::random_seed = start_seed;
engimon tile::universal_nullEngimon;
tile::tile()
{
	this->x = -1;
	this->y = -1;
	engimon nullEngimon;
	this->wild_engimon = nullEngimon;
	this->symbol = '-';
	this->tile_type = "grassland";
	this->tilePass = false;
}
tile::tile(int x, int y, engimon e, string type)
{
	this->x = x;
	this->y = y;
	this->wild_engimon = e;
	this->tile_type = type; //Hanya berupa grassland atau sea

	if (type == "sea")
	{
		symbol = 'o';
	}
	else
	{
		symbol = '-';
	}

	this->tilePass = false;

}
tile::~tile(){}

bool tile::isTileValid(engimon e)
{
	if ( ((e.getElmt1() == "Fire" || e.getElmt1() == "Ground" || e.getElmt1() == "Electric")
	|| (e.getElmt2() == "Fire" || e.getElmt2() == "Ground" || e.getElmt2() == "Electric"))
	&& this->tile_type == "grassland")
	{
		return true;
	}
	else if ( ((e.getElmt1() == "Water" || e.getElmt1() == "Ice")
	|| (e.getElmt2() == "Water" || e.getElmt2() == "Ice"))
	&& this->tile_type == "sea")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tile::haveWildPokemon()
{
	if (this->wild_engimon.isNull())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void tile::passed()
{
	this->tilePass = true;
}
void tile::resetPass()
{
	this->tilePass = false;
}
bool tile::isPass()
{
	return tilePass;
}
void tile::spawn()
{
	int species_count = engimon::all_species.size();

	/*Random module*/
	srand(tile::random_seed);
	tile::random_seed++;
	int randomNumber;
	randomNumber = rand() %  species_count;
	srand(tile::random_seed);
	tile::random_seed++;
	int randomLevel = rand() % 30 + 1;
	srand(tile::random_seed);
	tile::random_seed++;

	/*Find a species*/

	auto idx = engimon::all_species.begin();
	for (auto i = engimon::all_species.begin(); i != engimon::all_species.end() && randomNumber > 0; ++i)
	{
		randomNumber--;
		idx = i;
	}

	/*Pembuatan Engimon*/
	skill nullSkill;
	engimon potentialEngimon(get<0>(*idx), &universal_nullEngimon, &universal_nullEngimon, get<0>(*idx), randomLevel, 0);

	while(!this->isTileValid(potentialEngimon))
	{
		randomNumber = rand() %  species_count;
		srand(tile::random_seed);
		tile::random_seed++;

		randomLevel = rand() % 30 + 1;
		srand(tile::random_seed);
		tile::random_seed++;

		for (auto i = engimon::all_species.begin(); i != engimon::all_species.end() && randomNumber > 0; ++i)
		{
			randomNumber--;
			idx = i;
		}

		potentialEngimon = engimon(get<0>(*idx), &universal_nullEngimon, &universal_nullEngimon, get<0>(*idx), randomLevel, 0);
	}

	this->setEngimon(potentialEngimon);
	cout << "Spawn Success" << endl;
}

void tile::printTile()
{
	cout << this->symbol;
}

void tile::setEngimon(engimon &e)
{
	this->wild_engimon = e;

	if (e.isNull())
	{
		if (this->tile_type == "sea")
		{
			this->symbol = 'o';
		}
		else
		{
			this->symbol = '-';
		}
	}
	else if (e.getElmt1() == "Fire" && e.getElmt2() == "Electric")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'L';
		}
		else
		{
			this->symbol = 'l';
		}
		
	}
	else if (e.getElmt1() == "Water" && e.getElmt2() == "Ice")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'S';
		}
		else
		{
			this->symbol = 's';
		}
		
	}

	else if (e.getElmt1() == "Water" && e.getElmt2() == "Ground")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'N';
		}
		else
		{
			this->symbol = 'n';
		}
		
	}

	else if (e.getElmt1() == "Fire")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'F';
		}
		else
		{
			this->symbol = 'f';
		}
		
	}
	else if (e.getElmt1() == "Water")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'W';
		}
		else
		{
			this->symbol = 'w';
		}
		
	}
	else if (e.getElmt1() == "Electric")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'E';
		}
		else
		{
			this->symbol = 'e';
		}
	}

	else if (e.getElmt1() == "Ground")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'G';
		}
		else
		{
			this->symbol = 'g';
		}
	}

	else if (e.getElmt1() == "Ground")
	{
		if (e.getLevel() > HGIH_LEVEL_CAP)
		{
			this->symbol = 'G';
		}
		else
		{
			this->symbol = 'g';
		}
	}
}

engimon& tile::getEngimon()
{
	return this->wild_engimon;
}

void tile::setSymbol(char c)
{
	this->symbol = c;
}
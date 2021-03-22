#include <iostream>
#include <string>
#include <iterator> 
#include <vector>
#include "skill.hpp"
#include "engimon.hpp"
#include "player.hpp"
#include <set>
using namespace std;

int main()
{
    skill::InitializeSkillDatabase();
	engimon::IntializeDatabase();
    try
    {
        skill nullSkill;
        engimon nullEngimon;
        engimon Gab("Gab", &nullEngimon, &nullEngimon, "Magikarp", nullSkill, 4, 0);
        engimon Pulu("Pulu", &nullEngimon, &nullEngimon, "Vulpichu", nullSkill, 10, 50);
        player newPlayer;

        newPlayer.deleteActiveEngimon();
        newPlayer.deleteEngimonSelect();
        newPlayer.showEngimonDetails();

        newPlayer.showEngimonList();
    }
    catch (char const* e)
	{
		cout << e << endl;
	}
    return 0;
}
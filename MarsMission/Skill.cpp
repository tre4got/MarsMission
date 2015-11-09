#include "Skill.h"

Skill::Skill()
{
	type = SkillType(0);
	proficiency = 1;
}

Skill::Skill(int randomNumber)
{
	type = SkillType(randomNumber % 14);
	proficiency = (randomNumber % 100) + 1;
}

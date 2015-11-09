#include "Team.h"
#include <stdlib.h>
#include <time.h>    

Team::Team(std::vector<Person> canidateList)
{
	for (int i = 0; i < 100; ++i)
		people.push_back(canidateList[rand() % canidateList.size()]);
}

void Team::scoreTeam(Compatibility compatibility)
{
	score = 0;

	std::vector<int> skills;
	for (int i = 0; i < 19; ++i)
		skills.push_back(0);

	std::vector<int> personalityTypes;
	for (int i = 0; i < 16; ++i)
		personalityTypes.push_back(0);

	bool hasLeader = false;
	for (int i = 0; i < people.size(); ++i)
	{
		auto person = people[i];
		skills[person.skill.type] += person.skill.proficiency;
		personalityTypes[person.personalityType] += 1;
		if (person.personalityType == PersonalityType::ENTJ)
			hasLeader = true;
	}

	//Sum skills
	bool hasDoctor = false;
	bool hasPsychologist = false;
	bool hasJournalist = false;
	int agCount = 0;
	int cvCount = 0;
	int elCount = 0;
	int stCount = 0;
	for (int i = 0; i < 19; ++i)
	{
		switch (SkillType(i))
		{
		case SkillType::AgriculturalEngineer:
			agCount++;
			if (agCount > 5)
				score -= 1000;
			else
				score += (.5 * skills[i]);
			break;
		case SkillType::CivilEngineer:
			cvCount++;
			if (cvCount > 5)
				score -= 1000;
			else
				score += (.5 * skills[i]);
			break;
		case SkillType::Doctor:
			if (hasDoctor)
				score -= 1000;
			else
				score += (.75 * skills[i]);
			hasDoctor = true;
			break;
		case SkillType::ElectricalEngineer:
			elCount++;
			if (elCount > 5)
				score -= 1000;
			else
				score += (.5 * skills[i]);
			break;
		case SkillType::Psychologist:
			if (hasPsychologist)
				score += (.1 * skills[i]);
			else
				score += (.75 * skills[i]);

			hasPsychologist = true;
			break;
		case SkillType::StructuralEngineer:
			stCount++;
			if (stCount > 10)
				score -= 1000;
			else
				score += (.5 * skills[i]);
			break;
		case SkillType::Journalist:
			if (hasJournalist)
				score -= 2000;
			else
				score += (.25 * skills[i]);
			hasJournalist = true;
			break;
		default:
			score += (.25 * skills[i]);
		}
	}

	for (int i = 0; i < 16; ++i)
	{
		auto personalityCount = personalityTypes[i];
		auto bestWithList = compatibility.getBestWith(PersonalityType(i));
		auto worstWithList = compatibility.getWorstWith(PersonalityType(i));

		for (int k = 0; k < bestWithList.size(); ++k)
			score += (personalityCount * personalityTypes[bestWithList[k]]);
		for (int k = 0; k < worstWithList.size(); ++k)
			score -= (personalityCount * personalityTypes[worstWithList[k]] * 1.75);
	}

	if (!hasLeader)
		score -= 1000;
	if (!hasDoctor)
		score -= 1000;
	if (!hasPsychologist)
		score -= 1000;
}

void Team::reborn(Team dad, Team mom)
{
	people.clear();
	srand(time(NULL));
	for (int i = 0; i < dad.people.size(); ++i)
	{
		auto random = rand() % 2;
		if (random == 0)
			people.push_back(dad.people[i]);
		else
			people.push_back(mom.people[i]);
	}
}

void Team::replace(Person person, int index)
{
	people[index] = person;
}

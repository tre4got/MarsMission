#include "TeamBuilder.h"
#include <stdlib.h>
#include <time.h>  
#include <algorithm> 
#include <stdlib.h>
#include <time.h>   
#include <iostream>

TeamBuilder::TeamBuilder()
{
	srand(time(NULL));

	for (int i = 0; i < 1000; ++i)
		canidateList.push_back(Person(rand()));

	for (int i = 0; i < 50; ++i)
		teams.push_back(Team(canidateList));

	compatibility = Compatibility();

	reportTeams(true, 0);
}

std::vector<Team> TeamBuilder::createTeams(int iterations)
{
	for (int i = 0; i < iterations; ++i)
	{
		fitness();
		getBusy();
		mutate();
	}
	return teams;
}

void TeamBuilder::fitness()
{
	scoreTeams();
	deadIndecies.clear();
	purgeTheWeakAndTheHeretic(teams.size() * 0.6f, teams.size() * 0.2f);
}

void TeamBuilder::purgeTheWeakAndTheHeretic(int totalThatCanBePurged, int totalThatMustBePurged)
{
	sortTeams();
	int count = 0;
	while (deadIndecies.size() <= totalThatMustBePurged)
	{
		for (int i = 0; i < teams.size(); ++i)
		{
			if (deadIndecies.size() >= totalThatCanBePurged)
				break;

			if (teams[i].score < 0)
				deadIndecies.push_back(i);
			else if (teams[i].score < (1000 * count))
				deadIndecies.push_back(i);
		}

		count++;
	}
}

void TeamBuilder::getBusy()
{
	for (int i = 0; i < deadIndecies.size(); ++i)
	{
		int parentId1 = getIdOfRandomParent();
		int parentId2 = getIdOfRandomParent();
		while (parentId2 == parentId1)
			parentId2 = getIdOfRandomParent();

		teams[i].reborn(teams[parentId1], teams[parentId2]);
	}
}

void TeamBuilder::mutate()
{
	for (int i = 0; i < teams.size(); ++i)
	{
		for (int k = 0; k < 20; ++k)
		{
			int probablity = rand() % 100;
			if (probablity < 10)
			{
				int personListIndex = rand() % 100;
				int canidateListIndex = rand() % canidateList.size();
				teams[i].replace(canidateList[canidateListIndex], personListIndex);
			}
		}
	}
}

void TeamBuilder::reportTeams(bool isOriginal, int iterations)
{
	scoreTeams();
	sortTeams();
	int lowScore = teams[0].score;
	int highScore = teams[teams.size() - 1].score;
	int totalScore = 0;
	for (int k = 0; k < teams.size(); ++k)
		totalScore += teams[k].score;
	int average = totalScore / teams.size();

	if (isOriginal)
		std::cout << "Initial Teams:" << std::endl;
	else
		std::cout << "Iterations: " << iterations << std::endl;

	std::cout << "Lowest: " << lowScore << "  Highest: " << highScore << "  Average: " << average << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
}

void TeamBuilder::scoreTeams()
{
	for (int i = 0; i < teams.size(); ++i)
		teams[i].scoreTeam(compatibility);
}

void TeamBuilder::demo()
{
	for (int i = 0; i < 100000; ++i)
	{
		fitness();
		getBusy();
		mutate();
		reportTeams(false, i);
	}
}

int TeamBuilder::getIdOfRandomParent()
{
	while (true)
	{
		auto randomNumber = rand() % teams.size();
		bool isDead = false;
		for (int i = 0; i < deadIndecies.size(); ++i)
		{
			if (deadIndecies[i] == randomNumber)
			{
				isDead = true;
				break;
			}
		}

		if (!isDead)
		{
			return randomNumber;
		}
	}
}

void TeamBuilder::sortTeams()
{
	std::sort(teams.begin(), teams.end(), [](const Team& lhs, const Team& rhs)
	{
		return lhs.score < rhs.score;
	});
}

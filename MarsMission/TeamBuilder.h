#pragma once

#ifndef TEAMBUILDER_H
#define TEAMBUILDER_H

#include <vector>
#include "Team.h"
#include "Person.h"
#include "Compatibility.h"

class TeamBuilder
{
public:
	TeamBuilder();
	std::vector<Team> createTeams(int iterations);
	void demo();
private:
	///<summary>Score all the teams</summary>
	void fitness();

	///<summary>Marks bad teams. Will keep at least 40% of the population, and eliminate at least 20% of the population. As count increases so will the criteria of what a good team is.</summary>
	void purgeTheWeakAndTheHeretic(int totalThatCanBePurged, int totalThatMustBePurged);

	///<summary>The remaining members of the population will be randomly selected to reproduce and refill the population</summary>
	void getBusy();

	///<summary>Each team will get a small chance to mutate (randomly replacing some members of the team with a random person)</summary>
	void mutate();

	void reportTeams(bool isOriginal, int iterations);

	void scoreTeams();

	int getIdOfRandomParent();
	void sortTeams();
	std::vector<Team> teams;
	std::vector<Team> topTeams;
	std::vector<Person> canidateList;
	std::vector<int> deadIndecies;
	Compatibility compatibility;
};

#endif
#pragma once

#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "Person.h"
#include "Compatibility.h"

class Team
{
public:
	///<summary>Creates a team of random people</summary>
	Team(std::vector<Person> canidateList);

	///<summary>Scores the team</summary>
	void scoreTeam(Compatibility compatibility);

	///<summary>Recreates this team as an off spring of two parent teams</summary>
	void reborn(Team dad, Team mom);

	///<summary>Replace the person at the given index with the given person</summary>
	void replace(Person person, int index);

	int score;
private:
	std::vector<Person> people;
};

#endif
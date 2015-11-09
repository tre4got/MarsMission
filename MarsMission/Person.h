#pragma once

#ifndef PERSON_H
#define PERSON_H

#include "Skill.h"
#include "PersonalityType.h"

class Person
{
public:
	/// <summary>Creates a new person with a random skill and personalityType</summary>
	Person(int randomNumber);
	Skill skill;
	PersonalityType personalityType;
};

#endif
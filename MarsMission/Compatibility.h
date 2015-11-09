#pragma once

#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include <vector>
#include "PersonalityType.h"

class Compatibility
{
public:
	Compatibility();
	std::vector<PersonalityType> getBestWith(PersonalityType type);
	std::vector<PersonalityType> getWorstWith(PersonalityType type);
private:
	std::vector<std::vector<PersonalityType>> bestWith;
	std::vector<std::vector<PersonalityType>> worstWith;
};

#endif 
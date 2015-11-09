#include "Person.h"

Person::Person(int randomNumber)
{
	skill = Skill(randomNumber);
	personalityType = PersonalityType(randomNumber % 16);
}

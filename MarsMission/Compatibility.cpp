#include "Compatibility.h"

Compatibility::Compatibility()
{
	//ISTJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ENTJ, PersonalityType::ESTJ, PersonalityType::ESFJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::INFP, PersonalityType::ISFP, PersonalityType::INTP});

	//ISTP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ESTP, PersonalityType::ESFP, PersonalityType::ENTP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::INTJ, PersonalityType::INFJ, PersonalityType::ISFJ});

	//ISFJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ENFJ, PersonalityType::ESFJ, PersonalityType::ESTJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::INTP, PersonalityType::ISTP, PersonalityType::INFP});

	//ISFP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ESTP, PersonalityType::ESFP, PersonalityType::ENFP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::INTJ, PersonalityType::INFJ, PersonalityType::ISTJ});

	//INFJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ENFJ, PersonalityType::ESFJ, PersonalityType::ENTJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::INTP, PersonalityType::ISTP, PersonalityType::ISFP});

	//INFP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ENFP, PersonalityType::ENTP, PersonalityType::ESFP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ISTJ, PersonalityType::ISFJ, PersonalityType::INTJ});

	//INTJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ENTJ, PersonalityType::ESTJ, PersonalityType::ENFJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ISFP, PersonalityType::INFP, PersonalityType::ISTP});

	//INTP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ENTP, PersonalityType::ENFP, PersonalityType::ESTP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ISTJ, PersonalityType::ISFJ, PersonalityType::INFJ});

	//ESTP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ISTP, PersonalityType::INTP, PersonalityType::ISFP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ESFJ, PersonalityType::ENFJ, PersonalityType::ENTJ});

	//ESTJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ISTJ, PersonalityType::ISFJ, PersonalityType::INTJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ENTP, PersonalityType::ENFP, PersonalityType::ESFP});

	//ESFP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ISFP, PersonalityType::INFP, PersonalityType::ISTP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ESTJ, PersonalityType::ENTJ, PersonalityType::ENFJ});

	//ESFJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::ISTJ, PersonalityType::ISFJ, PersonalityType::INFJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ENTP, PersonalityType::ENFP, PersonalityType::ESTP});

	//ENFP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::INFP, PersonalityType::ISFP, PersonalityType::INTP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ESTJ, PersonalityType::ENTJ, PersonalityType::ESFJ});

	//ENFJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::INFJ, PersonalityType::INTJ, PersonalityType::ISFJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ESTP, PersonalityType::ESFP, PersonalityType::ENTP});

	//ENTP
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::INTP, PersonalityType::ISTP, PersonalityType::INFP});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ESFJ, PersonalityType::ENFJ, PersonalityType::ESTJ});

	//ENTJ
	bestWith.push_back(std::vector<PersonalityType>{PersonalityType::INTJ, PersonalityType::INFJ, PersonalityType::ISTJ});
	worstWith.push_back(std::vector<PersonalityType>{PersonalityType::ESTP, PersonalityType::ESFP, PersonalityType::ENFP});
}

std::vector<PersonalityType> Compatibility::getBestWith(PersonalityType type)
{
	return bestWith[type];
}

std::vector<PersonalityType> Compatibility::getWorstWith(PersonalityType type)
{
	return worstWith[type];
}

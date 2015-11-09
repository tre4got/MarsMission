#pragma once

#ifndef SKILL_H
#define SKILL_H

enum SkillType
{
	AeroSpaceEngineer,
	AgriculturalEngineer,
	Biologist,
	BioMedicalEngineer,
	ChemicalEngineer,
	CivilEngineer,
	Doctor,
	ElectricalEngineer,
	EnvironmentalEngineer,
	Geologist,
	Geneticist,
	Journalist,
	Mechanic,
	MechanicalEngineer,
	Pilot,
	Physicist,
	Psychologist,
	SoftwareEngineer,
	StructuralEngineer,
};

class Skill
{
public:
	Skill();
	/// <summary>Creates a new Skill with a randomly selected SkillType and proficiency</summary>
	Skill(int randomNumber);
	SkillType type;
	int proficiency;
};

#endif
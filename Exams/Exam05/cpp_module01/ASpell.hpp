#pragma once

#include <iostream>

class ATarget;

class ASpell {
protected:
	std::string name;
	std::string effects;

public:
	ASpell(std::string const &name, std::string const &effects);
	const std::string &getName() const;
	const std::string &getEffects() const;

	virtual ASpell* clone() const = 0;

	virtual ~ASpell();

	void launch(const ATarget& target) const;
};
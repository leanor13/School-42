#pragma once

#include <iostream>

class ATarget;

class ASpell {
protected:
	std::string _name;
	std::string _effects;

public:
	ASpell(std::string const &name, std::string const &effects);
	virtual ~ASpell();
	virtual ASpell* clone() const = 0;

	const std::string &getName() const;
	const std::string &getEffects() const;

	void launch(const ATarget& target) const;
};
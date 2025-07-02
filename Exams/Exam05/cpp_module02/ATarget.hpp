#pragma once

#include <iostream>

class ASpell;

class ATarget {
protected:
	std::string _type;

public:
	ATarget(std::string const &type);
	virtual ~ATarget();
	virtual ATarget* clone() const = 0;

	const std::string &getType() const;

	void getHitBySpell(ASpell const *spell) const;
};
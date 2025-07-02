#pragma once

#include <iostream>

class ASpell;

class ATarget {

protected:
	std::string type;

public:
	ATarget(std::string const &type);
	const std::string &getType() const;

	virtual ~ATarget();
	virtual ATarget* clone() const = 0;

	void getHitBySpell(const ASpell& spell) const;

};
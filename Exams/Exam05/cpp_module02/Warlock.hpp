#pragma once

#include <iostream>
#include <map>

#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

class Warlock {
private:
	std::string _name;
	std::string _title;

	SpellBook _spellBook;

public:
	Warlock(std::string const &name, std::string const &title);
	~Warlock();

	const std::string &getName() const;
	const std::string &getTitle() const;
	void setTitle(std::string const &title);
	void introduce() const;

	void learnSpell(ASpell* spell_ptr);
	void forgetSpell(std::string spell_str);
	void launchSpell(std::string spell_str, const ATarget& target);
};
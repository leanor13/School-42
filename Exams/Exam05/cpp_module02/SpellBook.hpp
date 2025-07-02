#pragma once

#include <iostream>
#include <map>

class ASpell;

class SpellBook {
private:
	std::map<std::string, ASpell *> _spellBook;

public:

	SpellBook();
	~SpellBook();

	void learnSpell(ASpell* spell_ptr);
	void forgetSpell(std::string const &spell_str);
	ASpell* createSpell(std::string const &spell_str);
};
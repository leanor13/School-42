#include "SpellBook.hpp"
#include "ASpell.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() {
	_spellBook.clear();
}

void SpellBook::learnSpell(ASpell* spell_ptr) {
	if (!spell_ptr) {return;}

	std::map<std::string, ASpell *>::iterator it=_spellBook.find(spell_ptr->getName());
	if (it == _spellBook.end()) {
		_spellBook[spell_ptr->getName()] = spell_ptr->clone();
	}
}

void SpellBook::forgetSpell(std::string const &spell_str) {
	std::map<std::string, ASpell *>::iterator it=_spellBook.find(spell_str);
	if (it != _spellBook.end()) {
		delete _spellBook[spell_str];
	}
}

ASpell* SpellBook::createSpell(std::string const &spell_str) {
	std::map<std::string, ASpell *>::iterator it=_spellBook.find(spell_str);
	if (it != _spellBook.end()) {
		return (_spellBook[spell_str]->clone());
	}
	return nullptr;

}


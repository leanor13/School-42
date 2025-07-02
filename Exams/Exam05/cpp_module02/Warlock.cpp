#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title) : _name(name), _title(title) {
	std::cout << name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock() {
	std::cout << _name << ": My job here is done!" << std::endl;
}

const std::string &Warlock::getName() const {
	return _name;
}

const std::string &Warlock::getTitle() const {
	return _title;
}

void Warlock::setTitle(std::string const &title) {
	_title = title;
}

void Warlock::introduce() const {
	std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell* spell_ptr) {
	if (spell_ptr) {
		_spellBook.learnSpell(spell_ptr);
	}
}

void Warlock::forgetSpell(std::string spell_str) {
	_spellBook.forgetSpell(spell_str);
}

void Warlock::launchSpell(std::string spell_str, const ATarget& target) {
	ASpell* spell=_spellBook.createSpell(spell_str);
	spell->launch(target);
	delete spell;
}
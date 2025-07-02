#include "ATarget.hpp"
#include "ASpell.hpp"

ASpell::ASpell(std::string const &name, std::string const &effects) : _name(name), _effects(effects) {}

const std::string &ASpell::getName() const {
	return _name;
}

const std::string &ASpell::getEffects() const {
	return _effects;
}

void ASpell::launch(const ATarget& target) const {
		target.getHitBySpell(this);
	}

ASpell::~ASpell() {}
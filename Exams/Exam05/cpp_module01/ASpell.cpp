#include "ASpell.hpp"
#include "ATarget.hpp"

ASpell::ASpell(std::string const &name, std::string const &effects) : 
	name(name), effects(effects) {

	}

const std::string &ASpell::getName() const {
	return name;
}

const std::string &ASpell::getEffects() const {
	return effects;
}

void ASpell::launch(const ATarget& target) const {
	target.getHitBySpell(*this);
}

ASpell::~ASpell() {}
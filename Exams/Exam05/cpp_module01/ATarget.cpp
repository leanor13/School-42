#include "ATarget.hpp"
#include "ASpell.hpp"

ATarget::ATarget(std::string const &type) : type(type) {}

const std::string &ATarget::getType() const {
	return type;
}

ATarget::~ATarget() {}

void ATarget::getHitBySpell(const ASpell& spell) const {
	std::cout << type << " has been " << spell.getEffects() << "!" << std::endl;
}
#include "ATarget.hpp"
#include "ASpell.hpp"

ATarget::ATarget(std::string const &type) : _type(type) {}

const std::string &ATarget::getType() const {
	return _type;
}

void ATarget::getHitBySpell(ASpell const *spell) const {
	std::cout << _type << " has been " << spell->getEffects() << "!" << std::endl;
}

ATarget::~ATarget() {}

#include "TargetGenerator.hpp"
#include "ATarget.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() {
	_targetGenerator.clear();
}

void TargetGenerator::learnTargetType(ATarget* target) {
	if (!target) return;
	if (_targetGenerator.count(target->getType()) == 0) {
		_targetGenerator[target->getType()] = target->clone();
	}
}

void TargetGenerator::forgetTargetType(std::string const &type) {
	if (_targetGenerator.count(type) != 0) {
		delete _targetGenerator[type];
		_targetGenerator.erase(type);
	}
}

ATarget* TargetGenerator::createTarget(std::string const &type) {
	if (_targetGenerator.count(type) != 0) {
		return _targetGenerator[type]->clone();
	}
	return nullptr;
}
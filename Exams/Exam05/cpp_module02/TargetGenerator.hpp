#pragma once

#include <iostream>
#include <map>

class ATarget;

class TargetGenerator {

private:
	std::map<std::string, ATarget *> _targetGenerator;

public:
	TargetGenerator();
	~TargetGenerator();

	void learnTargetType(ATarget* target);
	void forgetTargetType(std::string const &type);
	ATarget* createTarget(std::string const &type);
};
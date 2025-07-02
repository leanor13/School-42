#pragma once

#include <iostream>
#include <map>

class ASpell;
class ATarget;

class Warlock {
private:
  std::string name;
  std::string title;

  std::map<std::string, ASpell*> spellBook;

public:
  Warlock(const std::string &name, const std::string &title);
  ~Warlock();

  const std::string& getName() const;
  const std::string& getTitle() const;
  void setTitle(const std::string &title);
  void introduce() const;

  void learnSpell(ASpell* const spell);
  void forgetSpell(std::string spell);
  void launchSpell(std::string spell, const ATarget& target);
};

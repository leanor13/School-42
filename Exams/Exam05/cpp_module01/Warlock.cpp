#include "Warlock.hpp"
#include "ASpell.hpp"

#include <iostream>

Warlock::Warlock(const std::string &name, const std::string &title)
    : name(name),
      title(title) {
        std::cout << name << ": This looks like another boring day." << std::endl;
      }

const std::string &Warlock::getName() const {
  return this->name;
}

const std::string &Warlock::getTitle() const {
  return this->title;
}

void Warlock::setTitle(const std::string &title) {
  this->title = title;
}

void Warlock::introduce() const {
  std::cout << name << ": I am " << name << ", " << title << "!" << std::endl;
}

Warlock::~Warlock() {
  std::cout << name << ": My job here is done!" << std::endl;
}

void Warlock::learnSpell(ASpell* const spell) {
  if (spell) {
    std::map<std::string, ASpell*>::iterator it = spellBook.find(spell->getName());
    if (it == spellBook.end())
      spellBook[spell->getName()] = spell->clone();
  }
}

void Warlock::launchSpell(std::string spell, const ATarget& target) {
  std::map<std::string, ASpell *>::iterator it = spellBook.find(spell);
  if (it != spellBook.end()) {
    spellBook[spell]->launch(target);
  }
}

void Warlock::forgetSpell(std::string spell) {
  std::map<std::string, ASpell *>::iterator it = spellBook.find(spell);
  if (it != spellBook.end()) {
    delete it->second;
    spellBook.erase(spell);
  }
}
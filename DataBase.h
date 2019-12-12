#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <vector>
#include <string>
#include "Rules.h"
#include <stack>
#include "Predicate.h"
#include "Relations.h"

class DataBase {
public:
  DataBase() {}
  std::vector<Relation*> getRelations() { return myRelations; }
  void addSchemes(std::vector<Predicate*> mySchemes);
  void addFacts(std::vector<Predicate*> myFacts);
  std::string addRules(std::vector<Rule*> myRules);
  std::string printDB();

private:
  std::vector<Relation*> myRelations;

};

#endif //DATA_BASE_H

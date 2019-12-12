#ifndef RELATION_H
#define RELATION_H

#include <vector>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"
#include <map>
#include <iostream>
#include <utility>

class Relation {
public:
    Relation() {}
    Scheme getScheme() { return myScheme; }
    std::string getName() { return myScheme.getName(); }
    std::vector<std::string*> *getAttributes() { return myScheme.getAttributes(); }
    void addAttribute(std::string* newAttribute) { myScheme.addAttribute(newAttribute); }
    std::string *getAttributesAt(int i) { return myScheme.getAttributesAt(i); }
    void setScheme(std::string newName, std::vector<std::string*> *newAttributes);
    void setScheme(Scheme newScheme) { myScheme = newScheme; }
    void setTuple(std::set<Tuple> newTuple) { myTuples = newTuple; }
    void setTuple(std::vector<std::string*> *tupData);
    void addTuple(Tuple newTuple);
    std::set<Tuple> getTuple() { return myTuples; }
    Tuple getTupleAt(unsigned int i);

    Relation* select(std::string selectThis, std::string thisCol);
    Relation* selectMatching(std::string opOne, std::string opTwo);
    Relation* project(std::map<unsigned int,std::string> firstTimer);
    Relation* project(std::vector<std::pair<unsigned int, std::string>>firstTimer);
    Relation* rename(std::map<unsigned int,std::string> firstTimer);
    Relation* rename(std::vector<std::pair<unsigned int, std::string>> firstTimer);
    Relation* join(Relation *firstRel, Relation *secondRel);
    Relation* unionize(Relation firstRel, Relation secondRel);
    std::string toString();

private:
    Scheme myScheme;
    std::set<Tuple> myTuples;

};

#endif //RELATION_H

/*
bool isDup = false;
for(unsigned int i = 0; i < myTuples.size(); ++i)
{

  if (*newTup == *(myTuples.at(i)))
  {
    isDup = true;
  }
}
if (!isDup)
{
  bool inserted = false;
  for(unsigned int i = 0; i < myTuples.size(); ++i)
  {
    if(*(myTuples.at(i)) < *newTup){}
    else
    {
      inserted = true;
      myTuples.insert(myTuples.begin() + i, newTup);
      break;
    }
  }

  if (!inserted)
  {
    myTuples.push_back(newTup);
  }
}
else { delete newTup; }
*/

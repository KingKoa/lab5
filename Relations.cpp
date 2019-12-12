#include "Relations.h"
/*
Relation::Relation(const Relation &copyCat)
{
  this->addScheme(copyCat.getScheme());
  std::set<Tuple> otherTups = copyCat.getTuple();

  std::set<Tuple>::iterator it = otherTups.begin();

  while (it != otherTups.end())
  {
    this->addTuple(*it);
    it++;
  }

}
*/
void Relation::setScheme(std::string newName, std::vector<std::string*> *newAttributes)
{
  myScheme.setName(newName);
  myScheme.setAttributes(newAttributes);
}

void Relation::setTuple(std::vector<std::string*> *tupData)
{
  Tuple newTup;
  for (unsigned int i = 0; i < tupData->size(); ++i)
  {
    newTup.push_back(*(tupData->at(i)));
  }

  if(myTuples.insert(newTup).second)
  {
    myTuples.insert(newTup);
  }
}

void Relation::addTuple(Tuple newTuple)
{
  if(myTuples.insert(newTuple).second)
  {
    myTuples.insert(newTuple);
  }
}

Tuple Relation::getTupleAt(unsigned int i)
{
    std::set<Tuple>::iterator it = myTuples.begin();
    for(unsigned int j = 0; j < i; ++j) {
        ++it;
    }

    return *it;
}


Relation* Relation::select(std::string selectThis, std::string thisCol)
{
  unsigned int i;
  Relation* newRelation = new Relation();
  newRelation->setScheme(myScheme);

  for (i = 0; i < myScheme.getAttributes()->size(); ++i)
  {
    if (thisCol == *(myScheme.getAttributes()->at(i))) { break; }
  }

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if (selectThis == (*it).at(i))
    {
      newRelation->addTuple(*it);
    }

    it++;
  }

  return newRelation;
}

Relation* Relation::selectMatching(std::string opOne, std::string opTwo)
{
  unsigned int i;
  unsigned int j;
  Relation* newRelation = new Relation();
  newRelation->setScheme(myScheme);

  for (i = 0; i < myScheme.getAttributes()->size(); ++i)
  {
    if (opOne == *(myScheme.getAttributes()->at(i))) { break; }
  }

  for (j = 0; j < myScheme.getAttributes()->size(); ++j)
  {
    if (opTwo == *(myScheme.getAttributes()->at(j))) { break; }
  }

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if ((*it).at(j) == (*it).at(i))
    {
      newRelation->addTuple(*it);
    }

    it++;
  }

  return newRelation;
}

Relation* Relation::project(std::map<unsigned int,std::string> firstTimer)
{
    unsigned int i = 0;
    Relation* newRelation = new Relation();
    std::map<unsigned int,std::string>::iterator mapIt;


    std::set<Tuple>::iterator it = myTuples.begin();
    while (it != myTuples.end())
    {
        Tuple myTuple;

        for(i = 0; i < it->size(); ++i)
        {
            for (mapIt = firstTimer.begin(); mapIt != firstTimer.end(); ++mapIt)
            {
                if(i == mapIt->first)
                {   // string's value
                    myTuple.push_back(it->at(i));
                }
            }
        }

        newRelation->addTuple(myTuple);
        it++;
    }

    return newRelation;
}

Relation* Relation::project(std::vector<std::pair<unsigned int, std::string>>firstTimer) {
    unsigned int i = 0;
    Relation *newRelation = new Relation();
    //std::map<unsigned int, std::string>::iterator mapIt;


    std::set<Tuple>::iterator it = myTuples.begin();
    while (it != myTuples.end()) {
        Tuple myTuple;


        for (unsigned int j = 0; j < firstTimer.size(); ++j) {
            for (i = 0; i < it->size(); ++i) {
                if (i == firstTimer.at(j).first) {   // string's value
                    myTuple.push_back(it->at(i));
                }
            }
        }

        newRelation->addTuple(myTuple);
        it++;
    }

    return newRelation;
}

Relation* Relation::rename(std::map<unsigned int,std::string> firstTimer) {
    //unsigned int i;
    Relation *newRelation = new Relation();
    std::map<unsigned int, std::string>::iterator mapIt;

    for (mapIt = firstTimer.begin(); mapIt != firstTimer.end(); ++mapIt) {
        newRelation->myScheme.addAttribute(new std::string(mapIt->second));
    }

    newRelation->setTuple(myTuples);

    return newRelation;
}

Relation* Relation::rename(std::vector<std::pair<unsigned int, std::string>> firstTimer) {
    unsigned int i;
    Relation *newRelation = new Relation();
    //std::map<unsigned int, std::string>::iterator mapIt;

    for(i = 0; i < firstTimer.size(); ++i) {
        newRelation->myScheme.addAttribute(new std::string(firstTimer.at(i).second));
    }

    newRelation->setTuple(myTuples);

    return newRelation;
}

Relation* Relation::join(Relation *firstRel, Relation *secondRel) {
    Relation* newRelation = new Relation();
    //Catch Duplicate Attribute Positions
    std::vector<std::pair<unsigned int, unsigned int>*> dupAttribute;
    // Combine schemes
    newRelation->setScheme(firstRel->getScheme());

    bool isDup = false;
    unsigned int k;
    std::vector<std::string*> *schemeAttributes = secondRel->getAttributes();

    for(unsigned int i = 0; i < schemeAttributes->size(); ++i) {
        isDup = false;

        for(k = 0; k < newRelation->getAttributes()->size(); ++k) {
            if(*(newRelation->getAttributes()->at(k)) == *(schemeAttributes->at(i))) {
                isDup = true;
                break;
            }
        }

        if(!isDup) {
            newRelation->addAttribute(schemeAttributes->at(i));
        }
        else {
            dupAttribute.push_back(new std::pair<unsigned int, unsigned int>(k, i));
        }
    }
    // Go through every pair of tuples
        //See if you can combine the tuples
            //Does every column that's supposed to match match?
        //If tuples can be combined combine them.

    bool isJoinable = true;
    bool dontAdd = false;

    for (unsigned int i = 0; i < firstRel->getTuple().size(); ++i) {

        for (unsigned int j = 0; j < secondRel->getTuple().size(); ++j) {
            isJoinable = true;

            for(unsigned int m = 0; m < dupAttribute.size(); ++m) {
                if(firstRel->getTupleAt(i).at(dupAttribute.at(m)->first) !=
                    secondRel->getTupleAt(j).at(dupAttribute.at(m)->second)) {
                    isJoinable = false;
                }
            }

            if(isJoinable) {
                Tuple joinedTup;

                for(unsigned int n = 0; n < firstRel->getTupleAt(i).size(); ++n) {
                    joinedTup.push_back(firstRel->getTupleAt(i).at(n));
                }
                for(unsigned int p = 0; p < secondRel->getTupleAt(j).size(); ++p) {
                    dontAdd = false;

                    for(unsigned int z = 0; z < dupAttribute.size(); ++z) {
                        if(p == dupAttribute.at(z)->second) { dontAdd = true; }
                    }

                    if(!dontAdd) {
                        joinedTup.push_back(secondRel->getTupleAt(j).at(p));
                    }
                }

                newRelation->addTuple(joinedTup);
            }
        }
    }
    //bool isJoinable(){}
    //Scheme combineSchemes(){}
    //Tuple combineTuples(){}


    return newRelation;
}

Relation* Relation::unionize(Relation firstRel, Relation secondRel)
{
    Relation* newRelation = new Relation();
    /*
     * Be consistent about which Relation is which
     * The one you are inside is the database relation
     * The one you pass in as an argument is the result from the rule evaluation
     * When adding a tuple from the rule evaluation to the database, check if it already existed → if(mySet.insert(myTuple).second)
     * If it already existed, do nothing
     * If it is a new tuple, print out and add to DB relation
     */

    newRelation->setScheme(firstRel.getScheme());
    newRelation->setTuple(firstRel.getTuple());
    for(unsigned int i = 0; i < secondRel.getTuple().size(); ++i)
    {
        newRelation->addTuple(secondRel.getTupleAt(i));
    }

    return newRelation;
}

std::string Relation::toString()
{
    std::string returnString = "";
//  returnString += "Relation:\n";
//  returnString += "  ";
//  returnString += myScheme.toString();
//  returnString += "\n";

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if(myScheme.getAttributes()->size() != 0) { returnString += "  "; }

    for (unsigned int i = 0; i < myScheme.getAttributes()->size(); ++i)
    {
      returnString += *(myScheme.getAttributesAt(i));
      returnString += "=";
      returnString += (*it).at(i);

      if (i+1 != myScheme.getAttributes()->size())
      {
        returnString += ", ";
      }
    }

    it++;
    if(myScheme.getAttributes()->size() != 0) { returnString += "\n"; }
    //if (it != myTuples.end()) { returnString += "\n"; }
  }

  //returnString += "\n";
  return returnString;
}

/*
std::vector<std::string*> *myAttributes = myScheme.getAttributes();
for (unsigned int i = 0; i < parmList->size(); ++i)
{
  for (unsigned int j = 0; j < myAttributes->size(); ++j)
  {
    if (*(parmList->at(i)) == *(myAttributes->at(j))) break;
  }
}

int searching;

if ((i - 1) < 0) { searching = 1; }
else { searching = 0; }
*/

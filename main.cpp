#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Token.h"
#include "DataBase.h"
#include "Interpreter.h"

void sortDomain(std::vector<std::string*> *myDomain)
{
  unsigned int i, j;
  unsigned int size = myDomain->size();
  std::string t;
  std::vector<unsigned int> deleteThese;

  for(i=1; i<size; i++)
  {
    for(j=1; j<size; j++)
    {
      if(*myDomain->at(j-1) >= *myDomain->at(j))
      {
        t = *myDomain->at(j-1);
        *myDomain->at(j-1) = *myDomain->at(j);
        *myDomain->at(j) = t;
      }
    }
  }

  for (i = 1; i < size; ++i)
  {
    if(*myDomain->at(i-1) == *myDomain->at(i))
    {
      deleteThese.push_back(i);
    }
  }
  for (int k = (deleteThese.size() - 1); k >= 0; k--)
  {
    delete myDomain->at(deleteThese[k]);
    myDomain->erase(myDomain->begin() + deleteThese[k]);
  }
}


int main(int argc, char* argv[]) {
    std::string fileName = argv[1];
    std::vector<Token*> *myTokens;
    std::vector<Token*> *parseTokens = new std::vector<Token*>;

    Scanner myScanner(fileName);

    myTokens = myScanner.tokenize();

    for (unsigned int i = 0; i < myTokens->size(); i++)
    {
        if (myTokens->at(i) != nullptr && myTokens->at(i)->getTokenType() != COMMENT)
        {
            parseTokens->push_back(myTokens->at(i));
        }
    }

    Parser myParser(parseTokens);
    DatalogProgram* myProgram = myParser.getProg();
    //Add Schemes and Facts
    Interpreter myInterpreter(myProgram->getSchemes(), myProgram->getFacts());
    //Add Rules
    std::cout << myInterpreter.evalRules(myProgram->getRules());
    //Answer QUERIES
    std::cout << "Query Evaluation" << std::endl;
    std::cout << myInterpreter.checkQueries(myProgram->getQueries());

    delete myProgram;

    for (unsigned int i = 0; i < myTokens->size(); i++)
    {
        delete myTokens->at(i);
    }

    delete myTokens;
    delete parseTokens;

    return 0;
}

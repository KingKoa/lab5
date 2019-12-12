//
// Created by Kekoapo'aono Montalbo on 10/6/19.
//

#include "Parser.h"

bool Parser::checkProgram()
{
    try {
        checkDataLogProg();
    } catch (Token* thrownToken)
    {
        badToken = thrownToken;
        return false;
    }

    return true;
}

void Parser::checkDataLogProg()
{
    //SCHEMES
    if (myTokens->at(curPos)->getTokenType() == SCHEMES) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //scheme
    scheme();

    //schemeList
    schemeList();

    //FACTS
    if (myTokens->at(curPos)->getTokenType() == FACTS) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //factList
    factList();

    //RULES
    if (myTokens->at(curPos)->getTokenType() == RULES) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //ruleList
    ruleList();

    //QUERIES
    if (myTokens->at(curPos)->getTokenType() == QUERIES) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //queryList
    queryList();

    //EOF
    if (myTokens->at(curPos)->getTokenType() == EndOfFile) {}
    else { throw myTokens->at(curPos); }
}

void Parser::schemeList()
{
    if (myTokens->at(curPos)->getTokenType() != FACTS)
    {
        scheme();
        if (myTokens->at(curPos)->getTokenType() != FACTS) { schemeList(); }
    }
}

void Parser::factList()
{
    if (myTokens->at(curPos)->getTokenType() != RULES)
    {
        fact();
        if (myTokens->at(curPos)->getTokenType() != RULES) { factList(); }
    }
}

void Parser::ruleList()
{
    if (myTokens->at(curPos)->getTokenType() != QUERIES)
    {
        rule();
        if (myTokens->at(curPos)->getTokenType() != QUERIES) { ruleList(); }
    }
}

void Parser::queryList()
{
    if (myTokens->at(curPos)->getTokenType() != EndOfFile)
    {
        query();
        if (myTokens->at(curPos)->getTokenType() != EndOfFile) { queryList(); }
    }
}

void Parser::scheme()
{
    std::vector<std::string*> *thisScheme = new std::vector<std::string*>;
    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
        thisScheme->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
        curPos++;
    }
    else { throw myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
        {
            for (unsigned int i = 0; i < thisScheme->size(); ++i)
            {
                delete thisScheme->at(i);
            }

            delete thisScheme;

            throw myTokens->at(curPos);
        }

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
      thisScheme->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else
        {
            for (unsigned int i = 0; i < thisScheme->size(); ++i)
            {
                delete thisScheme->at(i);
            }

            delete thisScheme;

            throw myTokens->at(curPos);
        }

    //idList
    idList(thisScheme);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisScheme->size(); ++i)
      {
          delete thisScheme->at(i);
      }

      delete thisScheme;

      throw myTokens->at(curPos);
    }

    //Create & Add scheme to DataLogProgram
    myProgram->addScheme(thisScheme);
    delete thisScheme;
}

void Parser::fact()
{
    std::vector<std::string*> *thisFact = new std::vector<std::string*>;

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
      thisFact->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else { throw myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisFact->size(); ++i)
      {
          delete thisFact->at(i);
      }

      delete thisFact;

      throw myTokens->at(curPos);
    }

    //STRING
    if (myTokens->at(curPos)->getTokenType() == STRING)
    {
      std::string* newString = new std::string(myTokens->at(curPos)->getTokenString());
      myDomain.push_back(newString);
      thisFact->push_back(newString);
      curPos++;
    }

    else
    {
      for (unsigned int i = 0; i < thisFact->size(); ++i)
      {
          delete thisFact->at(i);
      }

      delete thisFact;
      throw myTokens->at(curPos);
    }
    //stringList
    stringList(thisFact);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisFact->size(); ++i)
      {
          delete thisFact->at(i);
      }

      delete thisFact;

      throw myTokens->at(curPos);
    }

    //PERIOD
    if (myTokens->at(curPos)->getTokenType() == PERIOD) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisFact->size(); ++i)
      {
          delete thisFact->at(i);
      }

      delete thisFact;
      throw myTokens->at(curPos);
     }

    //Create & Add scheme to DataLogProgram
    myProgram->addFacts(thisFact);
    delete thisFact;
}

void Parser::rule()
{
    Rule *myRule = new Rule();
    //headPredicate
    headPredicate(myRule);

    //COLON_DASH
    if (myTokens->at(curPos)->getTokenType() == COLON_DASH) { curPos++; }
    else
    {
      delete myRule;
      throw myTokens->at(curPos);
    }

    //predicate
    predicate(myRule);

    //predicateList
    predicateList(myRule);

    //PERIOD
    if (myTokens->at(curPos)->getTokenType() == PERIOD) { curPos++; }
    else if (myTokens->at(curPos)->getTokenType() != PERIOD)
    {
      delete myRule;
      throw myTokens->at(curPos);
    }
    myProgram->addRule(myRule);
}

void Parser::query()
{
    //predicate
    predicate();
    // Q_MARK
    if (myTokens->at(curPos)->getTokenType() == Q_MARK) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::headPredicate()
{
    auto *thisRule = new std::vector<std::string*>();

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else { throw myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else { throw myTokens->at(curPos); }

    //idList
    idList(thisRule);

    //Delete my Rule pointers
    for (unsigned int i = 0; i < thisRule->size(); ++i)
    {
        delete thisRule->at(i);
    }

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::headPredicate(Rule* myRule)
{

    auto *thisRule = new std::vector<std::string*>();

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
      thisRule->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else
    {
      for (unsigned int i = 0; i < thisRule->size(); ++i)
      {
          delete thisRule->at(i);
      }

      delete thisRule;
      delete myRule;
      throw myTokens->at(curPos);
    }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisRule->size(); ++i)
      {
          delete thisRule->at(i);
      }

      delete thisRule;
      delete myRule;

      throw myTokens->at(curPos);
    }

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) \
    {
      thisRule->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else
    {
      for (unsigned int i = 0; i < thisRule->size(); ++i)
      {
          delete thisRule->at(i);
      }

      delete thisRule;
      delete myRule;

      throw myTokens->at(curPos);
    }

    //idList
    idList(thisRule);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisRule->size(); ++i)
      {
          delete thisRule->at(i);
      }

      delete thisRule;
      delete myRule;

      throw myTokens->at(curPos);
    }

    //Create my Rules name
    Predicate *newName = new Predicate(thisRule);
    myRule->addRulesName(newName);
}

void Parser::predicate()
{
    std::vector<std::string*> *thisQuery = new std::vector<std::string*>;

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
      thisQuery->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else
        {
            for (unsigned int i = 0; i < thisQuery->size(); ++i)
            {
                delete thisQuery->at(i);
            }

            throw *myTokens->at(curPos);
        }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
        {
            for (unsigned int i = 0; i < thisQuery->size(); ++i)
            {
                delete thisQuery->at(i);
            }

            throw myTokens->at(curPos);
        }

    //parameter
    parameter(thisQuery);

    //parameterList
    parameterList(thisQuery);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else
        {
            for (unsigned int i = 0; i < thisQuery->size(); ++i)
            {
                delete thisQuery->at(i);
            }

            throw myTokens->at(curPos);
        }

    myProgram->addQuery(thisQuery);
    delete thisQuery;
}

void Parser::predicate(Rule* myRule)
{
    std::vector<std::string*> *thisQuery = new std::vector<std::string*>;

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
      thisQuery->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else
    {
      for (unsigned int i = 0; i < thisQuery->size(); ++i)
      {
          delete thisQuery->at(i);
      }

      delete thisQuery;
      delete myRule;

      throw *myTokens->at(curPos);
    }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisQuery->size(); ++i)
      {
          delete thisQuery->at(i);
      }

      delete thisQuery;
      delete myRule;

      throw myTokens->at(curPos);
    }

    //parameter
    parameter(thisQuery, myRule);

    //parameterList
    parameterList(thisQuery, myRule);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else
    {
      for (unsigned int i = 0; i < thisQuery->size(); ++i)
      {
          delete thisQuery->at(i);
      }

      delete thisQuery;
      delete myRule;

      throw myTokens->at(curPos);
    }

    //Add's a Pred to rule
    Predicate *newPred = new Predicate(thisQuery);
    myRule->addList(newPred);
}
/*
void Parser::predicateList() {
    if (myTokens->at(curPos)->getTokenType() != PERIOD)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else { throw myTokens->at(curPos); }

        // predicate
        predicate();

        // predicateList
        if (myTokens->at(curPos)->getTokenType() != PERIOD) { predicateList(); }
    }
}
*/
void Parser::predicateList(Rule* myRule) {
    if (myTokens->at(curPos)->getTokenType() != PERIOD)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
        {
          delete myRule;

          throw myTokens->at(curPos);
        }

        // predicate
        predicate(myRule);

        // predicateList
        if (myTokens->at(curPos)->getTokenType() != PERIOD) { predicateList(myRule); }
    }
}

void Parser::parameterList(std::vector<std::string*> *myVec)
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
            {
                for (unsigned int i = 0; i < myVec->size(); ++i)
                {
                    delete myVec->at(i);
                }

                delete myVec;

                throw myTokens->at(curPos);
            }

        //parameter
        parameter(myVec);

        //parameterList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { parameterList(myVec); }
    }
}

void Parser::parameterList(std::vector<std::string*> *myVec, Rule* myRule)
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
        {
          for (unsigned int i = 0; i < myVec->size(); ++i)
          {
              delete myVec->at(i);
          }

          delete myVec;
          delete myRule;

          throw myTokens->at(curPos);
        }

        //parameter
        parameter(myVec, myRule);

        //parameterList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { parameterList(myVec, myRule); }
    }
}

void Parser::stringList(std::vector<std::string*> *factList)
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
        {
          for (unsigned int i = 0; i < factList->size(); ++i)
          {
              delete factList->at(i);
          }

          delete factList;

          throw myTokens->at(curPos);
        }

        //STRING
        if (myTokens->at(curPos)->getTokenType() == STRING)
        {
          std::string* newString = new std::string(myTokens->at(curPos)->getTokenString());
          myDomain.push_back(newString);
          factList->push_back(newString);
          curPos++;
        }
        else
        {
          for (unsigned int i = 0; i < factList->size(); ++i)
          {
              delete factList->at(i);
          }

          delete factList;

          throw myTokens->at(curPos);
        }

        //stringList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { stringList(factList); }
    }
}

void Parser::idList(std::vector<std::string*> *schemeList, Rule *myRule)
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
            {
                for (unsigned int i = 0; i < schemeList->size(); ++i)
                {
                    delete schemeList->at(i);
                }

                delete schemeList;
                delete myRule;

                throw myTokens->at(curPos);
            }

        //ID
        if (myTokens->at(curPos)->getTokenType() == ID)
        {
            schemeList->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
            curPos++;
        }

        else
            {

                for (unsigned int i = 0; i < schemeList->size(); ++i)
                {
                    delete schemeList->at(i);
                }

                delete schemeList;
                delete myRule;

                throw myTokens->at(curPos);
            }

        //idList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { idList(schemeList); }
    }
}

void Parser::idList(std::vector<std::string*> *schemeList)
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
            {
                for (unsigned int i = 0; i < schemeList->size(); ++i)
                {
                    delete schemeList->at(i);
                }

                delete schemeList;

                throw myTokens->at(curPos);
            }

        //ID
        if (myTokens->at(curPos)->getTokenType() == ID)
        {
            schemeList->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
            curPos++;
        }

        else
            {

                for (unsigned int i = 0; i < schemeList->size(); ++i)
                {
                    delete schemeList->at(i);
                }

                delete schemeList;

                throw myTokens->at(curPos);
            }

        //idList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { idList(schemeList); }
    }
}

void Parser::parameter()
{
    //STRING ,ID, expression
    if (myTokens->at(curPos)->getTokenType() == ID || myTokens->at(curPos)->getTokenType() == STRING)
    {
      curPos++;
    }
    else { expression(); }
}

void Parser::parameter(std::vector<std::string*> *myVec)
{
    //STRING ,ID, expression
    if (myTokens->at(curPos)->getTokenType() == ID || myTokens->at(curPos)->getTokenType() == STRING)
    {
        myVec->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
        curPos++;
    }
    else { expression(myVec); }
}

void Parser::parameter(std::string *myStr,std::vector<std::string*> *myVec)
{
    //STRING ,ID, expression
    if (myTokens->at(curPos)->getTokenType() == ID || myTokens->at(curPos)->getTokenType() == STRING)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }
    else { expression(myStr, myVec); }
}

void Parser::parameter(std::vector<std::string*> *myVec, Rule* myRule)
{
    //STRING ,ID, expression
    if (myTokens->at(curPos)->getTokenType() == ID || myTokens->at(curPos)->getTokenType() == STRING)
    {
      myVec->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
      curPos++;
    }
    else { expression(myVec, myRule); }
}

void Parser::parameter(std::string *myStr,std::vector<std::string*> *myVec, Rule* myRule)
{
    //STRING ,ID, expression
    if (myTokens->at(curPos)->getTokenType() == ID || myTokens->at(curPos)->getTokenType() == STRING)
    {
      *myStr += myTokens->at(curPos)->getTokenString();
      curPos++;
    }
    else { expression(myStr, myVec, myRule); }
}

void Parser::expression(std::vector<std::string*> *myVec)
{
    std::string *myStr = new std::string;
    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
        for (unsigned int i = 0; i < myVec->size(); ++i)
        {
            delete myVec->at(i);
        }

        delete myVec;
        delete myStr;

        throw myTokens->at(curPos);
    }

    //parameter
    parameter(myStr, myVec);

    //operator
    op(myStr, myVec);

    //parameter
    parameter(myStr, myVec);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }
    else
    {
        for (unsigned int i = 0; i < myVec->size(); ++i)
        {
            delete myVec->at(i);
        }

        delete myVec;
        delete myStr;

        throw myTokens->at(curPos);
    }

    //Add this Expression to my parameter
    myVec->push_back(myStr);
}

void Parser::expression(std::string* myStr, std::vector<std::string*> *myVec)
{
    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
        for (unsigned int i = 0; i < myVec->size(); ++i)
        {
            delete myVec->at(i);
        }

        delete myVec;
        delete myStr;

        throw myTokens->at(curPos);
    }

    //parameter
    parameter(myStr, myVec);

    //operator
    op(myStr, myVec);

    //parameter
    parameter(myStr, myVec);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
        for (unsigned int i = 0; i < myVec->size(); ++i)
        {
            delete myVec->at(i);
        }

        delete myVec;
        delete myStr;

        throw myTokens->at(curPos);
    }
}

void Parser::expression(std::vector<std::string*> *myVec, Rule* myRule)
{
    std::string *myStr = new std::string;
    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
      for (unsigned int i = 0; i < myVec->size(); ++i)
      {
          delete myVec->at(i);
      }

      delete myVec;
      delete myRule;
      delete myStr;

      throw myTokens->at(curPos);
    }

    //parameter
    parameter(myStr, myVec, myRule);

    //operator
    op(myStr, myVec, myRule);

    //parameter
    parameter(myStr, myVec, myRule);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
      for (unsigned int i = 0; i < myVec->size(); ++i)
      {
          delete myVec->at(i);
      }

      delete myVec;
      delete myRule;
      delete myStr;

      throw myTokens->at(curPos);
    }

    //Add this Expression to my parameter
    myVec->push_back(myStr);
}

void Parser::expression(std::string* myStr, std::vector<std::string*> *myVec, Rule* myRule)
{
    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
      for (unsigned int i = 0; i < myVec->size(); ++i)
      {
          delete myVec->at(i);
      }

      delete myVec;
      delete myRule;
      delete myStr;

      throw myTokens->at(curPos);
    }

    //parameter
    parameter(myStr, myVec, myRule);

    //operator
    op(myStr, myVec, myRule);

    //parameter
    parameter(myStr, myVec, myRule);

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }

    else
    {
      for (unsigned int i = 0; i < myVec->size(); ++i)
      {
          delete myVec->at(i);
      }

      delete myVec;
      delete myRule;
      delete myStr;

      throw myTokens->at(curPos);
    }
}

void Parser::expression()
{
    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
    {
      throw myTokens->at(curPos);
    }

    //parameter
    parameter();

    //operator
    op();

    //parameter
    parameter();

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else
    {
      throw myTokens->at(curPos);
    }
}

void Parser::op()
{
    //ADD | MULTIPLY
    if (myTokens->at(curPos)->getTokenType() == ADD || myTokens->at(curPos)->getTokenType() == MULTIPLY) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::op(std::string *myStr,std::vector<std::string*> *myVec, Rule* myRule)
{
    //ADD | MULTIPLY
    if (myTokens->at(curPos)->getTokenType() == ADD || myTokens->at(curPos)->getTokenType() == MULTIPLY)
    {
      *myStr += myTokens->at(curPos)->getTokenString();
      curPos++;
    }
    else
    {
      for (unsigned int i = 0; i < myVec->size(); ++i)
      {
          delete myVec->at(i);
      }

      delete myVec;
      delete myRule;
      delete myStr;

      throw myTokens->at(curPos);
    }
}

void Parser::op(std::string *myStr,std::vector<std::string*> *myVec)
{
    //ADD | MULTIPLY
    if (myTokens->at(curPos)->getTokenType() == ADD || myTokens->at(curPos)->getTokenType() == MULTIPLY)
    {
        *myStr += myTokens->at(curPos)->getTokenString();
        curPos++;
    }
    else
    {
        for (unsigned int i = 0; i < myVec->size(); ++i)
        {
            delete myVec->at(i);
        }

        delete myVec;
        delete myStr;

        throw myTokens->at(curPos);
    }
}

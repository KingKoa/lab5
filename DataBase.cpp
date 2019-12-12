#include "DataBase.h"
#include <iostream>
#include <algorithm>    // std::sort

bool esConstant(std::string checkThis)
{
    if (checkThis.at(0) == '\'' && checkThis.at((checkThis.size() - 1)) == '\'')
    {
        return true;
    }

    return false;
}

void DataBase::addSchemes(std::vector<Predicate*> mySchemes) {
    for (unsigned int i = 0; i < mySchemes.size(); i++) {
        Relation *newRelation = new Relation();

        Predicate curScheme = *(mySchemes.at(i));

        newRelation->setScheme(curScheme.getName(), curScheme.getParams());
        myRelations.push_back(newRelation);
    }
}

void DataBase::addFacts(std::vector<Predicate*> myFacts) {
    for (unsigned int i = 0; i < myFacts.size(); i++) {
        Predicate *curFact = myFacts.at(i);

        for (unsigned int j = 0; j < myRelations.size(); j++) {
            std::string relName = myRelations.at(j)->getName();
            if (relName == curFact->getName()) {
                myRelations.at(j)->setTuple(curFact->getParams());
                break;
            }
        }
    }
}

std::string DataBase::addRules(std::vector<Rule*> myRules) {

    std::string returnString = "Dependency Graph\n";
    if(myRules.size() == 0)
    {
        returnString += "\nRule Evaluation\n\n";
        return returnString;
    }
    /*
     * Build the dependency graph.
        Build the reverse dependency graph.
        Run DFS-Forest on the reverse dependency graph.
        Find the strongly connected components (SCCs).
        Evaluate the rules in each component.
     */

    //Graph
    bool isDup = false;

    std::vector<std::vector<unsigned int>*> myGraph;
    for(unsigned int i = 0; i < myRules.size(); ++i) {
        myGraph.push_back(new std::vector<unsigned int>);
    }

    for(unsigned int i = 0; i < myRules.size(); ++i) {
        std::vector<Predicate> thisRule = myRules.at(i)->getPred();
        for(unsigned int k = 0; k < myRules.size(); ++k) { //unsigned int j = 0; j < thisRule.size(); ++j
            std::string thisDep = myRules.at(k)->getName().getName();
            for(unsigned int j = 0; j < thisRule.size(); ++j) { //unsigned int k = 0; k < myRules.size(); ++k
                if(thisDep == thisRule.at(j).getName()) {
                    isDup = false;
                    for(unsigned int lmao = 0; lmao < myGraph.at(i)->size(); ++lmao) {
                        if(myGraph.at(i)->at(lmao) == k) { isDup = true; }
                    }
                    if(!isDup) { myGraph.at(i)->push_back(k); }
                }
            }
        }
    }

    for(unsigned int i = 0; i < myGraph.size(); ++i) {
        returnString += "R";
        returnString += std::to_string(i);
        returnString += ":";
        for(unsigned int j = 0; j < myGraph.at(i)->size(); ++j) {
            returnString += "R";
            returnString += std::to_string(myGraph.at(i)->at(j));
            if(j != myGraph.at(i)->size() - 1) { returnString += ","; }
        }
        returnString += "\n";
    }

    returnString += "\n";

    // Build Reverse Dependencey Graph
    std::vector<std::vector<unsigned int>*> reverseGraph;
    for(unsigned int i = 0; i < myRules.size(); ++i) {
        reverseGraph.push_back(new std::vector<unsigned int>);
    }

    for(unsigned int i = 0; i < myGraph.size(); ++i) {
        for(unsigned int j = 0; j < myGraph.at(i)->size(); ++j) {
            reverseGraph.at(myGraph.at(i)->at(j))->push_back(i);
        }
    }

    //sort the reverse graph
    for(unsigned int i = 0; i < reverseGraph.size(); ++i) {
        std::sort(reverseGraph.at(i)->begin(), reverseGraph.at(i)->end());
    }

    //DFS Forst
    unsigned int V = reverseGraph.size();
    std::vector<unsigned int> DFS(V, 0);
    std::vector<bool> visited(V, false);
    std::stack<unsigned int> stack;
    unsigned int s = 0;
    stack.push(s);
    int postOrderNum = 1;
    while(!stack.empty()) {
        s = stack.top();

        if(!visited[s]) {
            visited[s] = true;
        } else {

            if(DFS.at(s) == 0) {
                DFS.at(s) = postOrderNum;
                ++postOrderNum;
            }
            stack.pop();
        }

        for(int i = reverseGraph.at(s)->size() - 1; i >= 0; --i) {
            if(!visited[reverseGraph.at(s)->at(i)]) {
                stack.push(reverseGraph.at(s)->at(i));
            }
        }
        if(stack.empty()) {
            for(unsigned int i = 0; i < visited.size(); ++i) {
                if(!visited[i]) {
                    stack.push(i);
                    break;
                }
            }
        }
    }

    returnString += "Rule Evaluation\n";
    //bool Done = false;

    unsigned int n = 0;

    unsigned int preNumTup = 0;

    //Find the strongly connected components (SCCs).
    //Reset Visited Nodes
    std::vector<std::vector<unsigned int>*> SCCs;
    for(unsigned int i = 0; i < myRules.size(); ++i) {
        SCCs.push_back(new std::vector<unsigned int>);
    }

    std::vector<bool> visitedMyGraph(V, false);
    bool allVisited = false;
    for (unsigned int i = 0; i < visited.size(); ++i) {
        visited[i] = false;
    }

    while(!allVisited) {
        allVisited = true;

        for (unsigned int i = 0; i < visited.size(); ++i) {
            visited[i] = false;
        }

        unsigned int biggestPON = 0;
        unsigned int posPON = 0;
        for (unsigned int i = 0; i < DFS.size(); ++i) {
            if (biggestPON < DFS.at(i) && !visitedMyGraph[i]) {
                biggestPON = DFS.at(i);
                posPON = i;
            }
        }
        stack.push(posPON);

        while (!stack.empty()) {
            s = stack.top();
            stack.pop();

            if (!visited[s]) {
                visited[s] = true;

            }

            for (unsigned int i = 0; i < myGraph.at(s)->size(); ++i) {
                if (!visited[myGraph.at(s)->at(i)]) {
                    stack.push(myGraph.at(s)->at(i));
                }
            }

        }

        visitedMyGraph[posPON] = true;


        for (unsigned int i = 0; i < reverseGraph.at(posPON)->size(); ++i) {
            if(reverseGraph.at(posPON)->at(i) == posPON) {
                SCCs.at(posPON)->push_back(posPON);
            }
        }

        for (unsigned int i = 0; i < visited.size(); ++i) {
            if (visited[i] && !visitedMyGraph[i] && i != posPON) {
                SCCs.at(posPON)->push_back(i);
                visitedMyGraph[i] = true;
            }
        }

        bool allRulesEvaluated = false;

        for (unsigned int t = 0; t < myRelations.size(); ++t) {
            preNumTup += myRelations.at(t)->getTuple().size();
        }

        for (unsigned int i = 0; i < visited.size(); ++i) {
            visited[i] = false;
        }

        unsigned int postNumTup = preNumTup;
        n = 0;



        if(SCCs.at(posPON)->size() == 0) {
            returnString += "SCC: R";
            returnString += std::to_string(posPON);
            returnString += "\n";

            n = 1;
            //returnString += ",R";
            //returnString += std::to_string(SCCs.at(posPON)->at(i));

            /*
             * 1. Evaluate the predicates on the right-hand side of the rule
             * 2. Join the relations that result
             * 3. Project the columns that appear in the head predicate
             * 4. Rename the relation to make it union-compatible
             * 5. Union with the relation in the database
             */

            //This is just what we do for setting the schemes
            Relation *ruleRel = new Relation();
            Predicate ruleScheme = myRules.at(posPON)->getName();
            for (unsigned int q = 0; q < myRelations.size(); ++q) {
                if (ruleScheme.getName() == myRelations.at(q)->getName()) {
                    //ruleRel->setScheme(ruleScheme.getName(), ruleScheme.getParams());

                    std::vector <Predicate> thisRule = myRules.at(posPON)->getPred();

                    for (unsigned int z = 0; z < thisRule.size(); z++) {
                        Predicate rulePart = thisRule.at(z);

                        for (unsigned int y = 0; y < myRelations.size(); y++) {
                            std::string relName = myRelations.at(y)->getName();
                            if (relName == rulePart.getName()) {
                                Relation thisRelation = *(myRelations.at(y));
                                //Evaluate Query
                                //Grab the realtion from DB *That's what curQuery is*
                                std::vector < std::string * > curParams = *(rulePart.getParams());
                                std::map<unsigned int, std::string> firstTimer;
                                //std::map<std::string, unsigned int> dupVars;
                                std::vector <std::string> dupVars;
                                // Go through Params
                                //Check each

                                for (unsigned int k = 0; k < curParams.size(); ++k) {
                                    if (esConstant(*(curParams.at(k)))) {
                                        //if const do a select
                                        //returnString += "it's a const \n";
                                        thisRelation = *(thisRelation.select(*(curParams.at(k)),
                                                                             *(thisRelation.getAttributesAt(
                                                                                     k))));
                                        //thisRelation = *(thisRelation.select(*(curParams.at(k)), *(myDataBase.getRelations().at(j)->getAttributes()->at(k))));
                                    } else {
                                        bool isDup = false;
                                        for (unsigned int o = 0; o < dupVars.size(); ++o) {
                                            if (dupVars.at(o) == *(curParams.at(k))) {
                                                isDup = true;
                                                break;
                                            }
                                        }
                                        if (!isDup && firstTimer.insert(std::pair<unsigned int, std::string>(k,
                                                                                                             *(curParams.at(
                                                                                                                     k)))).second) {
                                            firstTimer.insert(std::pair<unsigned int, std::string>(k,
                                                                                                   *(curParams.at(
                                                                                                           k))));
                                            dupVars.push_back(*(curParams.at(k)));
                                        } else {
                                            std::map<unsigned int, std::string>::iterator mapIt;

                                            for (mapIt = firstTimer.begin();
                                                 mapIt != firstTimer.end(); ++mapIt) {
                                                if (mapIt->second == *(curParams.at(k))) {
                                                    thisRelation = *(thisRelation.selectMatching(
                                                            *(thisRelation.getAttributesAt(k)),
                                                            *(thisRelation.getAttributesAt(mapIt->first))));
                                                }
                                            }
                                        }
                                    }
                                }
                                //Do a project
                                thisRelation = *(thisRelation.project(firstTimer));

                                //Do a rename & Join
                                thisRelation = *(thisRelation.rename(firstTimer));

                                if (z != 0) {
                                    ruleRel = ruleRel->join(&thisRelation, ruleRel);
                                } else {
                                    *ruleRel = thisRelation;
                                }
                            }
                        }
                    }

                    std::vector <std::pair<unsigned int, std::string>> ruleMap;
                    std::vector < std::string * > curParams = *(myRules.at(
                            posPON)->getName().getParams());
                    std::vector < std::string * > ruleRelParams = *(ruleRel->getAttributes());
                    //Map Rule

                    for (unsigned int k = 0; k < curParams.size(); ++k) {
                        for (unsigned int z = 0; z < ruleRelParams.size(); ++z) {
                            if (*(curParams.at(k)) == *(ruleRelParams.at(z))) {

                                ruleMap.push_back(
                                        std::pair<unsigned int, std::string>(z, *(ruleRelParams.at(z))));
                            }
                        }
                    }

                    //Project Columns
                    ruleRel = ruleRel->project(ruleMap);
                    //Rename Relation
                    ruleRel = ruleRel->rename(ruleMap);

                    returnString += myRules.at(posPON)->toString();

                    //bool isNew = true;
                    //Find the Dif between relations and rule
                    //for(unsigned int a = 0; a < ruleRel->getTuple().size(); ++a) {
                    for( Tuple t : ruleRel->getTuple()) {
                        //isNew = true;
                        //for(unsigned int b = 0; b < myRelations.at(q)->getTuple().size(); ++b) {
                        //    if(ruleRel->getTupleAt(a) == myRelations.at(q)->getTupleAt(b)) {
                        //isNew = false;
                        //    }
                        //}
                        if(!myRelations.at(q)->getTuple().count(t)){
                            returnString += "  ";
                            for(unsigned int c = 0; c < myRelations.at(q)->getAttributes()->size(); ++c)
                            {
                                returnString += *(myRelations.at(q)->getAttributesAt(c));
                                returnString += "=";
                                returnString += t.at(c);
                                if(c != myRelations.at(q)->getAttributes()->size() - 1) { returnString += ", "; }
                            }
                            returnString += "\n";
                        }
                    }

                    //Union Rule with it's Scheme
                    myRelations.at(q) = myRelations.at(q)->unionize(*(myRelations.at(q)), *(ruleRel));


                    /*

                    postNumTup = 0;
                    for (unsigned int t = 0; t < myRelations.size(); ++t) {
                        postNumTup += myRelations.at(t)->getTuple().size();

                    }

                    if (postNumTup != preNumTup) {
                        Done = false;
                        preNumTup = postNumTup;
                        returnString += myRelations.at(q)->toString();
                        //returnString += ruleRel->toString();
                    }
                     */
                }

            }

        }


        else {
            unsigned int position = 0;
            bool found = false;
            for(position = 0; position < SCCs.at(posPON)->size(); ++position) {
                if(SCCs.at(posPON)->at(position) == posPON) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                for(position = 0; position < SCCs.at(posPON)->size(); ++position) {
                    if(SCCs.at(posPON)->at(position) > posPON) {
                        break;
                    }
                }
                //--position;
                SCCs.at(posPON)->insert(SCCs.at(posPON)->begin() + position, posPON);
            }

            returnString += "SCC: ";
            for(unsigned int i = 0; i < SCCs.at(posPON)->size(); i++) {
                returnString += "R";
                returnString += std::to_string(SCCs.at(posPON)->at(i));

                if(SCCs.at(posPON)->size() - 1 != i) {
                    returnString += ",";
                }
            }
            returnString += "\n";

            n = 0;
            while (!allRulesEvaluated) {

                preNumTup = postNumTup;
                //Done = true;
                for (unsigned int i = 0; i < SCCs.at(posPON)->size(); i++) {
                    //isEvaluated = false;


                    //returnString += ",R";
                    //returnString += std::to_string(SCCs.at(posPON)->at(i));

                    /*
                     * 1. Evaluate the predicates on the right-hand side of the rule
                     * 2. Join the relations that result
                     * 3. Project the columns that appear in the head predicate
                     * 4. Rename the relation to make it union-compatible
                     * 5. Union with the relation in the database
                     */

                    //This is just what we do for setting the schemes
                    Relation *ruleRel = new Relation();
                    Predicate ruleScheme = myRules.at(SCCs.at(posPON)->at(i))->getName();
                    for (unsigned int q = 0; q < myRelations.size(); ++q) {
                        if (ruleScheme.getName() == myRelations.at(q)->getName()) {
                            //ruleRel->setScheme(ruleScheme.getName(), ruleScheme.getParams());

                            std::vector <Predicate> thisRule = myRules.at(SCCs.at(posPON)->at(i))->getPred();

                            for (unsigned int z = 0; z < thisRule.size(); z++) {
                                Predicate rulePart = thisRule.at(z);

                                for (unsigned int y = 0; y < myRelations.size(); y++) {
                                    std::string relName = myRelations.at(y)->getName();
                                    if (relName == rulePart.getName()) {
                                        Relation thisRelation = *(myRelations.at(y));
                                        //Evaluate Query
                                        //Grab the realtion from DB *That's what curQuery is*
                                        std::vector < std::string * > curParams = *(rulePart.getParams());
                                        std::map<unsigned int, std::string> firstTimer;
                                        //std::map<std::string, unsigned int> dupVars;
                                        std::vector <std::string> dupVars;
                                        // Go through Params
                                        //Check each

                                        for (unsigned int k = 0; k < curParams.size(); ++k) {
                                            if (esConstant(*(curParams.at(k)))) {
                                                //if const do a select
                                                //returnString += "it's a const \n";
                                                thisRelation = *(thisRelation.select(*(curParams.at(k)),
                                                                                     *(thisRelation.getAttributesAt(
                                                                                             k))));
                                                //thisRelation = *(thisRelation.select(*(curParams.at(k)), *(myDataBase.getRelations().at(j)->getAttributes()->at(k))));
                                            } else {
                                                bool isDup = false;
                                                for (unsigned int o = 0; o < dupVars.size(); ++o) {
                                                    if (dupVars.at(o) == *(curParams.at(k))) {
                                                        isDup = true;
                                                        break;
                                                    }
                                                }
                                                if (!isDup && firstTimer.insert(std::pair<unsigned int, std::string>(k,
                                                                                                                     *(curParams.at(
                                                                                                                             k)))).second) {
                                                    firstTimer.insert(std::pair<unsigned int, std::string>(k,
                                                                                                           *(curParams.at(
                                                                                                                   k))));
                                                    dupVars.push_back(*(curParams.at(k)));
                                                } else {
                                                    std::map<unsigned int, std::string>::iterator mapIt;

                                                    for (mapIt = firstTimer.begin();
                                                         mapIt != firstTimer.end(); ++mapIt) {
                                                        if (mapIt->second == *(curParams.at(k))) {
                                                            thisRelation = *(thisRelation.selectMatching(
                                                                    *(thisRelation.getAttributesAt(k)),
                                                                    *(thisRelation.getAttributesAt(mapIt->first))));
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        //Do a project
                                        thisRelation = *(thisRelation.project(firstTimer));

                                        //Do a rename & Join
                                        thisRelation = *(thisRelation.rename(firstTimer));

                                        if (z != 0) {
                                            ruleRel = ruleRel->join(&thisRelation, ruleRel);
                                        } else {
                                            *ruleRel = thisRelation;
                                        }
                                    }
                                }
                            }

                            std::vector <std::pair<unsigned int, std::string>> ruleMap;
                            std::vector < std::string * > curParams = *(myRules.at(
                                    SCCs.at(posPON)->at(i))->getName().getParams());
                            std::vector < std::string * > ruleRelParams = *(ruleRel->getAttributes());
                            //Map Rule

                            for (unsigned int k = 0; k < curParams.size(); ++k) {
                                for (unsigned int z = 0; z < ruleRelParams.size(); ++z) {
                                    if (*(curParams.at(k)) == *(ruleRelParams.at(z))) {

                                        ruleMap.push_back(
                                                std::pair<unsigned int, std::string>(z, *(ruleRelParams.at(z))));
                                    }
                                }
                            }

                            //Project Columns
                            ruleRel = ruleRel->project(ruleMap);
                            //Rename Relation
                            ruleRel = ruleRel->rename(ruleMap);

                            returnString += myRules.at(SCCs.at(posPON)->at(i))->toString();

                            //bool isNew = true;
                            //Find the Dif between relations and rule
                            //for(unsigned int a = 0; a < ruleRel->getTuple().size(); ++a) {
                            for( Tuple t : ruleRel->getTuple()) {
                                //isNew = true;
                                //for(unsigned int b = 0; b < myRelations.at(q)->getTuple().size(); ++b) {
                                //    if(ruleRel->getTupleAt(a) == myRelations.at(q)->getTupleAt(b)) {
                                //isNew = false;
                                //    }
                                //}
                                if(!myRelations.at(q)->getTuple().count(t)){
                                    returnString += "  ";
                                    for(unsigned int c = 0; c < myRelations.at(q)->getAttributes()->size(); ++c)
                                    {
                                        returnString += *(myRelations.at(q)->getAttributesAt(c));
                                        returnString += "=";
                                        returnString += t.at(c);
                                        if(c != myRelations.at(q)->getAttributes()->size() - 1) { returnString += ", "; }
                                    }
                                    returnString += "\n";
                                    postNumTup++;
                                }
                            }

                            //Union Rule with it's Scheme
                            myRelations.at(q) = myRelations.at(q)->unionize(*(myRelations.at(q)), *(ruleRel));


                            /*

                            postNumTup = 0;
                            for (unsigned int t = 0; t < myRelations.size(); ++t) {
                                postNumTup += myRelations.at(t)->getTuple().size();

                            }

                            if (postNumTup != preNumTup) {
                                Done = false;
                                preNumTup = postNumTup;
                                returnString += myRelations.at(q)->toString();
                                //returnString += ruleRel->toString();
                            }
                             */
                        }

                    }
                }
                /*
                postNumTup = 0;
                for (unsigned int t = 0; t < myRelations.size(); ++t) {
                    postNumTup += myRelations.at(t)->getTuple().size();

                }
                */
                if (postNumTup == preNumTup) { allRulesEvaluated = true; }
                ++n;
            } // END OF WHILE
        }
        returnString += std::to_string(n);
        returnString += " passes: ";

        if(SCCs.at(posPON)->size() == 0) {
            returnString += "R";
            returnString += std::to_string(posPON);
        }
        else {
            for(unsigned int i = 0; i < SCCs.at(posPON)->size(); i++) {
                returnString += "R";
                returnString += std::to_string(SCCs.at(posPON)->at(i));

                if(SCCs.at(posPON)->size() - 1 != i) {
                    returnString += ",";
                }
            }
        }

        returnString += "\n";

        for (unsigned int i = 0; i < visited.size(); ++i) {
            visited[i] = false;
        }

        for (unsigned int i = 0; i < visitedMyGraph.size(); ++i) {
            if (!visitedMyGraph[i]) { allVisited = false; }
        }
    }

    for(unsigned int i = 0; i < myRules.size(); ++i) {
        delete reverseGraph.at(i);
        delete myGraph.at(i);
    }

    returnString += "\n";

    return returnString;
}

std::string DataBase::printDB() {
    std::string returnString = "";
    for (unsigned int i = 0; i < myRelations.size(); ++i) {
        returnString += myRelations.at(i)->toString();
        returnString += "\n";
    }

    return returnString;
}



/*
std::string Interpreter::checkQueries(std::vector<Predicate*> myQueries)
{
  std::string returnString = "";

  for(unsigned int i = 0; i < myQueries.size(); i++)
  {
    Predicate curQuery = *(myQueries.at(i));

    for(unsigned int j = 0; j < myDataBase.getRelations().size(); j++)
    {
      std::string relName = myDataBase.getRelations().at(j)->getName();
      if(relName == curQuery.getName())
      {
        Relation thisRelation = *(myDataBase.getRelations().at(j));
        returnString += curQuery.toString();
        returnString += "? ";
        //Evaluate Query
          //Grab the realtion from DB *That's what curQuery is*
          std::vector<std::string*> curParams = *(curQuery.getParams());
          std::map<unsigned int,std::string> firstTimer;
          //std::map<std::string, unsigned int> dupVars;
          std::vector<std::string> dupVars;
          // Go through Params
          //Check each
          for(unsigned int k = 0; k < curParams.size(); ++k)
          {
            if(isConstant(*(curParams.at(k))))
            {
              //if const do a select
              //returnString += "it's a const \n";
              thisRelation = *(thisRelation.select(*(curParams.at(k)), *(thisRelation.getAttributesAt(k))));
              //thisRelation = *(thisRelation.select(*(curParams.at(k)), *(myDataBase.getRelations().at(j)->getAttributes()->at(k))));
            }

            else
            {
                bool isDup = false;
                for (unsigned int o = 0; o < dupVars.size(); ++o)
                {
                    if(dupVars.at(o) == *(curParams.at(k)))
                    {
                        isDup = true;
                        break;
                    }
                }
              if(!isDup && firstTimer.insert(std::pair<unsigned int,std::string>(k, *(curParams.at(k)))).second)
              {
                firstTimer.insert(std::pair<unsigned int,std::string>(k, *(curParams.at(k))));
                dupVars.push_back(*(curParams.at(k)));
              }

              else
              {
                  std::map<unsigned int,std::string>::iterator mapIt;

                  for (mapIt = firstTimer.begin(); mapIt != firstTimer.end(); ++mapIt)
                  {
                      if(mapIt->second == *(curParams.at(k)))
                      {
                          thisRelation = *(thisRelation.selectMatching(*(thisRelation.getAttributesAt(k)), *(thisRelation.getAttributesAt(mapIt->first))));
                      }
                  }
              }
            }
          }
          //Do a project
          thisRelation = *(thisRelation.project(firstTimer));

          //Do a rename
          thisRelation = *(thisRelation.rename(firstTimer));
        //Check size of query answer aka num tuples ( retuned as relation )
        // if not put Yes(num Tuples)
        // then print the returned relation
        if (thisRelation.getTuple().size() != 0)
        {
          returnString += "Yes(";
          returnString += std::to_string(thisRelation.getTuple().size());
          returnString += ")\n";
          returnString += thisRelation.toString();
        }
        // if 0 out put No
        else
        {
          returnString += "No\n";
        }
      }
    }
  }

  return returnString;
}
 */

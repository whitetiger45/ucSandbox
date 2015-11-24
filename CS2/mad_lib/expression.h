#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Exp
{
public:

    Exp()
    {
    };

    virtual string getString() = 0;
    typedef vector<Exp*> ChoiceVector;
    typedef vector<Exp*> SequenceVector;
    typedef map<string, Exp*> KeyWordMap;
    typedef map<string, Exp*>* KeyWordMapPtr;
    typedef map<string, Exp*>::iterator KeyWordMapIter;

};
/*
------------------------------------------------------
*/
class Terminal
    : public Exp
{

public:

    Terminal(string word)
    {
        this->word = word;
    };

    virtual string getString()
    {
        return word;
    }

protected:

    string word;

};

/*
---------------------------------------------------------------
*/

class Sequence
    : public Exp
{

public:

    virtual string getString()
    {
        string ret;
        for(auto ess : expression_storage_sequence)
            ret+= ess->getString() + " ";
        return ret;
    }

    void addExpression(Exp* thing)
    {
        expression_storage_sequence.push_back(thing);
    }

protected:

    SequenceVector expression_storage_sequence;
};

/*
---------------------------------------------------------------
*/

class Choice
    : public Exp
{

public:

    virtual string getString()
    {
        int i = rand() % expression_storage_choice.size();
        string ret = expression_storage_choice[i]->getString();
        return ret;
    }

    void addExpression(Exp* thing)
    {
        expression_storage_choice.push_back(thing);
    }

protected:

    ChoiceVector expression_storage_choice;
};



/*
-------------------------------------------------------------------
*/

class Keyword
    : public Exp
{

public:

    Keyword(KeyWordMapPtr mp, string keyword)
    {
        the_map_pointer = mp;
        key_word = keyword;
    }

    virtual string getString()
    {

        KeyWordMapIter kwIT;
        kwIT = the_map_pointer->find(key_word);

        bool found = true;
        string not_found;
        not_found = ":(";

        if(kwIT == the_map_pointer->end())
        {
            found = false;
            return not_found;
        }

        else if(found)
            return (*the_map_pointer)[key_word]->getString();
    }

protected:
    string key_word;
    KeyWordMapPtr the_map_pointer;
};

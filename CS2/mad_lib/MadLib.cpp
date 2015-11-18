/*    @file MadLib.cpp
      @author: Bryan Kanu
      @CS2 Assignment
      @Dr. Talaga
      @date 10/21/14

      @description This program accepts a grammar instance text file and
      prints out a random instance from that grammar.
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expression.h"

using namespace std;

Exp* parse(map<string, Exp*>* keywords, string input)
{
    string line_inside_parse = input;
    string expression, expression2;
    int count = 0;
    ///this if is where we start looking for choices
    size_t pos = line_inside_parse.find('|');
    std::smatch sm_keyWord;
    std::cmatch cm, p_keyWord;
    std::regex barRegEx("(.*)");
    std::regex keyWordParseRegEx("<([a-z]+)>.*");
    if( std::regex_match (line_inside_parse.c_str(),cm,barRegEx) && (isalpha(cm.str(1)[0])) && !iscntrl(cm.str(1)[0]))
    {
        //cout << "Bar Word: " << cm.str(1) << "\n";
    }
    if(line_inside_parse.find('|') != string::npos)
    {
        Choice* ret = new Choice();

        expression = line_inside_parse.substr(0, pos);
        line_inside_parse = line_inside_parse.substr(pos + 1);

        ret->addExpression(parse(keywords, expression));

        if(line_inside_parse.size() == 0)
            return ret;
        pos = line_inside_parse.find('|');
        while(pos != string::npos)
        {
            pos = line_inside_parse.find('|');
            expression = line_inside_parse.substr(0, pos);
            pos = line_inside_parse.find('|');
            count++;
            if(pos != string::npos)
            {
                line_inside_parse = line_inside_parse.substr(pos + 1);
            }
            else
            {
                expression = line_inside_parse.substr(0, string::npos);
                expression2 = cm.str(1);
                //cout << "\n\nPARSE '|' DEBUG inside else before return: " << expression;
                ret->addExpression(parse(keywords, expression));
                return ret;
            }
            //cout << "\n\nPARSE '|' DEBUG inside while: " << line_inside_parse;
            ret->addExpression(parse(keywords, expression));
        }
    }
    ///this else if is where we start looking for sequences
    else if(line_inside_parse.find(' ') != string::npos)
    {
        pos = line_inside_parse.find(' ');
        Sequence* ret = new Sequence();
        int count= 0;
        while(pos != string::npos)
        {
            expression = line_inside_parse.substr(0, pos);
            line_inside_parse= line_inside_parse.substr(pos + 1);

            count++;
            pos = line_inside_parse.find(' ');
            //cout << "\n\nPARSE ' ' DEBUG inside while: " << line_inside_parse;
            ret->addExpression(parse(keywords, expression));
        }
        if(pos == string::npos)
        {
            //cout << "\n\nPARSE ' ' DEBUG Inside if before ret: " << line_inside_parse;
            ret->addExpression(parse(keywords, line_inside_parse));
            return ret;
        }
        return ret;
    }
    //////////This else if is where we look for keywords
    else if(line_inside_parse.find('<') != string::npos)
    {
        string found_keyword=  line_inside_parse.substr(1, line_inside_parse.size()-1);
        //cout << "\n\nPARSE '<' DEBUG: " << line_inside_parse;
        pos = line_inside_parse.find('<');
        found_keyword.erase(found_keyword.size()-1, 1);
        //Keyword* ret = new Keyword(keywords, found_keyword);//original add new keyword in parse
    Keyword* ret;
    if( std::regex_match (cm.str(1),sm_keyWord, keyWordParseRegEx))
    {
        //cout << "*****\nKeyword in parse: (0)" << sm_keyWord[0] << "\n";
        if( std::regex_match (cm.str(1).c_str(),p_keyWord, keyWordParseRegEx))
        {
           // cout << "\nKeyword in parse, nested if: " << p_keyWord.str(0) << "\n*******\n";
            string kw = p_keyWord.str(0);
            //cout << "\nKeyword in parse, nested if: " << kw.substr(1, kw.size()-2) << "\n*******\n";
            kw = kw.substr(1, kw.size()-2);
            ret = new Keyword(keywords, kw);
        }
    }
        return ret;
    }
    ///if the input gets down here it must be a terminal
    else
    {
        expression = line_inside_parse;
        //cout << "\n******\nFOUND TERMINAL: " << cm.str(0) << "\n******\n";
        Terminal* ret = new Terminal(expression);

        return ret;
    }
}

int main(int argc, char* argv[])
{
//code example used was that shown  in the example solutions produced by Viveka Aggarwal
//https://github.uc.edu/CS2-Fall2014/ExamplesSolutions/blob/master/Solutions/02/printstats_HW2.cpp
//http://cs.dvc.edu/HowTo_Cparse.html
    int input = 0;

    const char* input_file_name = "textDocs/late.txt";
    //bool invalid_input = true;
/*
    while(input != -1){
         if (argc != 2){
                  cout<<"\nYou must include a text document filename on the command text_file_line!\n";
                  cout<<"Format: <text document>.txt\n" << endl;
                  exit(EXIT_SUCCESS);
              }

        input_file_name = *(argv + 1);
        break;
    }
*/
    ifstream file;
    file.open(input_file_name);
    file.seekg(0, file.end);
    file.seekg(0, file.beg);

    string text_file_line;
    vector<string> stored_lines_vector;
    vector<string> stored_keywords_vector;
    string keyword_in_text;
    int loop_count = 0;

    map<string, Exp*> keyword_map;
    //map<string, Exp*>::iterator it= keyword_map.begin();

    //http://www.cplusplus.com/forum/beginner/70805/
    //http://stackoverflow.com/questions/16074980/parse-a-file-in-c-and-ignore-some-characters
    std::cmatch cm;
    std::smatch mr, m2;
    std::regex keyWordRegEx("^([a-z]+):(.*)");
    std::regex regEx("<([a-z]+)>(.*)");
    std::regex r2("([A-Z?a-z]+ ?[a-z]* ?[a-z]*)(.*)");
    bool more = true;
    auto chop3 = [&m2, &r2](string in)->string{string ret; if(std::regex_match(in, m2, r2)){cout << "\nterminal: "<< m2[1]; 
                                                                                                        ret = m2[2];                                                                                                                                                                                                            
                                                                                                        if(isspace(ret[0]))
                                                                                                            ret = ret.substr(1, ret.size());
                                                                                                        }
                                                                                                        cout <<"\nrest of line: " <<  ret << "\n" ; return ret;};
    auto chop4 = [&regEx, &mr](string rol)->string{string ret; if(std::regex_match(rol, mr, regEx)){cout << "\nkeyword: "<< mr[1]<< "\nrest: " << mr[2] << "\n"; 
                                                                                                    ret = mr[2]; 
                                                                                                    if(isspace(ret[0]))
                                                                                                        ret = ret.substr(1, ret.size());
                                                                                                    }return ret;};

    auto chop = [](string restOfLine)->string{string ret; size_t pos = restOfLine.find("|"); if(pos != string::npos)cout <<"\nWord: " << restOfLine.substr(0, pos) << "\n"; ret= restOfLine.substr(pos+1);return ret;};
    
    auto chop2 = [&regEx, &mr, &more, &chop3, &chop4](string rol)->string{string ret; if(std::regex_match(rol, mr, regEx)){more = true;cout << "\nkeyword: "<< mr[1]<< "\nrest: " << mr[2] << "\n"; 
                                                                                                    ret = mr[2]; 
                                                                                                    if(isspace(ret[0]))
                                                                                                        ret = ret.substr(1, ret.size());
                                                                                                    while(ret[0] == '<')
                                                                                                        ret = chop4(ret);
                                                                                                    ret = chop3(ret);
                                                                                                    }
                                                                        else
                                                                        {
                                                                            more = false; 
                                                                        }
                                                                        return ret;};

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, text_file_line);
            size_t pos= text_file_line.find(':');
            
           //if( std::regex_match (text_file_line.c_str(),cm,keyWordRegEx))

            if(pos != string::npos)
            {
                //keyword_in_text = text_file_line.substr(0, pos);
                if( std::regex_match (text_file_line.c_str(),cm,keyWordRegEx))
                {
                    keyword_in_text = cm.str(1);
                    stored_keywords_vector.push_back(keyword_in_text);//keywords vector

                    stored_lines_vector.push_back(cm.str(2));//lines vector after colon extracted

                    keyword_map[keyword_in_text] = parse(&keyword_map, stored_lines_vector[loop_count]);
                }

            }
        string line = cm.str(2);
        while(line.find("|"))
        {
            line = chop(line);
            if(line.find("|") == string::npos)
            {
                break;
            }
        }
        while(more)
            line = chop2(line);
            loop_count++;
        }
        file.close();
    }

    srand(time(NULL));

    // Create map of keywords to expressions

    map<string, Exp*> m;

    Choice* action = new Choice();
    Exp* k1 = new Keyword(&m, "house");
    Terminal* v1 = new Terminal("ran");
    Terminal* v2 = new Terminal("walked");
    Terminal* v3 = new Terminal("crawled");

    action->addExpression(v1);
    action->addExpression(v2);
    action->addExpression(v3);
    action->addExpression(k1);

    // For every text_file_line in the file, send the right side to parse
    // and put the resuling Expression pointer into the map.
    //m[--keyword--] = parse(&m, --right side of text_file_line--);

    // Get start expression and print out sentence!

    Exp* myMadlib = keyword_map["start"];
    cout << myMadlib->getString() << endl;


  // Return all memory back to OS.
    delete action;
    delete k1;
    delete v1;
    delete v2; 
    delete v3;
}


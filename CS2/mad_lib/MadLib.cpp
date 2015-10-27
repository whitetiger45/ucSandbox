/*    @file MadLib.cpp
      @author <Bryan Kanu>
      @date <10/21/14>

      @description This program accepts a grammar instance text file and
      prints out a random instance from that grammar.
*/

#include <iostream>
#include <cstdlib>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "expression.h"

using namespace std;

Exp* parse(map<string, Exp*>* keywords, string input)
{
    string line_inside_parse = input;
    string expression;
    int count = 0;

    ///this if is where we start looking for choices
    size_t pos = line_inside_parse.find('|');
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
                ret->addExpression(parse(keywords, expression));
                return ret;
            }
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

            ret->addExpression(parse(keywords, expression));
        }
        if(pos == string::npos)
        {
            ret->addExpression(parse(keywords, line_inside_parse));
            return ret;
        }
        return ret;
    }

    //////////This else if is where we look for keywords
    else if(line_inside_parse.find('<') != string::npos)
    {
        string found_keyword=  line_inside_parse.substr(1, line_inside_parse.size()-1);

        pos = line_inside_parse.find('<');
        found_keyword.erase(found_keyword.size()-1, 1);

        Keyword* ret = new Keyword(keywords, found_keyword);

        return ret;
    }

    ///if the input gets down here it must be a terminal

    else
    {
        expression = line_inside_parse;
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

    const char* input_file_name = "textDocs/simple.txt";
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
    //int length = file.tellg();
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

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, text_file_line);
            size_t pos= text_file_line.find(':');

            if(pos != string::npos)
            {
                keyword_in_text = text_file_line.substr(0, pos);
                stored_keywords_vector.push_back(keyword_in_text);//keywords vector

                stored_lines_vector.push_back(text_file_line.substr(pos + 1));//lines vector after colon extracted

                keyword_map[keyword_in_text] = parse(&keyword_map, stored_lines_vector[loop_count]);
            }
            loop_count++;
        }
        file.close();
    }

    srand(time(0));

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

    Exp* s1 = keyword_map["start"];

    cout << s1->getString() << endl;

  // Return all memory back to OS.
}


#ifndef STARGATE7_H
#define STARGATE7_H

#include <QtWidgets>
#include <cstring>
#include <vector>
#include <regex>

using namespace std;

class Stargate7 {
public:
    Stargate7(QString equation, QString delimiters = "+-*/%=() ");
    Stargate7(string equation, string delimiters = "+-*/%=() ");
    bool parse(string eq, vector<string> &, vector<pair<string, bool>> &);
    bool parse(string);
private:
    void test(string );
    void pass(const string );
    void fail(const string );
    void print(const string );
    bool isValidNumber(string &);
    bool isValidVariable(string &);
    void Tokenize(const string &, vector<string> &, const string &);
    void testNumbers();
    void testVariables();
    void testEquations();

    string m_eq;
    string m_delimiters;
};

#endif // STARGATE7_H

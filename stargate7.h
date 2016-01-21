#ifndef STARGATE7_H
#define STARGATE7_H

#include <QtWidgets>
#include <cstring>
#include <vector>
#include <regex>

class Stargate7 {
public:
    Stargate7(QString equation, QString delimiters);

    bool parse(const string equation, const int row);
private:
    void test(const string );
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

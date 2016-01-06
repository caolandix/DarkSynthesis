#ifndef PHYSSHUNTYARDPARSER_H
#define PHYSSHUNTYARDPARSER_H

#include <QtWidgets>
#include <regex>
#include <stack>
#include <queue>

using namespace std;

class PhysShuntYardParser {

    // contains the operators
    typedef struct {
        char *szbuffer;
        int len, prec, assoc;
    } StrTokenType;

    // Structure for holding patterns of tokens
    typedef struct {
        char *str;
        int assoc, prec;
        regex re;
    } PatternType;

    // Operator association definitions.
    enum Association { ASSOC_NONE, ASSOC_LEFT, ASSOC_RIGHT };

public:
    PhysShuntYardParser();
    ~PhysShuntYardParser();

private:
    bool failShuntingYard(const char *, const char *);
    bool initShuntingYard();
    PhysShuntYardParser::PatternType *match(const char *, QList<PatternType *>, StrTokenType *, const char **);
    bool parse(const char *);
private:
    stack<StrTokenType> m_tokStack;    // stack
    queue<StrTokenType> m_tokQueue;    // queue
    int m_PrecisionBooster;         // prec_booster
    QList<PatternType *> m_PatternArgs;      // pat_arg[]
    QList<PatternType *> m_PatternOperators;    // pat_ops;
    PatternType m_PatternEndOfString;         //  pat_eos
};

#endif // PHYSSHUNTYARDPARSER_H

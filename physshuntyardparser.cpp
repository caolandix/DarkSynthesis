#include "physshuntyardparser.h"

PhysShuntYardParser::PhysShuntYardParser() {


    m_PatternEndOfString = { "", ASSOC_NONE, 0 };

    m_PatternOperators.push_back(new PatternType({ "^\\)", ASSOC_NONE, -1 }));
    m_PatternOperators.push_back(new PatternType({ "^\\*\\*", ASSOC_RIGHT, 3 }));
    m_PatternOperators.push_back(new PatternType({ "^\\^", ASSOC_RIGHT, 3 }));
    m_PatternOperators.push_back(new PatternType({ "^\\*", ASSOC_LEFT, 2 }));
    m_PatternOperators.push_back(new PatternType({ "^/",	ASSOC_LEFT, 2 }));
    m_PatternOperators.push_back(new PatternType({ "^\\+", ASSOC_LEFT, 1 }));
    m_PatternOperators.push_back(new PatternType({ "^-", ASSOC_LEFT, 1 }));
    m_PatternOperators.push_back(new PatternType({ 0 }));

    m_PatternArgs.push_back(new PatternType({ "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?" }));
    m_PatternArgs.push_back(new PatternType({ "^[a-zA-Z_][a-zA-Z_0-9]*" }));
    m_PatternArgs.push_back(new PatternType({ "^\\(", ASSOC_LEFT, -1}));
    m_PatternArgs.push_back(new PatternType({ 0 }));
}

PhysShuntYardParser::~PhysShuntYardParser() {
    foreach (PatternType *pObj, m_PatternOperators)
        delete pObj;
    m_PatternOperators.clear();
    foreach (PatternType *pObj, m_PatternArgs)
        delete pObj;
    m_PatternArgs.clear();
}

bool PhysShuntYardParser::failShuntingYard(const char *s1, const char *s2) {
   qDebug("[Error %s] %s\n", s1, s2);
   return false;
}

bool PhysShuntYardParser::initShuntingYard(void) {
    PatternType *pPattern = NULL;
 /*
    foreach (PatternType *pPattern, m_PatternOperators) {

        // int regcomp(regex_t *restrict preg, const char *restrict pattern, int cflags);
        if (regcomp(&(pPattern -> re), pPattern ->str, REG_NEWLINE | REG_EXTENDED))
            return failShuntingYard("comp", pPattern ->str);
    }
    foreach (PatternType *pPattern, m_PatternArgs) {
        if (regcomp(&(pPattern ->re), pPattern ->str, REG_NEWLINE | REG_EXTENDED))
            return failShuntingYard("comp", pPattern ->str);
    }
    */
    return true;
}

PhysShuntYardParser::PatternType *PhysShuntYardParser::match(
        const char *pszBuffer,
        QList<PatternType *> lstPatterns,
        StrTokenType *pToken,
        const char **ppExpression) {

    cmatch rxMatch;

    while (*pszBuffer == ' ')
        pszBuffer++;
    *ppExpression = pszBuffer;

    if (!*pszBuffer)
        return &m_PatternEndOfString;
/*
    foreach (PatternType *pPattern, lstPatterns) {
        if (pPattern ->str) {

            if (regexec(&(pPattern ->.re), pszBuffer, 1, &rxMatch, REG_NOTEOL))
                continue;
            pToken ->pszBuffer = pszBuffer;
            *ppExpression = pszBuffer + (pToken ->len = rxMatch.rm_eo - rxMatch.rm_so);
            return pPattern + i;
        }
    }
    */
    return NULL;
}

bool PhysShuntYardParser::parse(const char *pszBuffer) {
    PatternType *pPattern = NULL;
    StrTokenType *pToken = NULL, token;

    m_PrecisionBooster = 0;
    while (m_tokQueue.size())
        m_tokQueue.pop();

        /*
        while (*pszBuffer) {

        pPattern = match(pszBuffer, pat_arg, &token, &pszBuffer);
        if (!pPattern || pPattern == &pat_eos)
            return failShuntingYard("parse arg", pszBuffer);

        // Odd logic here. Don't actually stack the parens: don't need to.
        if (pPattern ->prec == -1) {
            m_PrecisionBooster += 100;
            continue;
        }
        tokQueue.push(tok);

        bool bDone = false;
        while (!bDone) {
//re_op:
            pPattern = match(pszBuffer, pat_ops, &token, &pszBuffer);
            if (!pPattern)
                return failShuntingYard("parse op", pszBuffer);

            token.assoc = pPattern ->assoc;
            token.prec = pPattern ->prec;

            if (pPattern ->prec > 0)
                token.prec = pPattern ->prec + m_PrecisionBooster;
            else if (pPattern ->prec == -1) {
                if (m_PrecisionBooster < 100)
                    return failShuntingYard("unmatched )", pszBuffer);
                token.prec = m_PrecisionBooster;
            }

            while (m_tokStack.size()) {
                pToken = stack + l_stack - 1;
                if (!(pToken ->prec == token.prec && pToken ->assoc == ASSOC_LEFT) && pToken ->prec <= token.prec)
                    break;
                m_tokQueue.push(m_tokStack.top());
                m_tokStack.pop();
                qpush(spop());            }

            if (pPattern ->prec == -1) {
                m_PrecisionBooster -= 100;
                continue;       // was: goto reop
            }

            if (!pPattern ->prec) {
                if (m_PrecisionBooster)
                    return failShuntingYard("unmatched (", pszBuffer);
                return true;
            }
            m_tokStack.push(token);
            bDone = false;
        }
    }
    */
    return true;
}

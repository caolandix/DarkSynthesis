#include <ctype.h>
#include "physeqvarextracter.h"

PhysEqVarExtracter::PhysEqVarExtracter() {
    m_Operators = "+-*/^%";
}

bool PhysEqVarExtracter::isOperator(const char c) {
    if (strchr(m_Operators.toUtf8().data(), c))
        return true;
    return false;
}

bool PhysEqVarExtracter::parse(const QString equation, const int row) {
    char *szEquation = equation.trimmed().toUtf8().data();
    char *szBuffer = szEquation;
    char szNumber[255] = { 0 };
    char szVariable[255] = { 0 };
    bool varFound = false;
    bool numFound = false;

    int idxNumber = 0, idxVariable = 0;
    while (*szBuffer) {
        int c = *szBuffer;

        // [a-zA-Z]+[0-9]*
        if (isalpha(c)) {
            szVariable[idxVariable++] = c;
            varFound = true;
            while (*szBuffer) {
                c = *szBuffer;

                // if alphanumeric or an underscore
                if (isalnum(c) || strchr("_", c))
                    szVariable[idxVariable++] = c;
                else {
                    varFound = false;
                    if (c == '(') {

                        // found a function, read until ')' or EOS
                        while (*szBuffer && *szBuffer != ')')
                            szBuffer++;
                        szVariable[0] = '\0';
                        idxVariable = 0;
                    }
                    break;
                }
            }
        }

        // Potential number
        else if (isdigit(c)) {
            szBuffer++;
            while (*szBuffer) {
                c = *szBuffer++;

                // found a decimal
                if (c == '.') {

                }
            }

        }
        else if (isOperator(c)) {
            if (varFound) {
                szVariable[idxVariable] = '\0';
                m_lstVariables.push_back(new VarStruct(szVariable, row));
                varFound = false;
                szVariable[0] = '\0';
            }
            else if (numFound) {
                szNumber[idxNumber] = '\0';
                numFound = false;
                szNumber[0] = '\0';
            }
            else
                szBuffer++;
        }

        // something invalid in the equation
        else
            return false;
    }
    return true;
}

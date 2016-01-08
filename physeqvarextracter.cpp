#include <ctype.h>
#include "physeqvarextracter.h"

PhysEqVarExtracter::PhysEqVarExtracter(const QString equation) {
    m_Equation = equation;
    m_Operators = "+-*/^%()"
}

void PhysEqVarExtracter::parse() {
    char *szEquation = m_Equation.trimmed().toUtf8().data();
    char *szBuffer = szEquation;
    char szNumber[255] = { 0 };
    char szVariable[255] = { 0 };
    bool varFound = false;
    bool numFound = false;

    int idxNumber = 0, idxVariable = 0;
    while (*szBuffer) {
        int c = *szBuffer;

        //
        if (isalpha(c)) {
            szVariable[idxVariable++] = c;
            varFound = true;
            // continue checking to see if it is a variable or a function
            while (*szBuffer) {
                if (m_Operators.contains()
                if (strchr(m_szOperators, c = *szBuffer))
            }

        }

        // Potential number
        else if (isdigit(c)) {
            szBuffer++;
            while (*szBuffer) {
                c = *szBuffer++;

                // found a decimal
                if (c == ".") {

                }
            }

        }

        // Check to see if it's an operator
        else if (strchr(m_szOperators, c))
    }
}

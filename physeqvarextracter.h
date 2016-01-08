#ifndef PHYSEQVAREXTRACTER_H
#define PHYSEQVAREXTRACTER_H

#include <QtWidgets>

class PhysEqVarExtracter {
public:
    PhysEqVarExtracter(const QString);

    typedef struct VarStruct {
        QString var;
        int row;
    };

private:
    QString m_Equation;
    QList<VarStruct> m_lstVariables;
    QString m_Operators;
};

#endif // PHYSEQVAREXTRACTER_H

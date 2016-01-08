#ifndef PHYSEQVAREXTRACTER_H
#define PHYSEQVAREXTRACTER_H

#include <QtWidgets>

class PhysEqVarExtracter {
public:
    PhysEqVarExtracter();

private:
    typedef struct {
        VarStruct(QString var, int row) : m_Variable(var), m_row(row) {}
        QString m_Variable;
        int m_row;
    } VarStruct;

    void parse(const QString, const int);
    bool isOperator(const char);
private:
    QList<VarStruct *> m_lstVariables;
    QString m_Operators;
};

#endif // PHYSEQVAREXTRACTER_H

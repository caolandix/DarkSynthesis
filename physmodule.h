#ifndef PHYSMODULE_H
#define PHYSMODULE_H

#include <QString>
#include <QObject>

class PhysModule : public QObject {
    Q_OBJECT
public:
    int type() const;

    PhysModule(const QString &);
    PhysModule(const PhysModule &);
    virtual ~PhysModule();

    PhysModule& operator=(const PhysModule &);
    QString Name() const { return m_Name; }

private:
    QString m_Name;
};

#endif // PHYSMODULE_H

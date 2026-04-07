#ifndef PHYSPRINTVIEW_H
#define PHYSPRINTVIEW_H

#include <QTableView>
class QPrinter;

class PhysPrintView : public QTableView {
    Q_OBJECT
public:
    PhysPrintView();
public Q_SLOTS:
    void print(QPrinter *printer);
};

#endif // PHYSPRINTVIEW_H


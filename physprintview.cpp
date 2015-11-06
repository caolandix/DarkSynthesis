#ifndef QT_NO_PRINTER
#include <QtPrintSupport/QPrinter>
#endif
#include <QStyleOptionViewItem>

#include "physprintview.h"

PhysPrintView::PhysPrintView() {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PhysPrintView::print(QPrinter *printer) {
#ifndef QT_NO_PRINTER
    resize(printer->width(), printer->height());
    render(printer);
#endif
}

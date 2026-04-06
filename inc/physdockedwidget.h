#ifndef PHYSDOCKEDWIDGET_H
#define PHYSDOCKEDWIDGET_H

#include <QtWidgets>

class PhysDockedWidget : public QDockWidget {
public:
    PhysDockedWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    PhysDockedWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;
signals:
public slots:

};

#endif // PHYSDOCKEDWIDGET_H

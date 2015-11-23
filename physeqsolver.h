#ifndef PHYSEQSOLVER_H
#define PHYSEQSOLVER_H

#include <QMainWindow>
#include <QTableView>
#include <QTableWidgetItem>

class QAction;
class QLabel;
class QLineEdit;
class QToolBar;


class PhysEqSolver : public QTableView {
    Q_OBJECT
public:
    PhysEqSolver(int rows, int cols, QWidget * = NULL);
public slots:
    void updateStatus(QTableWidgetItem *);
    void updateColor(QTableWidgetItem *);
    void updateLineEdit(QTableWidgetItem *);
    void returnPressed();
    void selectColor();
    void selectFont();
    void clear();
    void actionSum();
    void actionSubtract();
    void actionAdd();
    void actionMultiply();
    void actionDivide();

    void actionAppendTimeColumn();
    void actionInsertTimeColumn();
    void actionRemoveTimeColumn();
protected:
    void setupContextMenu();
    void setupContents();
    void setupMenuBar();
    void createActions();
    void actionMath_helper(const QString &, const QString &);
    bool runInputDialog(const QString &, const QString &, const QString &, const QString &,
                        const QString &, QString *, QString *, QString *);
private:
    QToolBar *m_pPhysEqToolBar;
    QAction *m_pActColor;
    QAction *m_pActFont;
    QAction *m_pActClear;
    QAction *m_pActAppendTimeColumn;
    QAction *m_pActInsertTimeColumn;
    QAction *m_pActRemoveTimeColumn;
    QAction *m_pActCellSum;
    QAction *m_pActCellAdd;
    QAction *m_pActCellSubtract;
    QAction *m_pActCellMultiply;
    QAction *m_pActCellDivide;

    QLabel *m_pCellLabel;
    QTableWidget *m_pTable;
    QLineEdit *m_pFormulaInput;

};

void decode_pos(const QString &, int *, int *);
QString encode_pos(int, int );

#endif // PHYSEQSOLVER_H

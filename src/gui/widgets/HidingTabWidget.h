#ifndef HIDINGTABWIDGET_H
#define HIDINGTABWIDGET_H

#include <QObject>
#include <QTabWidget>

/** A widget that hides itself when it has no tabs. */
class HidingTabWidget : public QTabWidget {
    Q_OBJECT
    using Super = QTabWidget;

public:
    explicit HidingTabWidget(QWidget *parent = nullptr) : Super(parent) {};

    void tabInserted(int index) override;
    void tabRemoved(int index) override;
};

#endif // HIDINGTABWIDGET_H

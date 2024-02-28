#pragma once
#include <qwidget.h>
#include <vector>
#include "Service.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>
#include <qmessagebox.h>

class GUI :
    public QWidget
{
    Q_OBJECT

private:
    Service service;

public:
    GUI(const Service& service, QWidget* parent = 0);

    void initGUI();

private:
    QListWidget* dogsListadmin;
    QLineEdit* nameEdit;
    QLineEdit* breedEdit;
    QLineEdit* ageEdit;
    QLineEdit* idEdit;
    QLineEdit* photographEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* exitButton;
    QPushButton* updateButton;

    QListWidget* dogsListuser;
    QListWidget* adoptionList;
    QPushButton* adoptButton;
    QPushButton* nextButton;
    QPushButton* exitButton2;
    QTabWidget* tabWidget;
    void populateList();
    void connectSignalsAndSlots();

    void listItemChanged();
    int getSelectedIndex();
    void UpdateDog();

signals:
    void mySignal();
};

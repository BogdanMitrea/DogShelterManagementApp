#pragma once
#include "Service.h"
#include <QtWidgets/QMainWindow>
#include "ui_a89MitreaBogdan.h"
#include <QPIxmap>
#include <qmessagebox.h>

class a89MitreaBogdan : public QMainWindow
{
    Q_OBJECT

public:
    a89MitreaBogdan(Service& service,QWidget *parent = nullptr);
    ~a89MitreaBogdan();

private:
    Service service;
    Ui::a89MitreaBogdanClass ui;
    void populate_list();
    void display_photo(string path);
    void connectSignalsAndSlots();
    void listItemChanged();
    void updateCurrentDog();
    int currentDogindex = 0;
    string current_using_list;
    vector<Dogs> filtered_breed_age_dogs;

public slots:
    void addDog();
    void removeDog();
    void updateDog();
    void SaveAndExit();
    void displayCurrentDog();
    void nextDog();
    void previousDog();
    void adoptDog();
    void filterDogs();
    void goFilterDogs();
    void showCSV();
};

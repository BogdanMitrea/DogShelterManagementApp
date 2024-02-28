#include "GUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <qlabel.h>

GUI::GUI(const Service& service, QWidget* parent) :
	QWidget{ parent }, service{ service }
{
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
}

void GUI::initGUI()
{
	QTabWidget* tabWidget = new QTabWidget(this);
	QHBoxLayout* mainlayout = new QHBoxLayout{ this };

	mainlayout->addWidget(tabWidget);

	QWidget* tabPage1 = new QWidget();
	tabWidget->addTab(tabPage1, "Admin Mode");

	QWidget* tabPage2 = new QWidget();
	tabWidget->addTab(tabPage2, "User Mode");

	QHBoxLayout* layoutadmin = new QHBoxLayout{ tabPage1 };
	QHBoxLayout* layoutuser = new QHBoxLayout{ tabPage2 };

	dogsListadmin = new QListWidget{};
	
	layoutadmin->addWidget(dogsListadmin);
	
	QVBoxLayout* dogsDataLayout = new QVBoxLayout{};
	
	layoutadmin->addLayout(dogsDataLayout);

	QFormLayout* dogInfoLayout = new QFormLayout{};
	QLabel* nameLabel = new QLabel{ "&Name" };
	nameEdit = new QLineEdit{};
	nameLabel->setBuddy(nameEdit);

	QLabel* breedLabel = new QLabel{ "&Breed" };
	breedEdit = new QLineEdit{};
	breedLabel->setBuddy(breedEdit);

	QLabel* ageLabel = new QLabel{ "&Age" };
	ageEdit = new QLineEdit{};
	ageLabel->setBuddy(ageEdit);

	QLabel* idLabel = new QLabel{ "&ID" };
	idEdit = new QLineEdit{};
	idLabel->setBuddy(idEdit);

	QLabel* photographLabel = new QLabel{ "&Photograph" };
	photographEdit = new QLineEdit{};
	photographLabel->setBuddy(photographEdit);

	dogInfoLayout->addRow(idLabel, idEdit);
	dogInfoLayout->addRow(nameLabel, nameEdit);
	dogInfoLayout->addRow(breedLabel, breedEdit);
	dogInfoLayout->addRow(ageLabel, ageEdit);
	dogInfoLayout->addRow(photographLabel, photographEdit);

	dogsDataLayout->addLayout(dogInfoLayout);

	QHBoxLayout* buttonsLayout = new QHBoxLayout{};
	addButton = new QPushButton{ "Add" };
	removeButton = new QPushButton{ "Remove" };
	exitButton = new QPushButton{ "Exit" };
	updateButton = new QPushButton{ "Update" };

	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(removeButton);
	buttonsLayout->addWidget(updateButton);
	buttonsLayout->addWidget(exitButton);

	dogsDataLayout->addLayout(buttonsLayout);

	//For user mode
	dogsListuser = new QListWidget{};
	adoptionList = new QListWidget{};

	layoutuser->addWidget(dogsListuser);
	QVBoxLayout* dogsdisplayLayout = new QVBoxLayout{};
	layoutuser->addLayout(dogsdisplayLayout);
	layoutuser->addWidget(adoptionList);

	QFormLayout* AdoptionInfoLayout = new QFormLayout{};

	QLabel* current_nameLabel = new QLabel{ "Name:" };
	QLabel* current_breedLabel = new QLabel{ "Breed:" };
	QLabel* current_ageLabel = new QLabel{ "Age:" };
	QLabel* current_idLabel = new QLabel{ "ID:" };
	QLabel* current_photographLabel = new QLabel{ "Photograph:" };

	AdoptionInfoLayout->addWidget(current_idLabel);
	AdoptionInfoLayout->addWidget(current_nameLabel);
	AdoptionInfoLayout->addWidget(current_breedLabel);
	AdoptionInfoLayout->addWidget(current_ageLabel);
	AdoptionInfoLayout->addRow(current_photographLabel);
	dogsdisplayLayout->addLayout(AdoptionInfoLayout);

	QHBoxLayout* buttonsLayoutuser = new QHBoxLayout{};
	exitButton2 = new QPushButton{ "Exit" };
	nextButton = new QPushButton{ "Next" };
	adoptButton = new QPushButton{ "Adopt" };
	buttonsLayoutuser->addWidget(adoptButton);
	buttonsLayoutuser->addWidget(nextButton);
	buttonsLayoutuser->addWidget(exitButton2);
	dogsdisplayLayout->addLayout(buttonsLayoutuser);
}

void GUI::populateList()
{
	dogsListadmin->clear();

	for (Dogs dog : this->service.get_all_dogs_service())
		dogsListadmin->addItem(QString::fromStdString(dog.toString()));

	dogsListadmin->setCurrentRow(0);

	dogsListuser->clear();

	for (Dogs dog : this->service.get_all_dogs_service())
		dogsListuser->addItem(QString::fromStdString(dog.toString()));

	dogsListuser->setCurrentRow(0);
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(dogsListadmin, &QListWidget::itemSelectionChanged, this, &GUI::listItemChanged);

	QObject::connect(addButton, &QPushButton::clicked,
		this, [&]() {
			try {
				this->service.add_dog_service(idEdit->text().toStdString(), breedEdit->text().toStdString(), nameEdit->text().toStdString(), ageEdit->text().toStdString(), photographEdit->text().toStdString());
			}
			catch (RepositoryException& repo_exception)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(repo_exception.what()));
				return;
			}
			catch (ValidationError& validation_error)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(validation_error.what()));
				return;
			}
			catch (invalid_argument& argument)
			{
				QMessageBox::critical(this, "Error", QString::fromStdString(argument.what()));
				return;
			}
			populateList();
			dogsListadmin->setCurrentRow(this->service.get_size_service() - 1);
		});

	QObject::connect(removeButton, &QPushButton::clicked,
		this, [&]() {
			QListWidgetItem* selectedItem = dogsListadmin->currentItem();
			if (selectedItem) {
				try
				{
					string idtoremove = idEdit->text().toStdString();
					dogsListadmin->takeItem(dogsListadmin->row(selectedItem));
					dogsListuser->takeItem(dogsListadmin->row(selectedItem));
					delete selectedItem;
					this->service.remove_dog_service(idtoremove);
				}
				catch (RepositoryException& repo_exception)
				{
					QMessageBox::critical(this, "Error", QString::fromStdString(repo_exception.what()));
					return;
				}
				catch (ValidationError& validation_error)
				{
					QMessageBox::critical(this, "Error", QString::fromStdString(validation_error.what()));
					return;
				}
				catch (invalid_argument& argument)
				{
					QMessageBox::critical(this, "Error", QString::fromStdString(argument.what()));
					return;
				}
			}
		});

	QObject::connect(exitButton, &QPushButton::clicked,
		this, [&]() {
			this->service.save_to_file("Dogs_List.txt");
			QCoreApplication::quit();
		});

	QObject::connect(exitButton2, &QPushButton::clicked,
		this, [&]() {
			this->service.save_to_file("Dogs_List.txt");
			QCoreApplication::quit();
		});

	QObject::connect(updateButton, &QPushButton::clicked, this, &GUI::UpdateDog);

	emit mySignal();
}

void GUI::listItemChanged()
{
	int index = getSelectedIndex();
	if (index < 0)
		return;

	Dogs dog = this->service.get_dog__position_serivce(index);
	nameEdit->setText(QString::fromStdString(dog.Get_Name()));
	breedEdit->setText(QString::fromStdString(dog.Get_Breed()));
	ageEdit->setText(QString::fromStdString(to_string(dog.Get_Age())));
	idEdit->setText(QString::fromStdString(to_string(dog.Get_id())));
	photographEdit->setText(QString::fromStdString(dog.Get_Photograph()));
}

int GUI::getSelectedIndex()
{
	int currentRow = dogsListadmin->currentRow();

	return currentRow;
}

void GUI::UpdateDog()
{
	try
	{
		this->service.update_dog_service(idEdit->text().toStdString(), breedEdit->text().toStdString(), nameEdit->text().toStdString(), ageEdit->text().toStdString(), photographEdit->text().toStdString());
	}
	catch (RepositoryException& repo_exception)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(repo_exception.what()));
		return;
	}
	catch (ValidationError& validation_error)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(validation_error.what()));
		return;
	}
	catch (invalid_argument& argument)
	{
		QMessageBox::critical(this, "Error", QString::fromStdString(argument.what()));
		return;
	}
	populateList();
}
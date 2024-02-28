#include "a89MitreaBogdan.h"

a89MitreaBogdan::a89MitreaBogdan(Service& service,QWidget *parent)
    : QMainWindow(parent)
{
    this->service = service;
    ui.setupUi(this);
    this->populate_list();
	this->connectSignalsAndSlots();
	this->current_using_list = "main";
	this->displayCurrentDog();
	this->ui.filter_ageEdit->hide();
	this->ui.filter_breedEdit->hide();
	this->ui.age_filterLabel->hide();
	this->ui.breed_filterLabel->hide();
	this->ui.goFilterButton->hide();
	
}

a89MitreaBogdan::~a89MitreaBogdan()
{}

void a89MitreaBogdan::populate_list()
{
    this->ui.doglistadmin->clear();

    for (Dogs dog : this->service.get_all_dogs_service())
        this->ui.doglistadmin->addItem(QString::fromStdString(dog.toString()));

    this->ui.doglistadmin->setCurrentRow(0);
}

void a89MitreaBogdan::display_photo(string path)
{
    QPixmap* pixmap = new QPixmap{ QString::fromStdString(path) };
	if(pixmap->isNull())
	{
		QPixmap* pixmap2 = new QPixmap{ QString::fromStdString("C:/OOP/a89-MitreaBogdan/DogsPhotos/imagenotavailable.png") };
		QPixmap scaledPixmap = pixmap2->scaled(this->ui.photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		this->ui.photoLabel->setPixmap(scaledPixmap);
		return;
	}
    QPixmap scaledPixmap = pixmap->scaled(this->ui.photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->ui.photoLabel->setPixmap(scaledPixmap);
}

void a89MitreaBogdan::connectSignalsAndSlots()
{
	QObject::connect(this->ui.doglistadmin, &QListWidget::itemSelectionChanged, this, &a89MitreaBogdan::listItemChanged);
}

void a89MitreaBogdan::listItemChanged()
{
	int index = this->ui.doglistadmin->currentRow();
	if (index < 0)
		return;

	Dogs dog = this->service.get_dog__position_serivce(index);
	this->ui.nameEdit->setText(QString::fromStdString(dog.Get_Name()));
	this->ui.breedEdit->setText(QString::fromStdString(dog.Get_Breed()));
	this->ui.ageEdit->setText(QString::fromStdString(to_string(dog.Get_Age())));
	this->ui.idEdit->setText(QString::fromStdString(to_string(dog.Get_id())));
	this->ui.photographEdit->setText(QString::fromStdString(dog.Get_Photograph()));
}

void a89MitreaBogdan::updateCurrentDog()
{
	Dogs currentdog;
	if (this->current_using_list == "main")
		currentdog = this->service.get_all_dogs_service().at(this->currentDogindex);
	else
		currentdog = this->filtered_breed_age_dogs.at(this->currentDogindex);
	this->ui.ageLabel->setText(QString::fromStdString(to_string(currentdog.Get_Age())));
	this->ui.breedLabel->setText((QString::fromStdString(currentdog.Get_Breed())));
	this->ui.nameLabel->setText((QString::fromStdString(currentdog.Get_Name())));
	this->display_photo(currentdog.Get_Photograph());
}

void a89MitreaBogdan::displayCurrentDog()
{
	this->current_using_list = "main";
	this->currentDogindex = 0;
	Dogs currentdog = this->service.get_all_dogs_service().at(this->currentDogindex);
	this->ui.ageLabel->setText(QString::fromStdString(to_string(currentdog.Get_Age())));
	this->ui.breedLabel->setText((QString::fromStdString(currentdog.Get_Breed())));
	this->ui.nameLabel->setText((QString::fromStdString(currentdog.Get_Name())));
	this->display_photo(currentdog.Get_Photograph());
}

void a89MitreaBogdan::nextDog()
{
	if (this->current_using_list == "main")
	{
		if (this->currentDogindex < this->service.get_all_dogs_service().size() - 1)
			this->currentDogindex++;
		else
			this->currentDogindex = 0;
	}
	else
	{
		if (this->currentDogindex < this->filtered_breed_age_dogs.size() - 1)
			this->currentDogindex++;
		else
			this->currentDogindex = 0;
	}
	this->updateCurrentDog();
}

void a89MitreaBogdan::previousDog()
{
	if (this->current_using_list == "main")
	{
		if (this->currentDogindex > 0)
			this->currentDogindex--;
		else
			this->currentDogindex = this->service.get_all_dogs_service().size() - 1;
	}
	else
	{
		if (this->currentDogindex > 0)
			this->currentDogindex--;
		else
			this->currentDogindex = this->filtered_breed_age_dogs.size() - 1;
	}
	this->updateCurrentDog();
}

void a89MitreaBogdan::adoptDog()
{
	Dogs dog;
	if (this->current_using_list == "main")
		dog = this->service.get_all_dogs_service().at(this->currentDogindex);
	else
		dog = this->filtered_breed_age_dogs.at(this->currentDogindex);
	bool result=this->service.add_dog_user_list(dog);
	if (result == true)
		this->ui.adoption_list->addItem(QString::fromStdString(dog.toString()));
	else
		QMessageBox::critical(this, "Error", QString::fromStdString(dog.Get_Name())+" is already on your adoption list");
	this->nextDog();
}

void a89MitreaBogdan::filterDogs()
{
	this->ui.filter_ageEdit->show();
	this->ui.filter_breedEdit->show();
	this->ui.age_filterLabel->show();
	this->ui.breed_filterLabel->show();
	this->ui.goFilterButton->show();
}

void a89MitreaBogdan::goFilterDogs()
{
	this->ui.filter_ageEdit->hide();
	this->ui.filter_breedEdit->hide();
	this->ui.age_filterLabel->hide();
	this->ui.breed_filterLabel->hide();
	this->ui.goFilterButton->hide();
	this->filtered_breed_age_dogs = this->service.filter_breed_and_age(this->ui.filter_breedEdit->text().toStdString(), stoi(this->ui.filter_ageEdit->text().toStdString()));
	if (this->filtered_breed_age_dogs.size() == 0)
	{
		QMessageBox::critical(this, "Error", "There are no dogs with the specified requirements");
		return;
	}
	this->current_using_list = "filtered";
	this->currentDogindex = 0;
	this->updateCurrentDog();
}

void a89MitreaBogdan::showCSV()
{
	this->service.display_adoption_list();
}

void a89MitreaBogdan::removeDog()
{
	QListWidgetItem* selectedItem = this->ui.doglistadmin->currentItem();
	if (selectedItem) {
		try
		{
			string idtoremove = this->ui.idEdit->text().toStdString();
			this->service.remove_dog_service(idtoremove);
			
			this->ui.doglistadmin->takeItem(this->ui.doglistadmin->row(selectedItem));
			this->ui.doglistadmin->setCurrentRow(0);
			
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
}

void a89MitreaBogdan::updateDog()
{
	try
	{
		this->service.update_dog_service(this->ui.idEdit->text().toStdString(), this->ui.breedEdit->text().toStdString(), this->ui.nameEdit->text().toStdString(), this->ui.ageEdit->text().toStdString(), this->ui.photographEdit->text().toStdString());
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
	this->populate_list();
}

void a89MitreaBogdan::SaveAndExit()
{
		this->service.save_to_file("Dogs_List.txt");
		QCoreApplication::quit();
}

void a89MitreaBogdan::addDog()
{
	try
	{
		this->service.add_dog_service(this->ui.idEdit->text().toStdString(), this->ui.breedEdit->text().toStdString(), this->ui.nameEdit->text().toStdString(), this->ui.ageEdit->text().toStdString(), this->ui.photographEdit->text().toStdString());
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
	this->populate_list();
	this->ui.doglistadmin->setCurrentRow(this->service.get_size_service() - 1);
}
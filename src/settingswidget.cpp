#include "settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QDialog(parent)
{
    this->setLayout(new QVBoxLayout);

    CreateSaveMusicBox();
    CreateReplaceMusicBox();

    btnSave = new QPushButton("Save", this);
    btnCancel = new QPushButton("Cancel", this);

    QHBoxLayout * layButtons = new QHBoxLayout(this);
    layButtons->addWidget(btnSave);
    layButtons->addWidget(btnCancel);

    QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(btnSave, SIGNAL(clicked()), this, SLOT(BtnSave()));

    this->layout()->addItem(layButtons);

    SetCurrentSettings();
}


void SettingsWidget::CreateSaveMusicBox()
{
    QGroupBox * gbSaveMusic = new QGroupBox("Save Music Options", this);
    QLabel * lblSaveMusic = new QLabel("Path:", gbSaveMusic);
    leSaveMusicPath = new QLineEdit(gbSaveMusic);
    btnBrowserPath = new QPushButton("Browser", gbSaveMusic);

    gbSaveMusic->setLayout(new QHBoxLayout);
    gbSaveMusic->layout()->addWidget(lblSaveMusic);
    gbSaveMusic->layout()->addWidget(leSaveMusicPath);
    gbSaveMusic->layout()->addWidget(btnBrowserPath);
    this->layout()->addWidget(gbSaveMusic);

    QObject::connect(btnBrowserPath, SIGNAL(clicked()), this, SLOT(SetSaveMusicPath()));
}

void SettingsWidget::CreateReplaceMusicBox()
{
    QGroupBox* gbReplaceMusic = new QGroupBox("Replace Music Options", this);
    chbReplaceMusic = new QCheckBox("Replace Music?", gbReplaceMusic);
    gbReplaceMusic->setLayout(new QHBoxLayout);
    gbReplaceMusic->layout()->addWidget(chbReplaceMusic);
    this->layout()->addWidget(gbReplaceMusic);
}

void SettingsWidget::SetCurrentSettings()
{
    /*
     *  Read and set path where the file will be saved
     */
    std::string path = Settings::init()->getJson()["settings"].get("save_path", "./").asString();
    leSaveMusicPath->setText(QString::fromStdString(path));

    /*
     * Set flag to (not) replace existing files
     */
    bool replaceMusic = Settings::init()->getJson()["settings"].get("replace_existing_files", false).asBool();
    chbReplaceMusic->setChecked(replaceMusic);
}

void SettingsWidget::SetSaveMusicPath()
{
    QString dirname = QFileDialog::getExistingDirectory(this, "Select Save Directory", QDir::currentPath());
    leSaveMusicPath->setText(dirname+"/");
}

void SettingsWidget::BtnSave()
{
    // settings
    std::string save_path = leSaveMusicPath->text().toStdString();
    bool replace_existing_files = chbReplaceMusic->isChecked();

    Settings::init()->getJson()["settings"]["save_path"] = save_path;
    Settings::init()->getJson()["settings"]["replace_existing_files"] = replace_existing_files;
    Settings::init()->save();

    this->close();
}


















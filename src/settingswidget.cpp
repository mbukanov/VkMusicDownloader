#include "settingswidget.h"

SettingsWidget::SettingsWidget(VKapi* vk, QWidget *parent) :
    QDialog(parent)
{
    if(vk == NULL)
    {
        assert("VKapi is NULL!");
        std::cout<<"VKapi is NULL!"<<std::endl;
        exit(0);
    }

    _vk = vk;
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
    std::string SettingsFileName = "settings.json";
    std::string settingsFileBuffer = FileOperations::readFromFile(SettingsFileName);
    Json::Value root;
    Json::Reader reader;
    reader.parse(settingsFileBuffer, root);

    /*
     *  Read and set path where the file will be saved
     */
    std::string path = root["settings"].get("save_path", "./").asString();
    leSaveMusicPath->setText(QString::fromStdString(path));

    /*
     * Set flag to (not) replace existing files
     */
    bool replaceMusic = root["settings"].get("replace_existing_files", false).asBool();
    chbReplaceMusic->setChecked(replaceMusic);

    _vk->setSaveFileDirectory(path);
    _vk->setReplaceFiles(replaceMusic);
    _vk->setFilesInDirectory();
}

void SettingsWidget::SetSaveMusicPath()
{
    QString dirname = QFileDialog::getExistingDirectory(this, "Select Save Directory", QDir::currentPath());
    leSaveMusicPath->setText(dirname+"/");
}

void SettingsWidget::BtnSave()
{
    std::string save_path = leSaveMusicPath->text().toStdString();
    bool replace_existing_files = chbReplaceMusic->isChecked();

    std::string settingsFileName = "settings.json";
    Json::Value root;

    root["settings"]["save_path"] = save_path;
    root["settings"]["replace_existing_files"] = replace_existing_files;

    std::string settings = Json::StyledWriter().write(root);
    FileOperations::writeToFile(settingsFileName, settings);

    _vk->setSaveFileDirectory(save_path);
    _vk->setReplaceFiles(replace_existing_files);

    this->close();
}





#include "filter.h"
#include "ui_filter.h"

Filter::Filter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Filter)
{
    ui->setupUi(this);
    setFixedSize(size());

    ui->name_edit->setEnabled(false);
    ui->description_edit->setEnabled(false);
    ui->dateEdit1->setEnabled(false);
    ui->dateEdit_2->setEnabled(false);
    ui->comboBox->setEnabled(false);


    ui->dateEdit1->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit_2->setDateTime(QDateTime::currentDateTime());


    QString item1 = "Показывать выполненные";
    QString item2 = "Показывать невыполненные";


    ui->comboBox->addItem(item1);
    ui->comboBox->addItem(item2);

    setWindowTitle("Установка фильтров");
}

Filter::~Filter()
{
    delete ui;
}

bool Filter::nameFilter(const QString &name)
{
    if(!isCheckboxChecked(ui->name_checkBox)){
        return true;
    }
    return name.toLower().contains(ui->name_edit->text().toLower());
}

bool Filter::descriptionFilter(const QString &description)
{
    if(!isCheckboxChecked(ui->description_checkBox)){
        return true;
    }
    return description.toLower().contains(ui->description_edit->toPlainText().toLower());
}

bool Filter::dateFilter(const QDateTime &date)
{
    if(!isCheckboxChecked(ui->date_checkBox)){
        return true;
    }
    QDateTime first = ui->dateEdit1->dateTime();
    QDateTime second = ui->dateEdit_2->dateTime();

    return date >= first && date <= second;
}

bool Filter::stateFilter(bool state)
{
    if(!isCheckboxChecked(ui->state_checkBox)){
        return true;
    }

    return (ui->comboBox->currentIndex() == 0) ? state : !state;
}



void Filter::on_name_checkBox_checkStateChanged(const Qt::CheckState &state)
{
    ui->name_edit->setEnabled(state == Qt::Checked);
}


void Filter::on_description_checkBox_checkStateChanged(const Qt::CheckState &state)
{
    ui->description_edit->setEnabled(state == Qt::Checked);
}

void Filter::on_date_checkBox_checkStateChanged(const Qt::CheckState &state)
{
    ui->dateEdit1->setEnabled(state == Qt::Checked);
    ui->dateEdit_2->setEnabled(state == Qt::Checked);
}

void Filter::on_state_checkBox_checkStateChanged(const Qt::CheckState &state)
{
    ui->comboBox->setEnabled(state == Qt::Checked);
}


bool Filter::isCheckboxChecked(QCheckBox *checkbox)
{
    return checkbox->checkState() == Qt::Checked;
}


void Filter::on_apply_bt_clicked()
{
    TaskFilterFunctor filter = [this](const Task& task){
        return nameFilter(task.name) && descriptionFilter(task.description)
               && dateFilter(task.deadline) && stateFilter(task.state);
    };

    emit aply(filter);
}


void Filter::on_cancel_bt_clicked()
{
    hide();
}


void Filter::on_reset_bt_clicked()
{
    ui->name_checkBox->setChecked(false);
    ui->description_checkBox->setChecked(false);
    ui->date_checkBox->setChecked(false);
    ui->state_checkBox->setChecked(false);

    TaskFilterFunctor filter = [](const Task&){
        return true;
    };

    emit aply(filter);
}


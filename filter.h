#ifndef FILTER_H
#define FILTER_H

#include <QWidget>
#include <functional>
#include <QCheckBox>
#include "task.h"


namespace Ui {
class Filter;
}

class Filter : public QWidget
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = nullptr);
    ~Filter();

    using TaskFilterFunctor = std::function<bool(const Task&)>;

    bool nameFilter(const QString& name);
    bool descriptionFilter(const QString& description);
    bool dateFilter(const QDateTime& date);
    bool stateFilter(bool state);

signals:
    void aply(TaskFilterFunctor filter);

private slots:
    void on_name_checkBox_checkStateChanged(const Qt::CheckState &state);

    void on_description_checkBox_checkStateChanged(const Qt::CheckState &state);

    void on_date_checkBox_checkStateChanged(const Qt::CheckState &state);

    void on_apply_bt_clicked();

    void on_cancel_bt_clicked();

    void on_state_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_reset_bt_clicked();

private:
    Ui::Filter *ui;

    bool isCheckboxChecked(QCheckBox* checkbox);

    QStringList comboBoxStrings;

};

#endif // FILTER_H

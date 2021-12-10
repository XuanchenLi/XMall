#ifndef PICLINEEDIT_H
#define PICLINEEDIT_H

#include <QWidget>

namespace Ui {
class PicLineEdit;
}

class PicLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit PicLineEdit(QWidget *parent = nullptr);
    ~PicLineEdit();
    void setPic(QString p);
private:
    Ui::PicLineEdit *ui;
    QString picPath;
};

#endif // PICLINEEDIT_H

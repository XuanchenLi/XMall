#include "piclineedit.h"
#include "ui_piclineedit.h"
#include <QLabel>
PicLineEdit::PicLineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicLineEdit)
{
    ui->setupUi(this);

}

PicLineEdit::~PicLineEdit()
{
    delete ui;
}

void PicLineEdit::setPic(QString p)
{
    this->picPath = p;
    QImage img;
    img.load (p);
    QPixmap pixmap(QPixmap::fromImage(img));
    QLabel* logoLabel = this->findChild<QLabel*>("picLabel");
    pixmap = pixmap.scaled(28,28);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setPixmap(pixmap);
}

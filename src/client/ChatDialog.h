#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

class BabelWindow;

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(BabelWindow &, QWidget *parent = 0);
    ~ChatDialog();

    void     writeMsg(const QString &);

protected:
    void    closeEvent(QCloseEvent *);

private slots:
    void on_btn_send_clicked();

private:
    BabelWindow     &_main;
    Ui::ChatDialog  *ui;
};

#endif // CHATDIALOG_H

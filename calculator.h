
#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

#include <button.h>


class Calculator : public QWidget {

    // To use signals & slots
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void pointClicked();
    void changeSignClicked();
    void equalClicked();

    void binaryOperatorClicked();
    void unaryOperatorClicked();

    void backspaceClicked();
    void clear();
    void clearAll();

    void clearMemory();
    void readMemory();
    void addMemory();
    void subMemory();

private:
    Button* createButton(const QString& sign, const char* slotFunction);
    Button* getClickedButton();
    void calculate();
    void abortOperation();

private:
    QLineEdit*   m_display_up;
    QLabel*      m_display_sign;
    QLineEdit*   m_display_down;
    QGridLayout* m_gridLayout;

    static const int DIGITS_COUNT    = 10;

    const QString m_initial_value    = "0";
    const QString m_error_value      = "###";

    const QString m_change_sign      = QChar(0x000000b1);
    const QString m_point_sign       = ".";

    const QString m_plus_sign        = "+";
    const QString m_minus_sign       = "—";
    const QString m_times_sign       = QChar(0x000000D7);
    const QString m_division_sign    = QChar(0x000000F7);

    const QString m_equal_sign       = "=";

    const QString m_sqrt_sign        = QChar(0x221A) + 'x';
    const QString m_sqpow_sign       = 'x' + QChar(0x000000b2);
    const QString m_reciprocal_sign  = "1/x"; // inverse

    const QString m_log_sign         = "log";
    const QString m_tenpow_sign      = 49 + QChar(48) + QChar(0x0000207F);
    const QString m_power_sign       = 'x' + QChar(0x0000207F);

    const QString m_allClean_sign    = "AC";
    const QString m_cleanEntry_sign  = "CE";
    const QString m_backspace_sign   = "<-";

    const QString m_memoryClean_sign = "MC";
    const QString m_memoryRead_sign  = "MR";
    const QString m_memoryAdd_sign   = "M+";
    const QString m_memorySub_sign   = "M-";

    double m_memorySum = 0.0; // memory buffer
};


#endif // CALCULATOR_H


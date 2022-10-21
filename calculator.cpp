
#include <QDebug>
#include <QtMath>

#include "calculator.h"


Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    // Allocate memory on the heap
    m_display_up   = new QLineEdit();
    m_display_sign = new QLabel();
    m_display_down = new QLineEdit();
    m_gridLayout   = new QGridLayout();

    // Setup display settings
    m_display_up  ->setAlignment(Qt::AlignRight);
    m_display_sign->setAlignment(Qt::AlignRight);
    m_display_down->setAlignment(Qt::AlignRight);

    m_display_up  ->setReadOnly(true);
    m_display_down->setReadOnly(true);

    m_display_up  ->setMaxLength(15);
    m_display_down->setMaxLength(15);

    // Setup widget & display symbol sizes
    QFont font = this->font();
    int symbolSize = font.pointSize();

    font.setPointSize(symbolSize + 4);
    setFont(font);

    font.setPointSize(symbolSize + 6);
    m_display_up->setFont(font);

    font.setPointSize(symbolSize + 6);
    m_display_sign->setFont(font);

    font.setPointSize(symbolSize + 10);
    m_display_down->setFont(font);

    // Initial display value
    m_display_down->setText(m_initial_value);

    // Create all calculator buttons
    Button* m_digitButtons[DIGITS_COUNT];

    for (int i = 0; i < DIGITS_COUNT; ++i)
    {
        m_digitButtons[i]     = createButton(QString::number(i), SLOT(digitClicked()));
    }

    Button *changeButton      = createButton(m_change_sign,      SLOT(changeSignClicked()));
    Button *pointButton       = createButton(m_point_sign,       SLOT(pointClicked()));

    Button *plusButton        = createButton(m_plus_sign,        SLOT(binaryOperatorClicked()));
    Button *minusButton       = createButton(m_minus_sign,       SLOT(binaryOperatorClicked()));
    Button *timesButton       = createButton(m_times_sign,       SLOT(binaryOperatorClicked()));
    Button *divisionButton    = createButton(m_division_sign,    SLOT(binaryOperatorClicked()));

    Button *equalButton       = createButton(m_equal_sign,       SLOT(equalClicked()));

    Button *sqrtButton        = createButton(m_sqrt_sign,        SLOT(unaryOperatorClicked()));
    Button *sqpowButton       = createButton(m_sqpow_sign,       SLOT(unaryOperatorClicked()));
    Button *reciprocalButton  = createButton(m_reciprocal_sign,  SLOT(unaryOperatorClicked()));

    Button *logButton         = createButton(m_log_sign,         SLOT(unaryOperatorClicked()));
    Button *tenpowButton      = createButton(m_tenpow_sign,      SLOT(unaryOperatorClicked()));
    Button *powerButton       = createButton(m_power_sign,       SLOT(binaryOperatorClicked()));

    Button *allCleanButton    = createButton(m_allClean_sign,    SLOT(clearAll()));
    Button *clearEntryButton  = createButton(m_cleanEntry_sign,  SLOT(clear()));
    Button *backspaceButton   = createButton(m_backspace_sign,   SLOT(backspaceClicked()));

    Button *memoryCleanButton = createButton(m_memoryClean_sign, SLOT(clearMemory()));
    Button *memoryReadButton  = createButton(m_memoryRead_sign,  SLOT(readMemory()));
    Button *memoryAddButton   = createButton(m_memoryAdd_sign,   SLOT(addMemory()));
    Button *memorySubButton   = createButton(m_memorySub_sign,   SLOT(subMemory()));

    // Set the widget to a fixed size so the layout / window cannot be resized
    m_gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    // Add display & buttons widgets to grid layout: row, column, rowSpan, columnSpan
    m_gridLayout->addWidget(m_display_up,      0, 0, 1, 6);
    m_gridLayout->addWidget(m_display_sign,    1, 5, 1, 1);
    m_gridLayout->addWidget(m_display_down,    2, 0, 1, 6);

    m_gridLayout->addWidget(logButton,         3, 0);
    m_gridLayout->addWidget(tenpowButton,      3, 1);
    m_gridLayout->addWidget(powerButton,       3, 2);

    m_gridLayout->addWidget(allCleanButton,    3, 3);
    m_gridLayout->addWidget(clearEntryButton,  3, 4);
    m_gridLayout->addWidget(backspaceButton,   3, 5);

    m_gridLayout->addWidget(memoryCleanButton, 4, 0);
    m_gridLayout->addWidget(memoryReadButton,  5, 0);
    m_gridLayout->addWidget(memoryAddButton,   6, 0);
    m_gridLayout->addWidget(memorySubButton,   7, 0);

    m_gridLayout->addWidget(divisionButton,    4, 4);
    m_gridLayout->addWidget(timesButton,       5, 4);
    m_gridLayout->addWidget(minusButton,       6, 4);
    m_gridLayout->addWidget(plusButton,        7, 4);

    m_gridLayout->addWidget(sqrtButton,        4, 5);
    m_gridLayout->addWidget(sqpowButton,       5, 5);
    m_gridLayout->addWidget(reciprocalButton,  6, 5);
    m_gridLayout->addWidget(equalButton,       7, 5);

    m_gridLayout->addWidget(changeButton,      7, 1);
    m_gridLayout->addWidget(pointButton,       7, 3);
    m_gridLayout->addWidget(m_digitButtons[0], 7, 2);

    int rowOffset = 6;
    int columnOffset = 1;

    int rows = rowOffset - 3;
    int columns = columnOffset + 3;

    int i = 0;

    for (int row = rowOffset; row > rows; --row)
    {
        for (int column = columnOffset; column < columns; ++column)
        {
            i++;
            m_gridLayout->addWidget(m_digitButtons[i], row, column);
        }
    }

    // Set the layout manager
    setLayout(m_gridLayout);

    qDebug() << "Calculator opened";
}


Calculator::~Calculator()
{
    qDebug() << "Calculator closed";
}


Button* Calculator::createButton(const QString &sign, const char *slotFunction)
{
    Button* button = new Button(sign);
    connect(button, SIGNAL(clicked()), this, slotFunction);
    return button;
}


Button *Calculator::getClickedButton()
{
    Button* button = qobject_cast<Button*>(sender());
    return button;
}


void Calculator::digitClicked()
{
    if (m_display_down->text() == m_initial_value || m_display_down->text() == m_error_value)
    {
        m_display_down->clear();

        if (m_display_up->text() == m_error_value)
        {
            m_display_up->clear();
        }
    }

    Button* button = getClickedButton();
    QString digit = button->text();

    m_display_down->setText(m_display_down->text() + digit);
}


void Calculator::pointClicked()
{
    QString digits = m_display_down->text();

    if (digits.contains(m_point_sign) == false)
    {
        m_display_down->setText(m_display_down->text() + m_point_sign);
    }
}


void Calculator::changeSignClicked()
{
    QString digits = m_display_down->text();

    if (digits == m_initial_value || digits == m_error_value)
    {
        return;
    }

    double value = digits.toDouble();

    if (value > 0.0)
    {
        digits.prepend('-'); // add minus
    }
    else if (value < 0.0)
    {
        digits.remove(0, 1); // remove minus
    }

    m_display_down->setText(digits);
}


void Calculator::binaryOperatorClicked()
{
    if (m_display_down->text() != m_error_value)
    {
        Button* button = getClickedButton();
        QString operation = button->text();

        m_display_sign->setText(operation);

        if (m_display_up->text().isEmpty() == false && m_display_up->text() != m_error_value)
        {
            calculate();
        }
        else
        {
            m_display_up->setText(m_display_down->text());
            m_display_down->setText(m_initial_value);
        }
    }
}


void Calculator::calculate()
{
    double operand_1 = m_display_up  ->text().toDouble();
    double operand_2 = m_display_down->text().toDouble();

    double result = 0.0;

    QString operation = m_display_sign->text();

    if (operation == m_plus_sign)
    {
        result = operand_1 + operand_2;
    }
    else if (operation == m_minus_sign)
    {
        result = operand_1 - operand_2;
    }
    else if (operation == m_times_sign)
    {
        result = operand_1 * operand_2;
    }
    else if (operation == m_division_sign)
    {
        if (operand_2 == 0.0)
        {
            abortOperation();
            return;
        }

        result = operand_1 / operand_2;
    }
    else if (operation == m_power_sign)
    {
        result = std::pow(operand_1, operand_2);
    }

    m_display_up->setText(QString::number(result));
    m_display_down->setText(m_initial_value);
}


void Calculator::equalClicked()
{
    if (m_display_up->text().isEmpty() == false && m_display_up->text() != m_error_value)
    {
        calculate();
        m_display_down->setText(m_display_up->text());
        m_display_up->clear();
        m_display_sign->clear();
    }
}


void Calculator::unaryOperatorClicked()
{
    Button* button = getClickedButton();
    QString operation = button->text();

    double operand = m_display_down->text().toDouble();
    double result = 0.0;

    if (operation == m_sqrt_sign)
    {
        if (operand < 0.0)
        {
            abortOperation();
            return;
        }

        result = std::sqrt(operand);
    }
    else if (operation == m_sqpow_sign)
    {
        result = std::pow(operand, 2.0);
    }
    else if (operation == m_reciprocal_sign)
    {
        if (operand == 0.0)
        {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    else if (operation == m_log_sign)
    {
        if (operand < 0.0 || operand == 0.0)
        {
            abortOperation();
            return;
        }
        result = log10(operand);
    }
    else if (operation == m_tenpow_sign)
    {
        result = std::pow(10.0, operand);
    }

    m_display_down->setText(QString::number(result));
}


void Calculator::abortOperation()
{
    m_display_up->setText(m_error_value);
    m_display_sign->clear();
    m_display_down->setText(m_error_value);
}


void Calculator::backspaceClicked()
{
    QString text = m_display_down->text();
    text.chop(1); // delete 1 right element

    if (text.isEmpty())
    {
        text = "0";
    }

    m_display_down->setText(text);
}


void Calculator::clear()
{
    m_display_down->setText("0");
}


void Calculator::clearAll()
{
    m_display_up->clear();
    m_display_sign->clear();
    m_display_down->setText("0");
}


void Calculator::clearMemory()
{
    m_memorySum = 0.0;
}


void Calculator::readMemory()
{
    m_display_down->setText(QString::number(m_memorySum));
}


void Calculator::addMemory()
{
    equalClicked();
    m_memorySum += m_display_down->text().toDouble();
}


void Calculator::subMemory()
{
    equalClicked();
    m_memorySum -= m_display_down->text().toDouble();
}


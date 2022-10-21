
#ifndef BUTTON_H
#define BUTTON_H


#include <QToolButton>


class Button : public QToolButton {

    Q_OBJECT

public:
    explicit Button(const QString& text, QWidget *parent = nullptr)
        : QToolButton(parent)
    {
        setText(text);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }

    virtual QSize sizeHint() const override
    {
        QSize size = QToolButton::sizeHint();
        size.rheight() += 34;
        size.rwidth() = qMax(size.width(), size.height());
        return size;
    }
};


#endif // BUTTON_H


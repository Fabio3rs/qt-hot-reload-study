#pragma once

#include <QObject>

class ObjectTest : public QObject {
    Q_OBJECT
public:
    ObjectTest(QObject *parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE void test();
    Q_INVOKABLE void test2();

    ~ObjectTest();
};



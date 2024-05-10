#include "ObjectTest.hpp"
#include <iostream>

void ObjectTest::test() { std::cout << "Este é um teste" << std::endl; }

void ObjectTest::test2() { std::cout << "Este é um teste 2" << std::endl; }

ObjectTest::~ObjectTest() = default;

#pragma once

#include "node.h"

#include <memory>   // для реализации shared_ptr
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

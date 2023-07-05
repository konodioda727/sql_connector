#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "geneStr.h"
#include "servicess.h"

void DaySelling(MYSQL* conn);
void Customer(MYSQL* conn);

#endif // !CONTROLLER_H

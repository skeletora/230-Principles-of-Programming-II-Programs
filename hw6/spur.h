#ifndef SPUR_DOT_H
#define SPUR_DOT_H

#include <string>
#include "stack.h"

enum struct NameT:char {WEST, EAST, LOCAL, YARD, UNKNOWN};
const std::string NAMET_NAMES[] = {"West", "East", "Local", "Yard", "UNKNOWN"};

const NameT FIRST_NAME = NameT::WEST;
const NameT LAST_NAME = NameT::UNKNOWN;
const int NAMET_COUNT = int(LAST_NAME) - int(FIRST_NAME);

struct SpurT{
    NameT name;
    StackT trains;
};

std::string NameTToString(const NameT n);
NameT StringToNameT(std::string& name);

std::string SpurTName(const SpurT s);
void InitSpur(SpurT& s);

#endif

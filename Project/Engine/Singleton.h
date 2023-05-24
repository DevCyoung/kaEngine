#pragma once

#define SINGLETON(CLASSNAME) public : \
                             static CLASSNAME* GetInst() { static CLASSNAME instance; return &instance; } \
                             private : \
                             CLASSNAME(); ~CLASSNAME();

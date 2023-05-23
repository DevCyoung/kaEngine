#pragma once

#define SINGLETON(CLASSNAME) public : \
                             static CLASSNAME* Get##CLASSNAME() { static CLASSNAME instance; return &instance; } \
                             private : \
                             CLASSNAME(); ~CLASSNAME();

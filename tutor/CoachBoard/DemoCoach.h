#pragma once

#include "interface/ICoach.h"

class Coach : public ICoach
{
public:
    virtual ~Coach() {}
};

class DemoCoach : public Coach
{
public:
    DemoCoach();

private:
    void PrepareLesson();
    size_t Count() { return 0; }
    IStep& GetStep(size_t n) {throw 1;}
};

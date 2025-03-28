#pragma once

#include <vector>
#include "cActor.h"

class cTeam {
public:
    std::vector<cActor*> members;
    int nCurrentMember = 0;
    int nTeamSize = 0;

    bool IsTeamAlive();
    cActor* GetNextMember();

};

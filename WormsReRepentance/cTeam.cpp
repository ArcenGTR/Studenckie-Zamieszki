#include "cTeam.h"

bool cTeam::IsTeamAlive() {
	bool bAllDead = false;
	for (auto w : members)
		bAllDead |= (w->fHealth > 0.0f);
	return bAllDead;
}

cActor* cTeam::GetNextMember() {
	do {
		nCurrentMember++;
		if (nCurrentMember >= nTeamSize) nCurrentMember = 0;
	} while (members[nCurrentMember]->fHealth <= 0);
	return members[nCurrentMember];
}

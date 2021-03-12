#include "access/rel.hpp"

relation::relation() {
	rd_smgr = nullptr;
}

void
relation::OpenSmgr() {
	if (rd_smgr == nullptr) {
		rd_smgr = smgropen(nullptr, MAIN_FORKNUM);
	}
}
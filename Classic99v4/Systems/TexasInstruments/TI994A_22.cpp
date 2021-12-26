// Classic99 v4xx - Copyright 2021 by Mike Brent (HarmlessLion.com)
// See License.txt, but the answer is "just ask me first". ;)

// This class subclasses TI994A for version 2.2
// TODO: Technically we should also disallow CRU to the cartridge port...

#include "TI994A_22.h"
#include "../../EmulatorSupport/interestingData.h"
#include "../../Memories/TI994A22GROM.h"
#include "../../Memories/TI994AROM.h"
#include "../../VDPs/TMS9918A.h"
#include "../../Keyboard/kb_994A.h"

TI994A22::TI994A22()
    : TI994()
{
}

TI994A22::~TI994A22() {
}

// this virtual function is used to subclass the various types of TI99 - anything that varies is
// loaded and initialized in here.
bool TI994A22::initSpecificSystem() {
    pGrom = new TI994A22GROM(this);     // this is the only difference compared to regular 99/4A right now
    pGrom->init(0);
    pRom = new TI994AROM(this);
    pRom->init(0);
    pVDP = new TMS9918A(this);
    pVDP->init(0);
    pKey = new KB994A(this);
    pKey->init(0);

    // map in the alpha lock key output on bit 21
    for (int idx=0; idx<0x800; idx+=20) {
        claimIOWrite(idx+21, pKey, 21);
    }

    return true;
}

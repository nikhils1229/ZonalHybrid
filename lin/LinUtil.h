#ifndef LINUTIL_H_
#define LINUTIL_H_

#include "LinDataFrame_m.h"

// Computes the protected identifier (ID + Parity)
unsigned char computePID(int frameId);

// Computes checksum for the new Response type
// Classic Checksum: Data only (PID=0x3C/0x3D)
// Enhanced Checksum: PID + Data (Everything else)
unsigned char computeChecksum(LinResponse *frame, int pid);

#endif

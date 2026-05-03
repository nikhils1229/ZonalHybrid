//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "CanSourceGatewayApp.h"
#include "fico4omnet/utilities/CanFdUtil.h"

// FiCo4OMNeT
// Auto-generated messages
#include "fico4omnet/linklayer/can/messages/CanDataFrame_m.h"

using namespace FiCo4OMNeT;

namespace SignalsAndGateways {

Define_Module(CanSourceGatewayApp);

CanSourceGatewayApp::~CanSourceGatewayApp() { outgoingDataFrames.clear(); }

void CanSourceGatewayApp::initialize(int stage) {
  CanTrafficSourceAppBase::initialize(stage);
  if (stage == 0) {
    isCanFd = par("isCanFd");
  }
}

void CanSourceGatewayApp::handleMessage(cMessage *msg) {
  if (msg->arrivedOn("in")) {
    CanDataFrame *df = dynamic_cast<CanDataFrame *>(msg);
    if (!df) {
      delete msg;
      return;
    }

    if (!isCanFd && df->isCanFd()) {
      // Fragment FD frame for Standard CAN
      unsigned int totalLen = df->getPayloadArraySize();
      unsigned int fragments = (totalLen + 7) / 8;

      for (unsigned int i = 0; i < fragments; i++) {
        CanDataFrame *frag = new CanDataFrame("CAN_Frag");
        frag->setTimestamp(simTime()); // Use current time
        frag->setCanID(df->getCanID());
        frag->setIsCanFd(false);
        frag->setDlc(8);
        frag->setPayloadArraySize(8);

        unsigned int offset = i * 8;
        for (unsigned int b = 0; b < 8; b++) {
          if (offset + b < totalLen)
            frag->setPayload(b, df->getPayload(offset + b));
          else
            frag->setPayload(b, 0); // Padding
        }

        // Approximate stuffed bit length: (Overhead + Payload) + 20% Stuffing
        int nominalBits = 47 + frag->getPayloadArraySize() * 8;
        frag->setBitLength(nominalBits + nominalBits / 5);

        send(frag, "out");
      }
      delete df; // Consumed
    } else {
      // Forward as is
      df->setTimestamp(simTime());
      send(df, "out");
    }
  } else {
    delete msg;
  }
}

} // namespace SignalsAndGateways

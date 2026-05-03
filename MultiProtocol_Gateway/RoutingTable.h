#ifndef __ROUTING_TABLE_H_
#define __ROUTING_TABLE_H_

#include <vector>
#include <map>
#include <cstdint>

namespace multiprotocol_gateway {

enum class Protocol {
    CAN,
    CAN_FD,
    ETHERNET,
    LIN
};

struct RouteEntity {
    Protocol targetProto;
    int targetPort;
    int targetId; // CAN ID, LIN PID, or Eth Dest (simplified)
};

class RoutingTable {
public:
    RoutingTable();
    
    // Routing rules
    bool lookupCanRoute(unsigned int canId, RouteEntity& outRoute);
    bool lookupEthRoute(int destId, RouteEntity& outRoute);
    bool lookupLinRoute(unsigned int linPid, RouteEntity& outRoute);

private:
    std::map<unsigned int, RouteEntity> canRoutes;
    std::map<int, RouteEntity> ethRoutes;
    std::map<unsigned int, RouteEntity> linRoutes;
};

}

#endif

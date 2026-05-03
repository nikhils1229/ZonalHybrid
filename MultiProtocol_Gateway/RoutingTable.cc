#include "RoutingTable.h"

namespace multiprotocol_gateway {

RoutingTable::RoutingTable() {
  // ==========================================
  // ZONE-TO-BACKBONE ROUTES (Aggregation)
  // ==========================================
  // Map CAN ID 100 (Std CAN Node) -> Ethernet Backbone
  canRoutes[100] = {Protocol::ETHERNET, 0, 1};
  
  // Map CAN ID 200 (CAN-FD Node) -> Ethernet Backbone
  canRoutes[200] = {Protocol::ETHERNET, 0, 1};

  // ==========================================
  // CROSS-ZONE ROUTES (Zonal Hops via Backbone)
  // ==========================================
  // 1. CAN-FD (ID 300) -> Route to Ethernet (Type 2576) -> Gateway 1 routes to Std CAN
  canRoutes[300] = {Protocol::ETHERNET, 0, 2576};

  // 2. Standard CAN (ID 400) -> Route to Ethernet (Type 2848) -> Gateway 2 routes to CAN-FD
  canRoutes[400] = {Protocol::ETHERNET, 0, 2848};

  // ==========================================
  // ETHERNET-TO-ZONES ROUTES (Segmentation)
  // ==========================================
  // 3. Ethernet -> Standard CAN (ID 120)
  ethRoutes[2576] = {Protocol::CAN, 0, 120}; 

  // 4. Ethernet -> CAN-FD (ID 220)
  ethRoutes[2848] = {Protocol::CAN_FD, 0, 220};

  // Legacy/Default rules
  ethRoutes[0xFFFF] = {Protocol::CAN_FD, 0, 0x2B};
}

bool RoutingTable::lookupCanRoute(unsigned int canId, RouteEntity &outRoute) {
  auto it = canRoutes.find(canId);
  if (it != canRoutes.end()) {
    outRoute = it->second;
    return true;
  }
  return false;
}

bool RoutingTable::lookupEthRoute(int destId, RouteEntity &outRoute) {
  auto it = ethRoutes.find(destId);
  if (it != ethRoutes.end()) {
    outRoute = it->second;
    return true;
  }
  return false;
}

bool RoutingTable::lookupLinRoute(unsigned int linPid, RouteEntity &outRoute) {
  auto it = linRoutes.find(linPid);
  if (it != linRoutes.end()) {
    outRoute = it->second;
    return true;
  }
  return false;
}

} // namespace multiprotocol_gateway

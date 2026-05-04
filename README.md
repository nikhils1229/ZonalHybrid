# Zonal Hybrid Automotive Network Simulation

This repository contains a high-fidelity OMNeT++ simulation of a **Zonal E/E Architecture** for modern vehicles. It features a multi-protocol gateway capable of translating between CAN, CAN-FD, LIN, and Automotive Ethernet, connected via a high-speed backbone.

## 🚗 Project Overview

The project demonstrates a transition from traditional domain-based architectures to a **Hybrid Zonal Model**. This shift reduces wiring complexity and weight by consolidating local protocol clusters (Zones) into Zonal Gateways, which communicate over a deterministic Ethernet backbone.

### Key Components:
- **Zonal Gateways (`MultiGateway`)**: Performs L7 protocol translation, frame encapsulation, segmentation (slicing), and aggregation.
- **Heterogeneous Zones**:
  - **Zone 1**: Classical CAN (500 kbps).
  - **Zone 2**: CAN-FD (2 Mbps Arbitration / 5 Mbps Data).
  - **Zone 4**: LIN (20 kbps Master-Slave).
- **Backbone**: 100 Mbps / 1 Gbps Automotive Ethernet (100BASE-T1) using `EtherSwitch` logic.

---

## 🛠️ Technical Specifications

### Multi-Protocol Translation Matrix
| Source | Target | Logic | Timing |
| :--- | :--- | :--- | :--- |
| **CAN-FD** | **CAN** | Slicing (64B -> 8x8B fragments) | 1ms Pacing |
| **CAN** | **Ethernet** | Aggregation (64B threshold) | 0.5ms Window |
| **Ethernet** | **CAN-FD** | Encapsulation (Direct) | 0.1ms Artifact* |
| **LIN** | **Ethernet** | Direct Mapping (8B -> Eth) | 1ms Processing |

> **Note on Latency Artifact**: An ultra-granular audit identified a simulation artifact where the initial Ethernet-to-CAN/FD dispatch uses a hardcoded 0.1ms timer, bypassing the configured 1ms processing delay. This is documented in the `Critical_Question_Report.md`.

### Performance Baselines
- **CAN -> Ethernet Latency**: ~1.506 ms (Aggregation + Processing).
- **Ethernet -> LIN Latency**: ~15.0 ms (Sequential Polling).
- **Backbone Throughput**: ~4.8 Mbps under current load profiles.

---

## 📊 Documentation & Reports

Detailed technical documentation and critical analysis reports are provided in the root directory:
- [**Deep Technical Report**](./Deep_Technical_Report.md): Full architectural breakdown, parameter matrices, and Mermaid.js frame-lifecycle diagrams.
- [**Critical Question Report**](./Critical_Question_Report.md): Technical defense answering edge-case questions regarding buffer overflows, fragment loss, and security.

---

## 🚀 Getting Started

### Prerequisites
- **OMNeT++ 6.0.2**
- **INET Framework**
- **FiCo4OMNeT Library**
- **CoRE4INET** (for TSN-ready capabilities)

### Running the Simulation
1. Ensure all shared libraries are built (`.so` or `.a` files).
2. Set your `LD_LIBRARY_PATH` to include the `src` directories of the dependencies.
3. Execute the simulation using `opp_run`:

```bash
opp_run -u Cmdenv -c General -n .:../inet/src:../FiCo4OMNeT/src:../CoRE4INET/src ZonalHybridNetwork/examples/omnetpp.ini
```

### Simulation Logs
Detailed traces of every frame transition are stored in the compressed `simulation_logs.zip`.

---
*Developed as part of the Zonal Hybrid Network Architecture Research.*

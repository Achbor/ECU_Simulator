# Automotive ECU Simulator

An automotive Electronic Control Unit (ECU) simulator developed in C for Embedded Linux. The project models the behaviour of a simplified automotive ECU by implementing multithreaded periodic tasks, sensor simulation, fault management, and CAN communication using SocketCAN.

The simulator is designed to demonstrate embedded software engineering concepts commonly used in the automotive industry, including thread synchronization, real-time task scheduling, modular software architecture, and CAN-based communication.

---

## Project Overview

This project simulates an ECU responsible for:

- Engine management
- Sensor monitoring
- Fault detection and handling
- CAN frame transmission
- Diagnostic command-line interface (CLI)
- Runtime system monitoring
- Fault injection and testing
- CAN statistics monitoring

The entire system is implemented using POSIX threads and Linux APIs, making it portable across both x86_64 and ARM64 Embedded Linux platforms.

---

## Features

- Multithreaded Embedded Linux application
- Thread-safe shared ECU state management
- Periodic real-time task execution
- SocketCAN communication
- Virtual CAN (vcan) support
- Diagnostic CLI interface
- Fault injection support
- CAN transmission statistics
- Runtime dashboard logging
- System uptime monitoring
- Modular and scalable software architecture

---

## Technologies Used

| Technology | Purpose |
|------------|---------|
| C | Application development |
| Embedded Linux | Operating System |
| POSIX Threads | Task scheduling |
| SocketCAN | CAN communication |
| Linux Networking APIs | CAN interface handling |
| Mutexes | Thread synchronization |
| Virtual CAN (vcan) | CAN bus simulation |
| GCC | Compilation |
| Makefile | Build automation |

---

## Software Architecture

```
                           ECU Simulator

                                  |
                                  |
                                 CLI
                                  |
                                  |
                           ECU Manager
                        (Thread-safe API)
                                  |
                                  |
                           Shared ECU State
                                  |
        ---------------------------------------------------------
        |              |              |              |          |
     Engine         Sensors         Faults          CAN       Logger
      Task            Task            Task           Task       Task
        |              |              |              |          |
        ---------------------------------------------------------
                                  |
                              SocketCAN
                                  |
                               vcan0
                                  |
                           Linux CAN Stack
```

---

## Threading Model

The ECU simulator uses multiple POSIX threads to model periodic ECU tasks.

| Task | Execution Period |
|------|----------------|
| Engine Task | 10 ms |
| Sensor Task | 100 ms |
| Fault Task | 100 ms |
| CAN Task | 100 ms |
| Logger Task | 1000 ms |

Each task operates independently and accesses the shared ECU state through the ECU Manager module.

---

## Project Structure

```
ECU-Simulator/

├── include/
│   ├── ecu.h
│   ├── ecu_manager.h
│   ├── engine.h
│   ├── sensors.h
│   ├── fault_manager.h
│   ├── scheduler.h
│   ├── can.h
│   ├── logger.h
│   ├── cli.h
│   └── system.h
│
├── src/
│   ├── main.c
│   ├── ecu.c
│   ├── ecu_manager.c
│   ├── engine.c
│   ├── sensors.c
│   ├── fault_manager.c
│   ├── scheduler.c
│   ├── can.c
│   ├── logger.c
│   ├── cli.c
│   └── system.c
│
├── Makefile
├── README.md
└── docs/
```

---

## CAN Frame Definitions

### Engine Frame (0x100)

| Byte | Description |
|------|-------------|
| 0-1 | RPM |
| 2-3 | Vehicle Speed |
| 4 | Throttle Position |
| 5 | Engine Running Flag |
| 6-7 | Reserved |

---

### Sensor Frame (0x101)

| Byte | Description |
|------|-------------|
| 0-1 | Coolant Temperature ×10 |
| 2-3 | Battery Voltage ×100 |
| 4-5 | Oil Pressure ×100 |
| 6-7 | Reserved |

---

### Fault Frame (0x102)

| Byte | Description |
|------|-------------|
| 0 | Overheat Fault |
| 1 | Battery Fault |
| 2-7 | Reserved |

---

## CLI Commands

```
start
stop

set throttle <0-100>

show engine
show sensors
show faults

inject overheat
inject battery

clear faults

show statistics

help
exit
```

---

## Building the Project

Clone the repository:

```bash
git clone <repository_url>
cd ECU-Simulator
```

Build the project:

```bash
make
```

---

## Setting Up Virtual CAN

Load the Virtual CAN module:

```bash
sudo modprobe vcan
```

Create the Virtual CAN interface:

```bash
sudo ip link add dev vcan0 type vcan
```

Bring the interface up:

```bash
sudo ip link set up vcan0
```

Verify the interface:

```bash
ip addr show vcan0
```

---

## Monitoring CAN Traffic

Install CAN utilities if necessary:

```bash
sudo apt install can-utils
```

Monitor transmitted CAN frames:

```bash
candump vcan0
```

---

## Running the Simulator

Run the ECU simulator:

```bash
./ecu_simulator
```

Example:

```text
ECU> start

Engine started.

ECU> set throttle 75

Throttle set to 75%.

ECU> show engine

Running   : YES
RPM        : 4550
Speed      : 75 km/h
Throttle   : 75%
```

---

## Fault Injection

Inject an overheat fault:

```text
ECU> inject overheat
```

Inject a battery fault:

```text
ECU> inject battery
```

Clear all faults:

```text
ECU> clear faults
```

View fault status:

```text
ECU> show faults
```

---

## CAN Statistics

View CAN transmission statistics:

```text
ECU> show statistics
```

Example output:

```text
CAN Statistics
------------------------

Engine Frames : 3561
Sensor Frames : 3561
Fault Frames  : 3561

Total Frames  : 10683

Uptime        : 00:15:43
```

---

## Embedded Systems Concepts Demonstrated

This project demonstrates several concepts commonly used in Embedded Linux and Automotive Software Engineering:

- Embedded Linux Development
- POSIX Thread Programming
- Thread Synchronization using Mutexes
- Real-Time Periodic Task Scheduling
- SocketCAN Programming
- CAN Frame Packing and Transmission
- Diagnostic Command-Line Interfaces
- Fault Injection Techniques
- Runtime Monitoring and Logging
- Modular Software Architecture
- Linux System Programming
- Automotive ECU Design Principles

---

## Platform Support

The project is designed to be portable across multiple Linux-based platforms:

- x86_64 Linux
- ARM64 Linux
- Raspberry Pi (ARM64)
- Embedded Linux Development Boards
- QEMU-based Linux environments

---

## Future Improvements

Potential future extensions include:

- CAN frame reception support
- Multiple ECU simulation
- Diagnostic Trouble Codes (DTCs)
- UDS diagnostic protocol support
- CAN logging to file
- ISO-TP support
- Unit testing framework
- ECU configuration files

---

## License

This project is intended for educational and portfolio purposes and may be freely modified and extended.

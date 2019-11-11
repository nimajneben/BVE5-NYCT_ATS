# NYCT ATS Plugin for BVE5

This BVE5 plugin aims to be as realistic as possible to emulate the safety systems of New York City Transit.

---
Currently this supports:
 * KMH to MPH Conversion
 * "Stop Arm" trip
 * "Time-based" speed control (Grade Time / Station Time)
---
What is in the works:
 * Psuedo-CBTC Support (in CBTC branch)
---
To build this repository:
 1. Download this repository.
 2. Open the .sln file in Visual Studio (I use VS 2017)
 3. Ensure the project settings are building a release 32-bit DLL.
 4. Build
 5. The DLL should be in a Release folder. Place it in your train files and have your Vehicle.txt load it.

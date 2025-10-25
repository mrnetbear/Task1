# Rutherford Scattering Simulation with Geant4

## Project Overview

This project implements a Geant4-based simulation of Rutherford scattering experiments. The simulation models alpha particles interacting with a thin gold foil and a lead detector, tracking energy deposition and angular distribution of scattered particles.

## Key Components

### Detector Geometry
- **World Volume**: 10 cm cube filled with galactic vacuum
- **Gold Foil**: 1×1 cm plate, 2 μm thickness at origin
- **Lead Detector**: Cylindrical tube (10 cm diameter, 5 cm height) rotated 90 degrees around X-axis

### Physics
- **Particles**: Alpha particles with energies of 5.5 MeV and 22 MeV
- **Physics List**: Standard electromagnetic processes (G4EmStandardPhysics)
- **Primary Generator**: Alternates between two energy levels with directional emission

### Data Collection
- **Output Format**: ROOT ntuples
- **Recorded Data**:
  - Deposited energy in detector
  - Cosine of scattering angle (cosθ)
- **Threshold**: Events with energy deposition > 80 keV

## Build Instructions

### Prerequisites
- Geant4 (version 10.0 or higher)
- CMake (version 3.8 or higher)
- ROOT data analysis framework
- C++ compiler with C++11 support

### Compilation
```bash
mkdir build
cd build
cmake ..
make -j4
```

## Usage

### Interactive Mode
```bash
./Task1
```

### Batch Mode
```bash
./Task1 macro.mac
```

### Visualization
The simulation includes visualization attributes:
- Gold foil: Yellow color
- Lead detector: Grey color

## Output

The simulation generates ROOT ntuples containing:
- Energy deposition in the detector
- Cosine of scattering angle relative to initial trajectory

## Physics Context

This simulation models the classic Rutherford scattering experiment where alpha particles scatter off atomic nuclei, demonstrating the nuclear model of the atom. The angular distribution follows the characteristic 1/sin⁴(θ/2) dependence predicted by Rutherford's formula.

## Configuration

Key parameters can be modified in the source files:
- Particle energies in `PrimaryGeneratorAction.cc`
- Detector dimensions in `DetectorConstruction.cc`
- Energy threshold in `EventAction.cc`

## License

This project is intended for educational and research purposes in particle physics simulation.
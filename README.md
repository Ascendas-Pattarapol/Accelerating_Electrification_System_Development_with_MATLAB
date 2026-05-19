# Buck Converter Simscape Electrical Workshop

This workshop series builds a buck converter workflow step by step, starting from a simple averaged converter model and progressing to detailed Simscape Electrical modeling, thermal behavior, PI control, controller optimization, and embedded-code verification using SIL and PIL.

## Workshop Overview

| No. | Workshop | Main Purpose |
|---|---|---|
| 00 | [Average Buck Converter](00_Create_Buck_Simscape_Average_Simplify_Workshop_Instructions.md) | Build a simple buck converter using the averaged `Buck Converter` block for fast system-level simulation. |
| 01 | [Simplified Switching Buck Converter](01_Create_Buck_Simscape_Elec_Simplify_Workshop_Instructions.md) | Build a detailed Simscape Electrical buck converter using MOSFET, diode, inductor, capacitor, resistor, sensors, and PWM. |
| 02 | [MOSFET Thermal Effect](02_Create_Temp_Simscape_Elec_Simplify_Workshop_Instructions.md) | Add MOSFET thermal modeling, heatsink/convection behavior, and compare thermal response. |
| 03 | [PI Controller Design](03_Create_PID_Buck_Simscape_Elec_Simplify_Workshop_Instructions.md) | Add closed-loop voltage control using a PI controller and tune it with PID Tuner by linearizing around an operating point. |
| 04 | [PI Gain Optimization](04_Optimize_PID_Buck_Simscape_Elec_Simplify_Workshop_Instructions.md) | Use Simulink Response Optimizer to tune `Kp` and `Ki` against step response requirements. |
| 05 | [SIL Simulation](05_SIL_PID_Buck_Simscape_Elec_Workshop_Instructions.md) | Run generated controller code in software-in-the-loop mode on the host computer and inspect code, traceability, and profiling. |
| 06 | [PIL Simulation](06_PIL_PID_Buck_Simscape_Elec_Workshop_Instructions.md) | Run generated controller code on the STM32 target processor using processor-in-the-loop simulation and compare against simulation. |

## Learning Flow

1. Start with an averaged buck converter model to understand duty-cycle-to-voltage behavior quickly.
2. Move to a switching Simscape Electrical implementation to understand the physical converter components.
3. Add thermal behavior to show how electrical losses affect MOSFET temperature.
4. Add PI closed-loop control so the output voltage tracks a target instead of relying on fixed duty.
5. Optimize PI gains using simulation-based response requirements.
6. Generate embedded controller code and verify it with SIL.
7. Run the same generated controller code on STM32 hardware with PIL and inspect execution timing.

## Toolbox Required for This Workshop

- MATLAB
- Simulink
- Plant Modeling for Electrification Systems
  - Simscape
  - Simscape Electrical
- Practical Control Design and Optimization
  - Control System Toolbox
  - Simulink Control Design
  - Optimization Toolbox
  - Simulink Design Optimization
  - System Identification Toolbox
- Deployment and Validation Workflow
  - MATLAB Coder
  - Simulink Coder
  - Embedded Coder
  - STM32 Microcontroller Blockset or Embedded Coder Support Package for STMicroelectronics STM32 Processors
  - C2000 Microcontroller Blockset or Embedded Coder Support Package for Texas Instruments C2000 Processors

For STM32 workflows, install and configure the required STM32 program dependencies by following the MathWorks setup guide:

[STM32CubeMX Configuration](https://www.mathworks.com/help/stm32b/ug/stm32-cubemx-configuration.html)

You can launch the STM32 hardware setup from MATLAB with:

```matlab
stm32cube.tools.launchHardwareSetup
```

## Workshop Files

The workshop instruction files, Simulink models, videos, generated assets, and support project files are published at the top level of this repository. Each instruction file describes the starting model, finished reference model when available, procedure, expected observations, and troubleshooting notes.

For SIL and PIL workshops, the controller model is:

```text
Voltage_Controller_STM32.slx
```

The STM32 project configuration is stored in:

```text
Voltage_Controller_Project\
```

## Final Outcome

After completing the series, participants should understand how to model, control, optimize, generate code for, and verify a buck converter controller using Simulink, Simscape Electrical, Embedded Coder, and STM32 target workflows.

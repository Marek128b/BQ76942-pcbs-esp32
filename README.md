# BQ76942-pcbs-esp32

**table of content**
- [BQ76942-pcbs-esp32](#bq76942-pcbs-esp32)
  - [Short description](#short-description)
  - [Registers](#registers)
    - [Functional Block Diagram](#functional-block-diagram)
    - [Voltage Measurement](#voltage-measurement)
    - [Direct commands and sub commands](#direct-commands-and-sub-commands)
  - [Voltage Switcher](#voltage-switcher)
  - [Support me](#support-me)

## Short description
The BQ76942 Balancer is an integrated circuit specifically designed for battery management applications, with a particular focus on multi-cell lithium-ion or lithium-polymer battery packs. Serving as a sophisticated component of a battery management system (BMS), the BQ76942 offers advanced functionalities such as monitoring cell voltages, balancing charge distribution, and sensing temperature levels. Its primary objective is to ensure the safe and efficient operation of battery packs by closely monitoring individual cell voltages and temperature, thereby preventing issues like overcharging, over-discharging, and thermal runaway. By redistributing charge among cells, the balancer functionality maintains optimal cell balance, extending battery life and enhancing the overall reliability of the system. With its compact size and comprehensive range of features, the BQ76942 Balancer plays a crucial role in the design and implementation of high-performance battery management systems across various applications, including electric vehicles, renewable energy storage systems, and portable electronics.

![drawio image basic diagram](documents/img/BQ76942-diagram.drawio.svg)


## Registers
!! NEEDS TESTING !!

### Functional Block Diagram
![functional block diagram](documents/img/functional-block-diagram.png)

### Voltage Measurement
`Technical Reference Manual BQ76942 @ page 19`

The BQ76942 device integrates a voltage ADC that is multiplexed between measurements of cell voltages, an internal temperature sensor, up to nine external thermistors, and also performs measurements of the voltage at the VC10 pin, the PACK pin, the LD pin, the internal Vref used by the coulomb counter, and the VSS rail (for diagnostic purposes). The BQ76942 device supports measurement of individual differential cell voltages in a series configuration, ranging from 3 series cells to 10 series cells. Each cell voltage measurement is a differential measurement of the voltage between two adjacent cell input pins, such as VC1–VC0, VC2–VC1, and so forth. The cell voltage measurements are processed based on trim and calibration corrections, and then reported in 16-bit resolution using units of 1 mV. The raw 24-bit digital output of the ADC is also available for readout using 32-bit subcommands (the 24-bit data is contained in the lower 3 bytes of the 32-bit data, and is sign-extended to create the upper byte). The cell voltage measurements can support a recommended voltage range from –0.2 V to 5.5 V. If a cell voltage is applied that exceeds a level of 5 × VREF1 (approximately 6.06 V), the device may report a value of –6.06 V (and the cell voltage raw counts similarly would report a value of -8388608). For best performance, stay at a maximum input of 5.5 V. The 16-bit cell and VC10 (stack), PACK, and LD pin voltage measurements are available by using the commands listed below.

![voltage measurement diagram](documents/img/voltage-messurement-diagram.png)

### Direct commands and sub commands
`Technical Reference Manual BQ76942 @ page 13`

The direct commands are accessed using a 7-bit command address that is sent from a host through the device serial communications interface and either triggers an action, provides a data value to be written to the device, or instructs the device to report data back to the host.

Subcommands are additional commands that are accessed indirectly using the 7-bit command address space and provide the capability for block data transfers. When a subcommand is initiated, a 16-bit
subcommand address is first written to the 7-bit command addresses 0x3E (lower byte) and 0x3F (upper byte).


## Voltage Switcher
The problem stems from the need to create links between the last battery cell and the VC10 and BAT terminals of the integrated circuit (IC), along with the obligation to connect the second-to-last battery cell, starting from its connection point (e.g., 3S Battery VC3), to all previous cell connections that lead to the BQ76942 Battery Management IC, except for the VC10 connection as this Pin has to be connected to the last Cell of the Battery pack.

## Support me
<a href="https://www.buymeacoffee.com/georgmareku" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a>
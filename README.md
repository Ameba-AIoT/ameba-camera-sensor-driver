# AmebaPro2 Camera Sensor Driver

Realtek AmebaPro2 (RTL8735B) camera sensor driver for VOE (Video Offload Engine). Supports **Normal Driver** and **Fast Camera Start (FCS)** flows for sensor bring-up.

## Compilation
**Please ensure that the toolchain path (``ASDK_DIR``) in ``rtl8735b_driver_code_sensor/source/Makefile`` and ``rtl8735b_driver_code_sensor/source/sensor/Makefile`` are CORRECT**

Build a specific sensor driver:

```bash
cd rtl8735b_driver_code_sensor/source/sensor
make sensor=sc2333 image
```

Build all supported sensors:

```bash
make all_sensor
```

Output binaries are placed in `source/output/` (please create one if the folder does not exist):

```
sensor_<name>.bin   — Normal driver
fcs_data_<name>.bin — FCS driver (if supported)
iq_<name>.bin       — IQ configuration
```

## FCS Driver

To generate the Fast Camera Start driver binary (per sensor folder):

```bash
gcc -o fcs_g.exe gen_fcs_data_<name>.c
./fcs_g.exe
```

## Folder Structure

```
source/sensor/          — Sensor driver sources (organized by vendor)
source/sensor/build/    — Built binaries (auto-generated)
source/sensor/Makefile  — Sensor build configuration
```
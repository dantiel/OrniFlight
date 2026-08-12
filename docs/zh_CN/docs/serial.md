# 串口

OrniFlight 使用串行端口与外围设备通信：接收器、GPS、遥测、VTX 控制、黑盒日志记录和 MSP（配置器连接）。

## 串口类型

|类型 |描述 |最适合 |
|------|------------|----------|
| **VCP** | USB 虚拟 COM 端口 — 直接 USB 连接到处理器 |配置器 (MSP) |
| **UART** |具有硬件信号检测功能的硬件 TX/RX 引脚 | RX、GPS、遥测、VTX、黑盒 |
| **SoftSerial** |任何引脚对上的软件驱动串行 |低带宽：仅遥测 |

VCP 不消耗物理 UART — 它始终可用于配置器。

## 端口分配

在 OrniFlight 配置器中，转到 **端口** 选项卡来分配功能：

|功能|典型的 UART |笔记|
|----------|-------------|--------|
|串行 RX | UART1 或 UART3 | SBUS、CRSF、IBUS 等 |
| GPS | UART3 或 UART6 | 57600 或 115200 波特率 |
|遥测|任何 TX 引脚 | SmartPort、HoTT、IBUS |
| VTX（流浪汉/SmartAudio）|任何 TX 引脚 |单线|
|黑匣子 |任何 TX 引脚 | OpenLog 或板载闪光灯 |
| MSP | VCP (USB) |配置器连接|

## OMNIBUSF4 端口映射

| UART |针脚 |典型用途|
|------|------|------------|
| VCP | USB | MSP（配置器）|
| UART1 | TX1/RX1 |串行 RX |
| UART3 | TX3/RX3 | GPS 或遥测 |
| UART6 | TX6/RX6 |免费 / 黑盒 / VTX |

## SoftSerial

SoftSerial 可用，但带宽有限。仅适用于低速率遥测（例如 9600 波特 SmartPort）。不建议使用串行 RX 或 GPS。
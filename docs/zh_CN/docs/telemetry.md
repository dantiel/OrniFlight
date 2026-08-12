# 遥测

遥测将飞行数据从 OrniFlight 发送到无线电发射器 — 电池电压、电流、RSSI、GPS 坐标、高度等。

## 支持的协议

|协议|无线电系统|线数 |
|----------|-------------|------------|
| **CRSF** |穿越火线 / 猎空 / ELRS |与 RX 集成（双向）|
| **SmartPort** | FrSky | 1 根线（TX 引脚）|
| **HoTT** |格劳普纳| 1 线 (TX+TZ) |
| **IBUS** | FlySky | 1 线（传感器 TX）|
| **LTM** |光遥测 (MWP) | 1 线 (TX) |

## 配置

1. 在配置器 → **端口** 中：将 UART TX 引脚设置为适当的遥测协议
2.启用遥测功能：`feature TELEMETRY`
3. 如果需要，配置遥测反演

对于 **CRSF**，自动处理遥测 —，无需单独的端口。

## SmartPort (FrSky)

SmartPort 需要 F4 处理器上的信号反转。要么：
- 使用内置逆变器的飞控
- 将 SoftSerial 与 `set tlm_inversion = ON` 一起使用

呜呜呜

## 遥测数据

OrniFlight 传输：
- VBAT 电压（主电池）
- 电流消耗/mAh消耗
- RSSI（信号强度）
- 飞行模式/手臂状态
- GPS 坐标（如果配备）
- 海拔高度/vario（如果是气压计）
- ONDAS 飞行剖面已激活
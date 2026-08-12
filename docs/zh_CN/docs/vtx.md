# 视频发射器 (VTX)

OrniFlight 支持 FPV 扑翼机的 VTX 控制。 VTX 模块可通过 OrniFlight 配置器、MSP 或 CLI — 设置频段、通道、功率电平和坑模式进行配置。

## 支持的协议

1. **IRC Tramp** — 常见于小型 VTX 模块，非常适合轻型 FPV 扑翼机
2. **TBS SmartAudio** — 支持坑模式的数字协议
3. **RTC6705** — 在带有集成 VTX 的板上直接 SPI 控制（例如 SPRACINGF3NEO）

## 配置

VTX 设置通过 OrniFlight 配置器中的 **VTX** 选项卡或通过 CLI 进行管理：

呜呜呜

## 串口

VTX 控制需要专用的 UART TX 引脚。使用 `IRC Tramp` 或 `TBS SmartAudio` 外设在 **端口** 选项卡中配置端口。

## FPV 扑翼机注意事项

- 重量很关键 — 选择轻量级 VTX 模块（Tramp Nano、Eachine Nano）
- 天线安装：确保与扑翼的间隙
- 电源滤波：在 LC 滤波器之后连接 VTX 电源，以避免视频中的伺服噪声
- 建议在台架测试中使用坑模式，以避免小型 VTX 模块过热
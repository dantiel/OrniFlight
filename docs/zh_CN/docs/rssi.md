#RSSI

RSSI（接收信号强度指示器）显示无线电链路的质量。 OrniFlight 可以从模拟输入、串行接收器数据或协议 RSSI 获取 RSSI。

## RSSI 来源

|来源 |连接|配置|
|--------|------------|---------------|
| **串行协议** |无（通过串行 RX 线）| CRSF、GHST — 自动 |
| **AUX 频道** |无（TX 发送 RSSI 作为通道）| `set rssi_channel = 8` |
| **模拟 ADC** | RSSI 垫在 FC → 接收器 RSSI 输出 | `set rssi_adc_channel = 1` |

## 配置

### 串行 RSSI (CRSF/GHST/SBUS)

呜呜呜

RSSI 通过串行协议 — 自动传输，无需额外接线。

### 模拟 RSSI

将接收器 RSSI 输出 → RSSI 焊盘连接到飞控上：

呜呜呜

### AUX 频道 RSSI

配置您的发射器以在特定通道上发送 RSSI，然后：

呜呜呜

## 显示

RSSI 显示在 OSD 中，可以通过遥测传输到您的收音机。配置警告阈值：

呜呜呜

## 扑翼机范围

对于扑翼机来说，RSSI 至关重要，— 扑动翅膀会产生动态 RF 干涉图案。在初始测试飞行期间监控 RSSI，以验证所有机翼位置的可靠链路性能。
# 黑盒日志记录

Blackbox 记录飞行数据，用于飞行后分析、调整和调试。 OrniFlight 支持记录到板载闪存芯片或外部 OpenLog 设备。

## 记录什么

- **陀螺仪** — 原始和过滤的 3 轴角速度
- **加速度计** — 3 轴加速度
- **PID 输出** — 每个轴的 P、I、D、F 贡献
- **ONDAS** — Cadence、Ferocity P/D 和其他特定于扑动的参数
- **RC 命令** — 在费率/博览会之后的位置
- **伺服输出** — 最终输出到每个伺服通道
- **电池** — 每次迭代的电压和电流
- **GPS** — 位置、速度、高度（如果有）

## 设置

### 板载闪存 (OMNIBUSF4)

OMNIBUSF4 包括用于 Blackbox 记录的 16MB 板载闪存。在配置器中启用：

1. **Blackbox** 选项卡 → 将 `Blackbox logging device` 设置为 `Onboard flash`
2. 设置日志记录速率（建议：`1/N`，对于 F4 目标，N=2-4）
3. 分配一个开关来启动/停止记录

### 外部 OpenLog

将 OpenLog 连接到空闲的 UART TX 引脚：

1. **端口**选项卡 → 将 UART 设置为 115200 波特率的 `Blackbox logging`
2、连接OpenLog：FC TX → OpenLog RX，加5V/GND

## 分析工具

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — 基于网络的日志查看器
- `blackbox_decode` — 转换为 CSV 以进行自定义分析

## ONDAS-特定

Blackbox 对于调整 ONDAS 参数至关重要。记录的 ONDAS 数据包括：
- `ondas_cadence_phase` — 调制窗口时序
- `ondas_ferocity_p` / `ondas_ferocity_d` — 非对称推力组件
- `ondas_balance` — 左/右翼平衡
- 每次迭代的每个伺服输出

这样可以精确分析扑动力学和机翼不对称校正。
# 第一个闪光

> *一步步将 OrniFlight 安装到您的飞控 —。*

## 你需要什么

- 基于 STM32F4 的飞行控制器（OMNIBUSF4、TINYFISH、MATEKF405 等）
- USB 电缆
- [dfu-util](http://dfu-util.sourceforge.net/) 或 STM32CubeProgrammer
- 来自 [发布页面](https://github.com/dantiel/OrniFlight/releases) 的 OrniFlight `.hex` 文件

## 第 1 步：进入 DFU 模式

1. **按住飞控上的 BOOT 按钮**
2. **按住按钮的同时插入 USB**
3. **2秒后松开**

在 macOS/Linux 上验证：

呜呜呜

应该显示 `Found DFU: [0483:df11]`

## 步骤 2：闪光

呜呜呜

## 步骤 3：首次启动

1.拔掉USB的插头
2. 重新插入 USB（不要按住 BOOT）
3. 通过 OrniFlight 配置器连接

## 步骤 4：基本配置

在配置器中：

1. **端口选项卡**：为您的接收器配置 UART（串行 RX）
2. **配置选项卡**：选择接收器协议（推荐 CRSF）
3. **模式选项卡**：设置 ARM、GLIDE/INDEPENDENT 和 PROFILE 开关
4. **高级 → ONDAS 选项卡**：查看默认值，首先调整 Cadence

## 故障排除

|问题 |修复|
|---------|-----|
|找不到 DFU 设备 |尝试不同的 USB 电缆，检查 BOOT 按钮 |
|闪存失败 |检查 dfu-util 安装、USB 权限 |
|刷机后无法开机|重新刷新，验证十六进制与您的目标匹配 |
|配置器无法连接 |检查 COM 端口和波特率 |

---

*下一步：[基本设置](basic_setup.html) →*
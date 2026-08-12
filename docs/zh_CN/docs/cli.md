# CLI 参考

OrniFlight 的命令行界面 (CLI) 提供对所有设置的完全访问。通过 OrniFlight 配置器中的 **CLI** 选项卡或通过 115200 波特率的串行终端进行访问。

## 基本命令

|命令|描述 |
|---------|------------|
| `help` |显示所有命令 |
| `status` |显示系统状态 |
| `version` |显示固件版本 |
| `defaults` |将所有设置重置为默认值 |
| `save` |保存设置并重新启动 |
| `exit` |退出 CLI（重新启动而不保存）|
| `diff` |显示更改的设置（对于共享配置很有用）|
| `dump` |显示所有设置 |
| `dump all` |显示所有设置，包括硬件默认值 |

## 基本设置

### 板和功能

呜呜呜

### 接收器

呜呜呜

### 电池

呜呜呜

### 舵机

呜呜呜

## ONDAS 设置（apiVersion 1.46+）

呜呜呜

## 航班资料

呜呜呜

## 伺服安装角度（apiVersion 1.46+）

呜呜呜

## 费率设置

呜呜呜

## 故障保护

```
set failsafe_delay = 4
set failsafe_procedure = LAND
set failsafe_throttle = 1000
```

## 分享您的配置

使用 `diff` 仅导出非默认设置：

呜呜呜
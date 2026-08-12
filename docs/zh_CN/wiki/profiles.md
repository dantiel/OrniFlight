# 航班资料

> *4 个独立调谐槽，可在飞行中切换。*

## 概念

OrniFlight 存储 4 个完整的 `ornithopterProfile_t` 结构 —，每个结构包含所有 19 个 ONDAS 和翼动力学参数。 BOX 模式（`BOXORNITHOPTERPROFILE`、permanentId 52）通过映射到 4 个插槽 (0–3) 的 2 位 RC 开关选择活动配置文件。

## 为什么要配置文件？

不同的飞行状态需要不同的调整：

|简介 |使用案例| Cadence | Ferocity |笔记|
|--------|----------|---------|---------|--------|
| 0 | **游轮** |中 (50) |低 (30) |高效前飞 |
| 1 | **特技飞行** |低 (20) |高 (80) |最大权限|
| 2 | **悬停/徘徊** |高 (70) |中 (50) |稳定性胜过速度|
| 3 | **滑行** |中 (50) |低 (10) |最少的干预 |

## 个人资料中有什么

`ornithopterProfile_t` 的所有 19 个字段：

- **滑翔几何**：glide_angle
- **ONDAS v2 (10)**：节奏、ferocity_d/p/roll/yaw、平衡、扭曲、warp_yaw、锚定、共振
- **Phase 2 (4)**：预知、espelho、saudade、ssff
- **波形 (2)**：ferocity_downtrip、ferocity_uprinkle
- **气动弹性 (2)**：aeroelastic_glide_coefficient、aeroelastic_flap_coefficient

## 什么是全局的（不是每个配置文件）

- 频率通道（一个 RC 通道，适用于 INDEPENDENT 和 GLIDE）
- 伺服安装角度
- 扑动相移
- GralhaAzul 几何（servo_speed、max_amplitude、flap_magnitude、wing_origin）

这些是机身的物理常数 — 它们不会随着飞行状态而改变。

## 飞行中切换

1. 将 2 位或 3 位开关分配给备用通道
2. 在“配置器模式”选项卡中，将该范围映射到 `ORNITHOPTER PROFILE`
3. 每个开关位置选择4个插槽之一
4. 配置器的配置文件下拉列表通过 MSP 编辑*当前选择的*插槽

---

*请参阅 `src/main/flight/ornithopter_profile.h` 了解结构定义。*
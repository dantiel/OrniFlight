# 控制

OrniFlight uses standard RC stick mapping with ornithopter-specific extensions.

## 棒映射

|坚持|轴|主要影响|
|--------|------|---------------|
|油门（左，垂直）|油门|扑动幅度/推力|
|偏航（左、水平）|偏航 |转弯时的差速翼推力 |
|间距（右、垂直）|推介|向前/向后倾斜 |
|滚动（右，水平）|卷|左/右银行|

## 飞行模式

|模式|坚持行为|
|------|----------------|
| **ACRO** | Sticks control angular rate — no auto level |
| **ANGLE** | Sticks control angle — auto-level when released |
| **HORIZON** | ANGLE near center, ACRO at full deflection |

ACRO 推荐给经验丰富的飞行员。 ANGLE is good for first flights and thermal soaring.

## 扑翼机专用控制

### INDEPENDENT 模式

When INDEPENDENT mode is active, each wing servo responds independently:
- **左摇杆** → 左翼舵机
- **右摇杆** → 右翼舵机
- Enables asymmetric flapping for aggressive maneuvers

### GLIDE 模式

GLIDE mode locks both wings in horizontal position.扑翼机变成滑翔机：
- **油门**对机翼位置没有影响
- **Pitch/Roll/Yaw** still influence tail control surfaces (if equipped)

### 配置文件切换

In-flight profile switching via AUX channel allows changing PID/ONDAS parameters mid-flight:
- **配置文件 1**：标准巡航设置
- **配置文件 2**：高敏捷性设置
- **配置文件 3**：效率/滑行设置

## 价格

在 **PID 调整** 选项卡中配置速率。 For ornithopters, start with conservative rates — flapping dynamics amplify control inputs:
- RC 速率：0.80–1.00
- 超级率：0.60–0.70
- 世博会：0.20–0.40
# STM32F407_HAL_Template

STM32F407 HAL库模板工程：工程中只保留与特定应用不相关的通用代码。

### 文件夹结构

```c
|--App /* 应用代码 */
|  |--Inc
|  |
|--Bsp /* 板级支持包 */
|  |--Inc
|  |  |--clock.h
|  |  |--delay.h
|  |  |--dwt.h
|  |  |--usart.h
|  |  |--serial.h
|  |--clock.c
|  |--delay.c
|  |--dwt.c
|  |--usart.c
|  |--serial.c
|  |
|--Config /* 配置文件 */
|  |--stm32f4xx_hal_conf.h
|  |
|--Doc /* 文档 */
|  |--readme.txt
|  |
|--Libraries /* 库 */
|  |--CMSIS
|  |  |--system_stm32f4xx.c/h
|  |  |--startup_stm32f407xx.s
|  |--STM32F4xx_HAL_DRIVER
|  |  |--Inc
|  |  |  |--stm32f4xx_hal_xxx.h
|  |  |  |--stm32f4xx_ll_xxx.h
|  |  |--Src
|  |  |  |--stm32f4xx_hal_xxx.c
|  |  |  |--stm32f4xx_ll_xxx.c
|  |
|--Project
|  |--project.uprojx
|  |
|--Usr
|  |--Inc
|  |  |--main.h
|  |  |--stm32f4xx_it.h
|  |--main.c
|  |--stm32f4xx_it.c
|  |--stm32f4xx_hal_msp.c
|  |
|--Utils /* 通用文件 */
|  |--Inc
```

### 工程结构

```c
|--STM32F407
|  |--CMSIS
|  |--STM32F4xx_HAL_Driver
|  |--Utils
|  |--Bsp
|  |--App
|  |--Config
|  |--User
|  |--Doc
```

### 更新

---

**`2020-03-26 V0.0.1`**

1. 构建工程结构，创建工程
2. 实现通用的板级支持包功能，目前Bsp部分包含硬件代码层和硬件抽象层。
   - 微秒延时函数：通过DWT和SysTick两种方式实现，DWT精度更高，但必须要执行dwt初始化函数，且程序下载到单片机后要复位才能运行。
   - 利用循环队列和串口中断发送接收实现带缓存的串口处理机制，并建立硬件抽象层，后续开发只需针对于通信层。
   - 时钟：提供获取当前系统运行的时间，包括ms时间和us时间。

---


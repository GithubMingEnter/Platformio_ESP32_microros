# Platformio_ESP32_microros

## RUN




打开`platform.ini`,添加MicroROS的依赖。

```C
[env:featheresp32]
platform = espressif32
board = featheresp32
framework = arduino
lib_deps = 
    https://gitee.com/ohhuo/micro_ros_platformio.git

```





```C
/**
 *  Initializes rcl and creates some support data structures.
 *  Initializes clock as RCL_STEADY_TIME.
 *  * <hr>
 * Attribute          | Adherence
 * ------------------ | -------------
 * Allocates Memory   | Yes (in RCL)
 * Thread-Safe        | No
 * Uses Atomics       | No
 * Lock-Free          | Yes
 *
 * \param[inout] support a zero-initialized rclc_support_t
 * \param[in] argc number of args of main
 * \param[in] argv array of arguments of main
 * \param[in] allocator allocator for allocating memory
 * \return `RCL_RET_OK` if RCL was initialized successfully
 * \return `RCL_RET_INVALID_ARGUMENT` if any null pointer as argument
 * \return `RCL_RET_ERROR` in case of failure
 */
RCLC_PUBLIC
rcl_ret_t
rclc_support_init(
  rclc_support_t * support,
  int argc,
  char const * const * argv,
  rcl_allocator_t * allocator);

```





```C
#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

void setup()
{
  Serial.begin(115200);
  // 设置通过串口进行MicroROS通信
  set_microros_serial_transports(Serial);
  // 延时时一段时间，等待设置完成
  delay(2000);
  // 初始化内存分配器
  allocator = rcl_get_default_allocator();
  // 创建初始化选项
  rclc_support_init(&support, 0, NULL, &allocator);
  // 创建节点 hello_microros
  rclc_node_init_default(&node, "hello_microros", "", &support);
  // 创建执行器
  rclc_executor_init(&executor, &support.context, 1, &allocator);
}

void loop()
{
  delay(100);
  // 循环处理数据
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
}


```



连接开发板，编译下载，如果遇到端口被占用，多半是你的microros_agent没有关闭，Ctrl+C打断运行再次尝试。

容器命令

```C
 sudo docker run -it --rm -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:foxy serial --dev /dev/ttyUSB0 -v6

```

注意要使用对应的ROS2版本,和你所链接的端口


成功

![](https://secure2.wostatic.cn/static/917pBvqnUK3hsyaAjgBAQX/image.png?auth_key=1713148005-3VnQLNBvc9e4WXDumgFpUu-0-b5cb9403fb07cc565a0b48cd312a2d0a)






# ref
https://fishros.com/d2lros2/#/humble/chapt14/basic/2.%E4%BD%A0%E7%9A%84%E7%AC%AC%E4%B8%80%E4%B8%AAMicroROS%E8%8A%82%E7%82%B9?id=_12-%e6%b7%bb%e5%8a%a0%e4%be%9d%e8%b5%96
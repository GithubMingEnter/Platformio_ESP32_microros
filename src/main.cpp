#include <Arduino.h>
#include<micro_ros_platformio.h>
#include <rcl/rcl.h>
#include<rclc/rclc.h>
#include<rclc/executor.h>

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;






// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //micros communication by serial
  set_microros_serial_transports(Serial);
  delay(2000);
  //init memory allocator
  allocator = rcl_get_default_allocator();
  //create initial term
  rclc_support_init(&support,0,NULL,&allocator);
  //create node hello_microros
  rclc_node_init_default(&node,"hello_microros","",&support);
  //create executor
  rclc_executor_init(&executor,&support.context,1,&allocator);

  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:

  //handle data loop
  rclc_executor_spin_some(&executor,RCL_MS_TO_NS(100));
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
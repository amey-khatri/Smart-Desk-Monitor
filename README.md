# Smart-Desk-Monitor
Smart Desk Monitoring system to promote healthy practices during extended periods spent at a desk. 

![alt tag](http://placecorgi.com/1200/650)

## How It's Made:

**Tech used:** C, C++, FreeRTOS, ESP-IDF

The motivation for this project stemmed from my countless hours spent studying at a desk during my first year of university. I would get frequent, seemingly inexplicable, headaches while studying for longer periods of time. Eventually I realized that while studying I would forget to drink water, leaving myself dehydrated for hours at a time. Thus I created this smart desk monitor to track time spent at my desk and to remind me to drink water, stand periodically, and not slouch during the time spent at my desk. The monitor is built off of an ESP32 microcontroller integrated with an IMU, an ultrasonic sensor, and a small OLED display alongside smaller components linked through a breadboard. The device monitors proximity to the sensor and starts tracking once the threshold is met. Every 20 minutes the user is alerted to drink water with an audible signal and a written message on the display. The same happens every 40 minutes, only now reminding the user to stand periodically. The device also constantly tracks posture via an IMU unit worn on the neck by the user. If the IMU detects a slouch angle past the set threshold, an audible signal sounds until rectified. A button is used to reset the reference angle for posture tracking.

## Optimizations

At first this project was implemented using the basic setup and loop functions found in any microcontroller code. However a problem quickly became evident in that the loop functionality could not track multiple values and timers simultaneously. Whatever function was running at the time would take full priority, and all other functionaliy would be suspended. The solution to this was using a real-time operating system via FreeRTOS. With FreeRTOS, I was able to create a task for each function the desk monitor had to perform. These tasks could then be started, stopped, and ran simultaneously whenever code logic dictated them to do so. This enabled predictable and timely execution of tasks, as is required in embedded systems, robotics, and industrial automation. By managing resource scheduling and providing a structured environment, the RTOS enhanced responsiveness, simplified development, and enabled more complex functionalities that would have been difficult or impossible without it. 


## Lessons Learned:

This project not only showed me the immense benefits of using RTOS, but specifically how important implementation is in regards to an end goal. While there may be 50 ways to do the same thing, there is most definetly a correct way to do it for the given situation. Looking then at actually using the monitor, it's made me realize just how bad my desk habits are. I slouch very often, which I now know due to the constant alerts given. My water intake as increased significantly, going from 1 bottle in the entire day to at least 2, possibly 3. I also now stand more often, and thus actually feel my muscles being less stiff at the end of the day and I find myself with more energy leftover.





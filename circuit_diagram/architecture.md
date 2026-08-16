# System Architecture

```text
                    USER
                     |
                     v
             +---------------+
             | Hand Sensor   |
             | HC-SR04       |
             +-------+-------+
                     |
                     v
              +-------------+
              | Arduino UNO |
              | Control     |
              | Logic       |
              +------+------+ 
                     |
          +----------+----------+
          |          |          |
          v          v          v
       Servo      Level       Alert
       Control    Sensor      System
          |          |          |
          v          v      +---+---+
        Lid       Fill %    LED   Buzzer
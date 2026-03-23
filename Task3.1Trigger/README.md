Task 3.1P - Trigger and Notification System.

System Description
This is a system that is based on an Arduino Nano 33 IoT and a BH1750 light sensor to detect the amount of light reaching the terrarium of Linda. The system notifies Telegram via IFTTT when the
amount of light exceeds a chosen threshold, which tells the system that there is now light and the sun has begun to shine. In case the level of light drops below the threshold, the system informs
the user that the sunlight ceased and issues another notification. This enables automatic monitoring of the amount of sunlight that is exposed to the terrarium.

Components Used
Arduino Nano 33 IoT
BH1750FVI light sensor
Breadboard
Jumper wires
Wi-Fi connection
IFTTT Webhooks
Telegram

Circuit Connections
BH1750 VCC - Arduino 3.3V
BH1750 GND - Arduino GND
BH1750 SDA - Arduino A4
BH1750 SCL - Arduino A5
BH1750 ADO - not connected

Explanation of the Code

Sensor Setup
The BH1750 light sensor is initalized into the program by means of I2C communication. The sensor constantly determines the amount of ambient light in lux.

Wi-Fi Connection
The Arduino has a connection to the local Wi-Fi network to enable it to make web requests to IFTTT. In case Wi-Fi connection is lost, the program tries to connect again.

Trigger Mechanism
The light level is contrasted with a set limit. In case lux value is larger or equal than the threshold and the system was in a dark state, the program switches the state to sunlight present
and causes the sunlightstarted event. When the value of lux decreases and the system was in sunlight state in the past, the program replaces the state with sunlight absent and the sunlightstopped event occurs.

Notification Mechanism
Upon the fulfillment of a trigger condition, the Arduino will send an HTTPS GET request to the IFTTT Webhooks service with the appropriate event name and Webhooks key. An event is then sent out by
IFTTT as a Telegram message.

State Control
The presence or absence of sunlight is an additional variable which is stored in a Boolean variable to remember whether it is in the presence or absence. This eliminates the transmission of repeated
notifications in each loop cycle with the light level held to the same state.

Testing
The system was also tested by shining a phone torch on to the sensor (BH1750) and then covering it again. On an increase in the amount of light more than the threshold, a message was received by
Telegram stating that the sun had begun. Once the light intensity fell below the threshold, a second message via Telegram was received which said that the sunlight had ceased. This proved that
the trigger logic was functioning properly and the notification mechanism was functioning properly.

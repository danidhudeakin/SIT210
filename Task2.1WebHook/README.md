Task 2.1P - ThingSpeak to Sensor Data.

System Description
This system operates on an Arduino Nano 33 IoT to acquire temperature and light readings of sensors that are connected via it and sends the results to ThingSpeak after every 30s. The sensor that reads temperature is the DHT11 sensor, and the sensor that reads the light intensity is the BH1750FVI light sensor. The uploaded information is presented on ThingSpeak in the form of graphs to track the conditions in the room.

Components Used
Arduino Nano 33 IoT
DHT11 temperature sensor
BH1750FVI light sensor
Breadboard
Jumper wires
Wi-Fi connection
ThingSpeak channel

Explanation of the Code

Sensor Setup
The program is used to initialize the DHT11 sensor and BH1750 light sensor. The DHT11 goes to the digital pin, D2 and the BH1750 is connected using the I2C communication between SDA and SCL.

Wi-Fi Connection
The Arduino is connected to the local Wi-Fi network with the help of the supplied SSID and password. In case the connection goes dead, the system tries to reconnect itself.

Reading Sensor Data
The sensor is connected to the DHT11 sensor which measures the temperature and the BH1750 sensor which measures the light intensity. The readings are kept in variables and then uploaded.

Sending Data to ThingSpeak
The channel ID and Write API key helps in sending the value of the temperature to Field 1 and the light value to Field 2 of the ThingSpeak channel.

Time Interval
The data is uploaded after 30 seconds, and this fits the task requirement and enables one to monitor changes in the environment over a period.

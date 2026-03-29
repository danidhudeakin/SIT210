Task 2.1P - ThingSpeak to Sensor Data.

System Description
This system depends on the Arduino Nano 33 IoT to retrieve temperature and light data of the connected sensors and transmit the readings to ThingSpeak after every 30 seconds. DHT11 sensor is utilized to detect temperature, and BH1750FVI sensor is utilized to detect the light intensity. The uploaded data can then be presented on ThingSpeak in form of graphs to be able to watch the conditions in the room with time.

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
The sensors are initialized in the setupSensors() function where both sensors are initialized by the program. The sensor DHT11 is attached to the digital pin D2 and the sensor BH1750 is connected to the I2C communication with the help of SDA and SCL.

Wi-Fi Connection
The Arduino gets linked to the Wi-Fi network of the local area by using the connectWiFi() command. In case of loss of the Wi-Fi connection in the middle of operation, ensureWiFiConnected() function is used to check the status and automatically connect again.

Reading Sensor Data
Separate functions are used to process the sensor readings. ReadTemperature() and readLightLevel() functions read the temperature of the sensor and the light intensity of the sensor respectively. It simplifies the process of testing the code.

Sending Data to ThingSpeak
The uploadToThingSpeak() function has the role of uploading the sensor values to the ThingSpeak channel. ThingSpeak.setField(1, temperature) is used to set the temperature in Field 1 and ThingSpeak.setField(2, lightLevel) is used to set the light level in Field 2. The information is uploaded via the ThingSpeak.writeFields(channelID, writeapikey).

Serial Monitoring
The printSensorData () function displays the temperature and light measurements in the Serial Monitor. This also helped in testing whenever the sensors were functioning properly and then examine the uploaded information in ThingSpeak.

Time Interval
The data are uploaded by the system at 30 second intervals. This fulfils the task requirement and enables the sensor values to be followed through the time with the help of the graphs on ThingSpeak.

Modular Programming
Modular programming was evidenced by breaking the program into smaller task-oriented functions including sensor setup, Wi-Fi connection, sensor reading, serial output and data upload. This simplified the code to read, debug and edit as opposed to putting all the logic within the loop() function.

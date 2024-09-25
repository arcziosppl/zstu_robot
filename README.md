# ESP8266 Wi-Fi Controlled Robot

This project implements a Wi-Fi-controlled robot using an ESP8266 microcontroller. The robot can be operated through a web interface that supports gamepad controls, and it includes an ultrasonic distance sensor and a servo motor for a camera system.

## Features

- **Wi-Fi Control**: The robot is controlled via a web interface served by the ESP8266, allowing the user to move the robot forward, backward, left, or right.
- **Ultrasonic Distance Sensor**: An ultrasonic sensor measures the distance from obstacles, and the data is displayed in real-time on the web interface.
- **Camera Servo Control**: A servo motor controls the orientation of a camera, with the angle adjustable via gamepad or web commands.
- **Gamepad Support**: The robot can be controlled using a connected gamepad, making navigation more intuitive.
- **Real-time Distance Display**: The distance measured by the ultrasonic sensor is updated on the interface every 100 milliseconds.

## Components

- **ESP8266**: The microcontroller that manages the Wi-Fi connection and controls the robot.
- **Servo Motor**: Controls the angle of the camera.
- **Ultrasonic Sensor**: Measures the distance from obstacles to avoid collisions.
- **DC Motors**: Drive the robot forward, backward, and turn left or right.
- **Gamepad**: Used for controlling the robot via a web interface.

## Setup

1. **Hardware Connections**:
   - Connect the ultrasonic sensor's `trigPin` and `echoPin` to the ESP8266.
   - Connect the DC motors to pins `in1`, `in2`, `in3`, and `in4` for motor control.
   - Attach the servo motor to control the camera.
   
2. **Software Configuration**:
   - Fill in your Wi-Fi credentials in the `ssid` and `password` variables.
   - Define the necessary pin configurations in the `config.h` file.
   - Upload the code to the ESP8266 using the Arduino IDE.

3. **Web Interface**:
   - The robot serves a web page at the ESP8266's IP address. The interface includes:
     - A live distance display.
     - Gamepad controls for navigation.
     - Servo control for the camera.
     - Embedded iframe with Google search functionality.

## API Endpoints

The ESP8266 hosts several routes to control the robot:

- `/distance`: Returns the current distance from the ultrasonic sensor.
- `/for`: Moves the robot forward.
- `/back`: Moves the robot backward.
- `/left`: Turns the robot left.
- `/right`: Turns the robot right.
- `/stop`: Stops the robot's movement.
- `/camera?value=<angle>`: Adjusts the camera's angle by controlling the servo motor.

## Gamepad Controls

The robot can be controlled via a connected gamepad using the following mappings:

- **Left Stick X-axis**: Controls left/right movement.
- **Left Stick Y-axis**: Controls forward/backward movement.
- **Right Stick**: Adjusts the camera angle.

## Web Interface Preview

The interface includes a distance indicator, directional arrows, and a Google search embedded in an iframe for convenient browsing while controlling the robot.

![Web Interface](https://cdn.icon-icons.com/icons2/1648/PNG/512/10103robotface_109992.png)

---

## License

This project is open-source and free to modify.

## Credits

Developed by Artur Meus.

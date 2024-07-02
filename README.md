Vehicle Heavy Weight Monitoring and Accident Prevention System
📌 Overview
This project implements an automated system to monitor vehicle weight and prevent accidents due to overloading. It uses RFID technology to identify vehicles, a load cell to measure weight, and controls access through a servo motor-operated barrier.
🚀 Features

RFID-based vehicle identification
Real-time weight measurement using a load cell
LCD display for user feedback
Automated barrier control
Overload prevention

🛠️ Hardware Components

Arduino board (e.g., Arduino Uno)
RFID reader (MFRC522)
Load cell with HX711 amplifier
LCD display (I2C interface)
Servo motor
LEDs and buzzer (optional)

📚 Libraries Used

MFRC522
HX711
LiquidCrystal_I2C
Servo
SPI
Wire

🔧 Setup and Configuration

Connect the hardware components to the Arduino board:

RFID reader: SS_PIN to 10, RST_PIN to 5
Load cell: DOUT_PIN to 2, SCK_PIN to 3
LCD: SDA and SCL pins (I2C)
Servo motor: Signal pin to 9


Install the required libraries through the Arduino IDE Library Manager.
Upload the provided code to your Arduino board.
Calibrate the load cell for accurate weight measurements.
Program RFID tags with vehicle weight limits.

💻 Usage

Power on the system.
The LCD will display a welcome message.
When a vehicle approaches:

Scan the vehicle's RFID tag.
The system will read the weight limit from the tag.
The load cell will measure the actual vehicle weight.
If the weight is within the limit, the barrier will open.
If overloaded, the system will display a warning and keep the barrier closed.



🔍 Code Structure
The main code integrates all components:

RFID reading functions
Weight measurement
LCD display control
Servo motor control for the barrier

Separate sections are provided for individual component testing and calibration.
⚙️ Customization

Adjust the extractInteger function to match your RFID data format.
Modify the weight calculation in the actualWeight variable to fit your load cell characteristics.
Change the servo motor angles for opening and closing the barrier.

🚧 Troubleshooting

Ensure all connections are secure.
Check serial output for debugging information.
Verify that the RFID tags are programmed correctly.
Calibrate the load cell if weight measurements are inaccurate.

🤝 Contributing
Contributions to improve the system are welcome! Please follow these steps:

Fork the repository
Create a new branch
Make your changes
Submit a pull request

📄 License
This project is open-source and available under the MIT License.

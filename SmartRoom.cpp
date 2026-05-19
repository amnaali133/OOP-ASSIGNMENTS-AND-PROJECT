#include<iostream>
#include<string>
using namespace std;
//device class
class Device {
private:         //access specifiers
	string name;
	bool isOn;
	int brightness;
public:
	Device() {              //default constructor
		name = "Unknown";
		isOn = false;
		brightness = 50;
	}
	Device(string n, bool status, int b) {   // overloaded constructor
		name = n;
		isOn = status;
		if (b >= 0 && b <= 100)//validation to ensure brightness between 0 and 100
			brightness = b;
		else
			brightness = 50;

	}
	~Device() {         //destructor
		cout << "Device " << name << " is being removed" << endl;
	}
	//setter functions
	void setName(string n) {
		name = n;
	}
	void setBrightness(int b) {
		if (b >= 0 && b <= 100) //validation check
			brightness = b;
			else
				cout << "brightness must be between 0 and 100" << endl;
	}
	void turnOn() {
		isOn = true;
	}
	void turnOff() {
		isOn = false;
	}
	//Getter functions
	string getName()const {
		return name;
	}
	int getBrightness()const {
		return brightness;
	}
	bool getStatus()const {
		return isOn;
	}
	void showInfo()const {           //display device details
		cout << "Name:" << name << ",Status:" << (isOn ? "ON" : "OFF") << ",Brightness:" << brightness << endl;
	}

};
//Room class
class Room {
private:
	string roomName;//name of the room
	Device devices[5];//array to store maximum 5 devices
	int count;//current number of devices
public:
	Room(string name) {     //constructor
		roomName = name;
		count = 0;
	}
	~Room() {      //destructor 
		cout << "Room" << roomName << "manager closed" << endl;
	}
	void addDevice(Device d) {//add device
		if (count < 5) {
			devices[count] = d;//store device in array
			count++;//increase device count
			cout << "Device added successfully" << endl;
		}
		else {
			cout << "Room is full. Cannot add more devices." << endl;
		}
	}
	void showAllDevices() const {//show all the devices
		if (count == 0) {
			cout << "No devices in the room" << endl;
			return;
		}

		for (int i = 0; i < count; i++) {
			devices[i].showInfo();
		}
	}
	int findDevice(string name)const {//find device by name and return index
		for (int i = 0;i < count;i++)
		{
			if (devices[i].getName() == name)
				return i;// return index if found
		}
		return -1;//return -1 if not found
	}void toggleDevice(string name) {//turns device ON/OFF
		int index = findDevice(name);
		if (index != -1)
		{
			if (devices[index].getStatus())
				devices[index].turnOff();
			else
				devices[index].turnOn();
			cout << "Devices toggled of successfully!" << endl;

		}
		else
		{
			cout << "Devices not found" << endl;
		}
	}
	void setDeviceBrightness(string name, int brightness) {//change brightness
		int index = findDevice(name);
		if (index != -1)
		{
			devices[index].setBrightness(brightness);
		}else
		{
			cout << "Devices not found" << endl;
		}
	}
};
int main() {
	string roomName;
	cout << "Enter room name:";
	getline(cin, roomName);//used to take full line inputt including spaces
	Room myRoom(roomName);
	int choice;
	do {
		cout << "\n ===Smart Room Manager===\n";//menu 
		cout << "1. Add a Device\n";
		cout << "2. Show All Devices\n";
		cout << "3. Turn Devices on/off\n";
		cout << "4. Change Brightness\n";
		cout << "5. Exit\n";
		cout << "Enter Choice:";
		cin >> choice;
		cin.ignore();//clear leftover newline from input buffer
		if (choice == 1) {
			string name;
			int brightness;
			cout << "Enter device Name:";
			getline(cin, name);
			cout << "Enter brightness (0-100):";
			cin >> brightness;
			cin.ignore();
			Device d(name, false, brightness);
			myRoom.addDevice(d);
		}
		else if (choice == 2) {
			myRoom.showAllDevices();
		}
		else if (choice == 3) {
			string name;
			cout << "Enter device Name:";
			getline(cin, name);
			myRoom.toggleDevice(name);
		}
		else if (choice == 4) {
			string name;
			int brightness;
			cout << "Enter device Name:";
			getline(cin, name);
			cout << "Enter new brightness (0-100):";
			cin >> brightness;
			cin.ignore();
			myRoom.setDeviceBrightness(name, brightness);
		}
		else if (choice == 5) {
			cout << "Exiting program" << endl;

		}
		else {
			cout << "Invalid choice" << endl;
		}
	} while (choice != 5);
	return 0;
}
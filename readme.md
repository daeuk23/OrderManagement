# Customer Order Management

## purpose 
This program simulates the entire process of assembling and processing products by taking in CustomerOrders and passing them through multiple Workstations.   
It provides a way to track customer orders and products, while managing the workflow of the workstations. The program is implemented in C++.  

## Project Period
May 12th ~ May 24th 2024 : Individually Ended
contact: Email : a24738598@gmail.com  

## Feature for user
**Ordering system** : Allowed adding new sorce or new method    
**Data handling** : easily input new data of items and order  
**Station-based storage systems** : Significantly less likely to result in duplicate data  
**Multiple Station Management Features** : by Line Manager file  

## Why this  
**Memory efficiency** -> Perfectly allocated and deleted memory, good for developing similar types of programs  
**Less risk of duplicate data** -> Similar units, such as station, linemanager, and workstation,   
are very unlikely to cause data confusion or error by separating them in different roles  
**Classify each function** into small, easy-to-understand units  
**High cohesion + high consistency** : good maintanence and high resuability  

## Operable Files

**Main**
[main.c](rcs/main.cpp): Simplified interface request user new input of order or viewing item info  

**CustomerOrder**  
`CustomerOrder` class : Provides tracking of customer order information and item processing  
[CustomerOrder.c](rcs/CustomerOrder.cpp), [Header](rcs/CustomerOrder.h)  

**LineManager**  
`LineManager` class : Classes representing line managers which act as controllers to control the flow of production lines and manage the order of each workstation  
[LineManager.c](rcs/LineManager.cpp), [Header](rcs/LineManager.h)  

**Station**  
`Station` class : Represents the station that manages one item on the production line.  
Each station has a specific item and performs quantity management, serial number management, information output, etc  
[Station.c](rcs/Station.cpp), [Header](rcs/Station.h)  

**Status**  
`Workstation` class : It serves as a working station for the production line, is responsible for the logic  
of processing CustomerOrder and delivering it to the next station, and is responsible for dealing with specific units in the assembly line.  
[Workstation.c](rcs/Workstation.cpp), [Header](rcs/Workstation.h)  

**Utils**  
`utilities` class : Additional function for effeciency.  
[Utilities.c](rcs/Utilities.cpp), [Header](rcs/Utilities.h)  

## Text Files  
[AssmblyLine](txt/AssemblyLine.txt), [CustomerOrder](txt/CustomerOrders.txt), [Station1](txt/Stations1.txt), [Station2](txt/Stations2.txt)

## Compile In remote 
G++ compiler required  

```bash
g++ -Wall -std=c++17 -g -o main main.cpp CustomerOrder.cpp LineManager.cpp Station.cpp Utilities.cpp Workstation.cpp
```
Using SSH will be good

## How to test local

### 1. Clone repo

Clone my repo to your local

```bash
git clone https://github.com/daeuk23/OrderManagement.git
cd orderManagement
```  
### 2. compile

compile the tester files

```bash
cd orderManagement
g++ test_filename.cpp -o test_run
./test_run
```
=> modify test_filename to actual tester name

### 3. run txt files
```bash
./main Stations1.txt Stations2.txt CustomerOrders.txt AssemblyLine.txt
```
make sure to put txt files on same folder.  

## Example Output  
Comare with It : [Example](txt/sampleoutput.txt)

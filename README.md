# esp32_car
An esp32-control car, featuring a liftable robotic arm, Mecanum wheels and BLE control(TBD). 

## for developer
```
cd <your esp folder>
git clone https://github.com/A-lexisL/esp32_car.git
cd esp32_car
git checkout demo #change to the demo branch
```
In the demo branch, you can do some tests to get familiar with the esp32.  

After the basic settings in main branch are done, create a dev branch.
```
git checkout main #switch to main branch
git checkout -b <devbranch> 
git push -u origin <devbranch>
``` 
In the dev branch, develop the specific function (TBD).

## pin
please refer to the pin.xlsx for the pin map.  
**(Attention: please do not modify pin.xlsx)**
# RaspberryPIModules
In order from when I worked on them to familiarize myself with embedded systems programming by programming various functions for a pre-configured raspberry pi: 

# OnAndOffx5.c 
This file is to be installed as a Kernel module into the pi at your disposal. To run it, first ensure that you have set up a pair of SSH authentication keys for the pi
and your workstation. Then ssh into your pi using the command `ssh -Y pi@{IP of the pi device}`. Keep that terminal window open for later. Next, in a separate terminal window dedicated to your workstation / machine, run `mount.rpifs {IP of the pi device}` to mount the pi's file system into a folder named rpifs on your workstation. You will open on your workstation the file you desire from that folder--OnAndOffx5.c in this case--to edit it. Once you've saved changes to the file, then you will open the raspberry pi terminal from earlier. You will enter the same directory in rpifs to access the same file, and compile the file, in this case with `gcc OnAndOffx5.c`. This will generate a kernel module with the extension .ko. You will then install that file onto the pi like so: `sudo insmod OnAndOffx5.ko`, which initiates the actual running of the process. To uninstall the kernel module, run `sudo rmmod OnAndOff`. Note that there is no need to add the extension the second time. The file OnAndOffx5.c merely turns on and off all four LEDs of the pi five times. I made it to understand what kernel modules are and how to use them.

# ToggleLEDs.c
This is another kernel module, so follow the same instructions above to get it to run on the pi. This one allows a bit of user interaction with the pi by associating each LED with a button with which a user can turn the LED on. The fifth and last button turns off all four LEDs when pressed. 

# MatrixConvolutionAnalysis.zip
This and every other file after it do not contain kernel modules. The *.c files are to be compiled on the workstation inside the mounted rpifs directory, and were originally meant to be run on the pi, though are also compatible with suitable architectures (though they may still not run exactly as meant to). With this .zip file in particular, extract the contents to the directory of your choosing. Inside this directory, you will find MatrixConvolutionAnalysis.c, 2x10.txt, and 20x10.txt. To run, use the command `gcc MatrixConvolutionAnalysis.c -lpthread -o mca` to compile then `./mca {file of your choice here}`, where `file of your choice here` is any space separated variable file in the following format: 
`{rows of matrix} {columns of matrix}
{matrix}
{rows of filter vector (=1)} {columns of filter vector}
{filter vector}
`
2x10.txt and 20x10.txt are provided as example files. Upon running the code, you will see in the terminal an analysis of three different convolutions of the same matrix by the same (horizontal) filter vector as given in the file you supplied on the command line. Convolution one was single threaded, convolution two associated each row of the matrix with a thread and convolved simultaneously, and convolution three associated each cell of the matrix with a thread and convolved simulataneously. I did this to see which was faster. I figured that Convolution three would be, given that it should be sacrificing so much space complexity with all the thread creation overhead in order to reduce time complexity by doing so many simultaneous operations, but in fact, convolution 2 was the fastest on average, as you may test for yourself. I suspect this is due to the thread creation itself having not just spatial overhead, but also temporal overhead that adds up. I did not consider this minmaxxing. 

# PeriodicRTFileSync.zip
Extract the contents of this one to the desired working directory and you will see PeriodicRTFileSync.c, and two example files named first.txt and second.txt. The first of these files contains code that implements a periodic real time task. The tasks themselves are to 
1) take data from a file named first.txt (hardcoded), which contains the odd numbered lines of a text
2) take data from a file named second.txt (hardcoded), which contains the even numbered lines of a text
3) Synchronize the writes in real time from the other two tasks into a shared buffer which is to contain the correctly ordered full text to be presented back to the user in the terminal.
Each of these tasks is assigned its own thread, and overall, I learned a lot from this one, as it was my first approach to periodic real time tasks.
To run, enter on the command line: `gcc PeriodicRTFileSync.c -lpthread -lrt -o filesync` to compile, then `sudo ./filesync` to see the results in the terminal.

# SimpleTrafficLight.c 
I used this program to learn about the wiringPI library, which was much easier on the eyes and moderately more pleasant to use than gpio.h for interacting with the pi. Upon running `gcc SimpleTrafficLight.c -lwiringPi -lpthread -o traffic_light` and then `sudo ./traffic_light`, the red and yellow LEDs will alternate indefinitely, until button one is pressed, which will activate the green light. 

# MultiThreadedTrafficLightsWithPriority.c 
This is quite similar to the above, but I experimented (successfully) with adding a thread per light, which were each assigned scheduling priorities. The permutation of priorities which ended up reproducing the result seen in running SimpleTrafficLight.c were acquired via repeated experimentation, and is as follows: Red < (Yellow == Green). It was a bit of a journey to figure out exactly why that set of priorities worked in the end but I got it worked out. Enter `gcc MultithreadedTrafficLightsWithPriority.c -lwiringPi -lpthread -o modded_traffic_light` and then `sudo ./modded_traffic_light` to run the code on the pi. 

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>  
#include <linux/gpio.h>     
#include <linux/interrupt.h>
#include <linux/err.h>
#define RED_LED 2
#define YELLOW_LED 3
#define GREEN_LED 4
#define BLUE_LED 5
MODULE_LICENSE("GPL");
 
int when_installed(void)
{
    printk(KERN_INFO "MODULE INSTALLED\n"); 
    if (gpio_is_valid(RED_LED))
    {
        gpio_request(RED_LED, "Red LED"); 
    }
    if (gpio_is_valid(YELLOW_LED))
    {
        gpio_request(YELLOW_LED, "Yellow LED"); 
    }
    if (gpio_is_valid(GREEN_LED))
    {
        gpio_request(GREEN_LED, "Green LED"); 
    }
    if (gpio_is_valid(BLUE_LED))
    {
        gpio_request(BLUE_LED, "Blue LED"); 
    }
    for (int i = 0; i < 5; i++)
    {
       
       gpio_direction_output(RED_LED, 0);
       gpio_direction_output(YELLOW_LED, 0);
       gpio_direction_output(GREEN_LED, 0);
       gpio_direction_output(BLUE_LED, 0);
       mdelay(250); 
       gpio_direction_output(RED_LED, 1);
       gpio_direction_output(YELLOW_LED, 1);
       gpio_direction_output(GREEN_LED, 1);
       gpio_direction_output(BLUE_LED, 1);
       mdelay(250); 
    }
    return 0;
}
void when_removed(void)
{
    gpio_free(RED_LED);
    gpio_free(YELLOW_LED); 
    gpio_free(GREEN_LED); 
    gpio_free(BLUE_LED); 
    printk(KERN_INFO "MODULE REMOVED\n");
}
module_init(when_installed);
module_exit(when_removed);
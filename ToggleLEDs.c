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
#include <linux/jiffies.h>
MODULE_LICENSE("GPL");

int InputPin1 = 16, OutputPin1 = 2;
int InputPin2 = 17, OutputPin2 = 3;
int InputPin3 = 18, OutputPin3 = 4; 
int InputPin4 = 19, OutputPin4 = 5;
int InputPin5 = 20; 
int GPIO_irqNumber1;
int GPIO_irqNumber2; 
int GPIO_irqNumber3; 
int GPIO_irqNumber4; 
int GPIO_irqNumber5; 
//Interrupt handler for InputPin1. This will be called whenever there is a raising edge detected. 
static irqreturn_t gpio_irq_handler1(int irq,void *dev_id) 
{
 
    disable_irq(InputPin1);
    // Turn on LED 1 
        
    gpio_direction_output(OutputPin1, 1); 
    enable_irq(InputPin1);
    printk("Interrupt1 handled\n");
    return IRQ_HANDLED;
}
//Interrupt handler for InputPin2. This will be called whenever there is a raising edge detected. 
static irqreturn_t gpio_irq_handler2(int irq,void *dev_id) 
{
 
    disable_irq(InputPin2);
    // Turn on LED 2 
        
    gpio_direction_output(OutputPin2, 1); 
    enable_irq(InputPin2);
    printk("Interrupt2 handled\n");
    return IRQ_HANDLED;
}
//Interrupt handler for InputPin3. This will be called whenever there is a raising edge detected. 
static irqreturn_t gpio_irq_handler3(int irq,void *dev_id) 
{
 
    disable_irq(InputPin3);
    // Turn on LED 3 
        
    gpio_direction_output(OutputPin3, 1); 
    enable_irq(InputPin3);
    printk("Interrupt handled\n");
    return IRQ_HANDLED;
}
//Interrupt handler for InputPin4. This will be called whenever there is a raising edge detected. 
static irqreturn_t gpio_irq_handler4(int irq,void *dev_id) 
{
 
    disable_irq(InputPin4);
    // turn on LED 4 
        
    gpio_direction_output(OutputPin4, 1); 
    enable_irq(InputPin4);
    printk("Interrupt handled\n");
    return IRQ_HANDLED;
}
//Interrupt handler for InputPin5. This will be called whenever there is a raising edge detected. 
static irqreturn_t gpio_irq_handler5(int irq,void *dev_id) 
{
 
    disable_irq(InputPin5);
    // Turn off all LEDs  
        
    gpio_direction_output(OutputPin1, 0); 
    gpio_direction_output(OutputPin2, 0); 
    gpio_direction_output(OutputPin3, 0); 
    gpio_direction_output(OutputPin4, 0); 
    enable_irq(InputPin5);
    printk("Interrupt handled\n");
    return IRQ_HANDLED;
}
/*
** Module Init function
*/ 
int mod_install(void)   // Call the default name
{
    // Configure the output and the input pins
    if (gpio_is_valid(InputPin1))
    {
        gpio_request(InputPin1, "Button1"); 
    }
    if (gpio_is_valid(InputPin2))
    {
        gpio_request(InputPin2, "Button2"); 
    }
    if (gpio_is_valid(InputPin3))
    {
        gpio_request(InputPin3, "Button3"); 
    }
    if (gpio_is_valid(InputPin4))
    {
        gpio_request(InputPin4, "Button4"); 
    }
    if (gpio_is_valid(InputPin5))
    {
        gpio_request(InputPin5, "Button5"); 
    }
    if (gpio_is_valid(OutputPin1))
    {
        gpio_request(OutputPin1, "Red LED"); 
        gpio_direction_output(OutputPin1, 0);
    }
    if (gpio_is_valid(OutputPin2))
    {
        gpio_request(OutputPin2, "Yellow LED"); 
        gpio_direction_output(OutputPin2, 0);
    }
    if (gpio_is_valid(OutputPin3))
    {
        gpio_request(OutputPin3, "Green LED"); 
        gpio_direction_output(OutputPin3, 0);
    }
    if (gpio_is_valid(OutputPin4))
    {
        gpio_request(OutputPin4, "Blue LED"); 
        gpio_direction_output(OutputPin4, 0);
    }
    //Get the IRQ number for our GPIO
    GPIO_irqNumber1 = gpio_to_irq(InputPin1);
    GPIO_irqNumber2 = gpio_to_irq(InputPin2);
    GPIO_irqNumber3 = gpio_to_irq(InputPin3);
    GPIO_irqNumber4 = gpio_to_irq(InputPin4);
    GPIO_irqNumber5 = gpio_to_irq(InputPin5);
    
    // Request the interrupt / attach handler
    //Enable (Async) Rising Edge detection
    //The last argument is a variable needed to identify the handler, but can be set to NULL
    if (request_irq(GPIO_irqNumber1,(void *)gpio_irq_handler1, 
    IRQF_TRIGGER_RISING,"Button1 Interrupt", NULL)) 
    {                    //device id for shared IRQ
        pr_err("Cannot register the IRQ ");
        gpio_free(InputPin1);
    }
    if (request_irq(GPIO_irqNumber2,(void *)gpio_irq_handler2, 
    IRQF_TRIGGER_RISING,"Button2 Interrupt", NULL)) 
    {                    //device id for shared IRQ
        pr_err("Cannot register the IRQ ");
        gpio_free(InputPin2);
    }
    if (request_irq(GPIO_irqNumber3,(void *)gpio_irq_handler3, 
    IRQF_TRIGGER_RISING,"Button3 Interrupt", NULL)) 
    {                    //device id for shared IRQ
        pr_err("Cannot register the IRQ ");
        gpio_free(InputPin3);
    }
    if (request_irq(GPIO_irqNumber4,(void *)gpio_irq_handler4, 
    IRQF_TRIGGER_RISING,"Button4 Interrupt", NULL)) 
    {                    //device id for shared IRQ
        pr_err("Cannot register the IRQ ");
        gpio_free(InputPin4);
    }
    if (request_irq(GPIO_irqNumber5,(void *)gpio_irq_handler5, 
    IRQF_TRIGGER_RISING,"Button5 Interrupt", NULL)) 
    {                    //device id for shared IRQ
        pr_err("Cannot register the IRQ ");
        gpio_free(InputPin5);
    }
    pr_info("Module Inserted!!!\n");
    return 0;
}
/*
** Module exit function
*/
void mod_uninstall(void) 
{
    //Remove the interrupt handlers
    free_irq(GPIO_irqNumber1,NULL);
    free_irq(GPIO_irqNumber2,NULL);
    free_irq(GPIO_irqNumber3,NULL);
    free_irq(GPIO_irqNumber4,NULL);
    free_irq(GPIO_irqNumber5,NULL);
    //Free the Pins
    gpio_free(InputPin1);
    gpio_free(OutputPin1);
    gpio_free(InputPin2);
    gpio_free(OutputPin2);
    gpio_free(InputPin3);
    gpio_free(OutputPin3);
    gpio_free(InputPin4);
    gpio_free(OutputPin4);
    gpio_free(InputPin5);
    printk("*************Module Removed**********\n");
}
 
module_init(mod_install);
module_exit(mod_uninstall);
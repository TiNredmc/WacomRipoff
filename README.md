# WacomRipOff
Interfacing with w9013 Wacom EMR chip on EMR pad taken from borken Halo keyboard belong to my YOGA Book.

# How I get it done ?
It's started from I was trying to replace the battery of my Yoga Book, but I broke my keyboard (sencond time). so I took that chance to reverse enginerring the Wacom EMR i2c pad. by probing with multi-meter to see the voltage, one that lower than 3.3 volt means that it's oscillating. Leter I use arduino uno as a SUMP logic analyzer. It turns out that It's running i2c at 1MHz, but I later tested with 100KHz and 400KHz, works just fine. so I continue to port the code from Linux to STM32. 

# The process(es) in easy way.
It's easy to explain, when the pen is in-range of EMR pad. the w9013 sends the interrupt to Host (STM32) by pulling INT pin low, this trigger STM23 and enter wacom_irq().
Inside the irq handler the MCU will semi-polling-ly read data from w9013. this is a workaround to fix the low speed i2c limitation of physical connection (That's why I'm not running at 1MHz). when we received data from w9013, just do some simple switch case and array copying and then send the proper HID packet (according to the HID descriptor I PAINFULLY wrote).

# The process(es) in HARD way.
Starting with USB, The USB HID standard is currently 17 years old (just one year yunger than 2021 me xD). it's painfully took me about one month to just understanding USB HID standard and how to write the proper HID descriptor, and to make entire thing works, I need to read Microsoft hardware guidelines :
```
https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/required-hid-top-level-collections
https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/windows-pen-states
https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/supporting-usages-in-digitizer-report-descriptors
https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/touch-and-pen-support
```
after that I need to write the HID descriptor and replace the one that came default in STM32 USB FS driver to be specific, HID descriptor is located at 
```
The descriptor array :
/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c line 318, identifier : HID_MOUSE_ReportDesc
The descriptor array SIZE :
/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc/usbd_hid.h line 49, identifier : HID_MOUSE_REPORT_DESC_SIZE (p.s. this one is = 93)
```
I explained some of bits on my hackaday project [here](https://hackaday.io/project/180207-wacomi2c-hacked) Including the HID packet too. after got the USB working, next is to write the w9013 initializer function and the IRQ handler to quickly grab the data off the Wacom EMR pad. I only need 7 bytes of important data. including pen/eraser detection, in-rage detection, barrel button (2 buttons), XY coordinates and pressure report. data is being processed in switch() case: for the pen detection+button press, simple byte2=byte1 copy with X coordinate and pressure, Y coordinate need some inverting tricky to workaround the flipped Y axis. all left is the nicy 8 bytes packet ready to send. (wonder why it's 8? first byte is report ID that I described in HID descriptor to later implement touchpad and/or macro keys).

the packet is sent via USBD_HID_SendReport() which is the part of USB FS. and we're done! 

# Overview:

The following system is a simple education system that takes user input and echo's (prints) it back out to the user. The whole goal for this project is to learn how a bootloader loads the kernel and gets the system up and running. I took this example from the following place: https://github.com/ghaiklor/ghaiklor-os-gcc

I'm using this as my starting ground due to the lack of finding good and simple projects that I can learn on my own. Another huge problem that I seem to run into is finding an example that not only works but is with the times. What I mean by "with the times" is that since this is such low level project, not many people are coding examples or putting massive amount of "How To's" like what you would see in the website programming area. The original person that created this project did an overall good job at making it simple for me to dive into and understand how everything was working to a certain degree. 

This example however was with the times but not operational. There was a compiling issue that I found on my Ubuntu 18.04 virtual machine and had to add an option to the compiling to make it be able to work for me. After diving into the project even more I found more issues with the system that slipped past the original designer. There is a printing of the characters issue, an assembly instruction that did not exist that was being used (had not affect on the entirety of the system), and just some simple comment mistakes.

Once those were fixed and overhualing the comments completely so that if any other pleb like myself came along and wanted to learn easily, they could. I'm making this README be the source goto document for explaining how everything works and all the useful URL's that I found along the way. Like I mentioned previously, I overhauled the comments almost every line of code in this project, it only took me 5 mins (more like two days) but there are some areas that still confuse the hell out of me and I might've just put a generalized idea. Once I actually start tinkering with the system more, I hopefully will replace majority of those comments and update them. 

The reason behind doing all of this is for my Topics in Operating Systems class and for my undying obsseion to build an operating system. I have a lot of goals while working on this project and you can follow my progress in the wiki of the repository. I will hopefully be updating this as I make changes in the future. Lastly this system is intended for working on the x86 and x86_64 Intel CPU and working with NASM. 


# Getting Started:

To get started you should have some background in Assembly, C, GCC, NASM, and lastly Operating Systems. If you don't, well then good luck to you. Just be careful about the older generations that patrol the fourms when you ask your simple questions. Please just do your research, Google has all the answers that you may need and if not then pick up a manual and start searching for your answer. Here are some popular staring places for OS development:

The Holy Grail of information: https://wiki.osdev.org/Main_Page

You might want to start here though: https://wiki.osdev.org/Creating_an_Operating_System

This one source of material should help you on your journeys of understanding OS development. This source might not be the easiest to understand but once you start learning, things will start to click into place with what the writer is trying to get at. Trust me I'm even struggling at times.

Another great resource that I found while digging is from the following: https://github.com/conmarap/osdev-tutorial

I haven't read into it too much but I was able to use some of the components that I was stuck on with this project from that resource. Hopefully more good information is lurking from within.


# Getting Started w/ Assembly:

Like I said previously you gotta know assembly in order to understand this project, so here are some great resources that I found useful for learning assembly. Just remember that there is "general" assembly and then system architecture specific assembly. 

Tutorials for learning about Assembly: https://www.tutorialspoint.com/assembly_programming/index.htm

Intel Assembly x86 Instructions: https://www.felixcloutier.com/x86

What the extern instruction does: http://www.keil.com/support/man/docs/a51/a51_st_extern.htm

What the global instruction does: https://stackoverflow.com/questions/17898989/what-is-global-start-in-assembly-language

What 0x7C00 means: https://www.glamenv-septzen.net/en/view/6

What IN and OUT instructions do: https://stackoverflow.com/questions/3215878/what-are-in-out-instructions-in-x86-used-for


# Getting Started w/ BIOS interrupts:

I found the following source useful for understanding all the interrupts that happen from the BIOS. One great tip is that BIOS interrupts can be used in Real Mode (16-bit) but not in Protected (32-bit) or Long (64-bit) mode. There are special cases that allow you to go back to Real Mode once you have entered either Protected or Long mode but I haven't done to much research in that area yet.

BIOS Interrupts: https://en.wikipedia.org/wiki/BIOS_interrupt_call


# The BootLoader

The bootloader starts in the directory called boot. The boot.asm file that is located within this directory is where our bootloarder lives. The bootloader will also use the other files within side of the boot directory to get the "kernel" up and running correctly. Remember that the BIOS loads the first 512 bytes from the disk into memory (our bootloader) and it is the bootloaders job to read additionaly sectors from the disk into memory, enable either Protected (32-bit) or Long (64-bit) mode, and then load the "kernel". The files again within the boot directory are pretty self explanatory with what they do in the name of the file.

Good Starting spot: https://wiki.osdev.org/Bootloader

Examples of Bootloaders: https://github.com/conmarap/osdev-tutorial

This might be helpful: https://en.wikibooks.org/wiki/X86_Assembly/Bootloaders

Real Mode: https://wiki.osdev.org/Real_Mode

Protected Mode: https://wiki.osdev.org/Protected_Mode

Long Mode: https://wiki.osdev.org/Setting_Up_Long_Mode


# Interrupts:

Interrupts: https://wiki.osdev.org/Interrupts#From_the_keyboard.27s_perspective

Interrupt Descriptor Table: https://wiki.osdev.org/Interrupt_Descriptor_Table

Interrupt Service Routines: https://wiki.osdev.org/Interrupt_Service_Routines

Programmable Interrupt Controller (8259 chip): https://wiki.osdev.org/8259_PIC#Initialisation


# Anything dealing with the screen:

Printing to the screen: https://wiki.osdev.org/Printing_To_Screen

VGA Hardware: https://wiki.osdev.org/VGA_Hardware


# Anything dealing with memory:

Memory Map of x86: https://wiki.osdev.org/Printing_To_Screen

Segmentation: https://wiki.osdev.org/Segmentation


# Programmable Interval Timer: 

Programmable Interval Timer: https://wiki.osdev.org/Programmable_Interval_Timer

Additional Help: https://wiki.osdev.org/Programmable_Interval_Timer

More additional help: https://github.com/AaronV77/osdev-tutorial/blob/master/5-irqs-and-pit.md

More additional help: https://www.quora.com/What-is-the-purpose-of-PIT-Programmable-Interval-Timer-in-a-Micro-controller


# Remapping your IRQ:

There was good information about this here:

Additional Information: https://stackoverflow.com/questions/282983/setting-up-irq-mapping

More additional help: https://github.com/AaronV77/osdev-tutorial/blob/master/5-irqs-and-pit.md

# Building your OS:

Information for creating a linker script: https://wiki.osdev.org/Linker_Scripts


# Wrapping Up:

The original designer left all the links in the places that corrolated to them and I removed them and put them here. It felt cluttered and messy, and also some of the links were just not helpful. This is all the links that I used to help me navigate this project and understand 90% of it. 


Thanks:

Aaron Valoroso
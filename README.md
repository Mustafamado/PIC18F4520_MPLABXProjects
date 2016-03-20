# PIC18F4520-MPLABXProjects
This repository contains several MPLABX Projects and some libraries to understand how to use a specific PIC18F4520 Development Board. This development board is designed by me and it is currently used in EEX 237 - Introduction to Microprocesses course of Fatih University, Istanbul, Turkey. I am the responsible Teaching Assistant of this course.

Aim of sharing these projects is reaching to and developing the projects easier by my students and people who may be interested. 

To be able to run my projects:

1- Latest MPLAB X IDE program needs to be installed. (MPASM compiler is included to this installation.)
  http://www.microchip.com/mplab/mplab-x-ide
  
2- Latest XC8 Compiler needs to installed. (C compiler for 8-bit PIC microcontrollers)
  http://www.microchip.com/mplab/compilers
  
3- Folder hierarchy is important to use my libraries. You shouldn't change the folder hierarchy. For example, Libraries and PIC18F4520-XC8-LED.X folders should have equal hierarchy which means that they should be in the same directory.

4- If you want to use my Libraries in your own projects,

  Firstly, your project folder should be in same directory with Libraries folder.
  
  Secondly, right click to your project name in project window of MPLAB X IDE program. Then select Properties > Categories > Conf:
[default] > XC8 global otions > XC8 compiler > Include directories. Insert "..\Libraries" to Include directories.

  Now, you can include any of my library in your code, by calling it like #include "pic18f4520_config.h".

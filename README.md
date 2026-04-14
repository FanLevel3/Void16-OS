# Void16-OS
🌌 Void16 OS V0.6

A Tiny CLI Operating System Built from Scratch

Void16 OS is a minimalist, hobbyist operating system designed for fun and exploration. It’s built to demonstrate the core fundamentals of OS development, starting from the boot sequence to a basic interactive shell.

Currently, it features a simple functional CLI where you can feed it inputs, and it will spit outputs back at you. Simple, raw, and straight to the point. lol
✨ Features

    Custom C Kernel: The heart of the system is written in C. (16Kernel)

    Assembly Loader: Low-level entry point handled by Assembly for maximum control.

    GRUB Ready: Uses GRUB as the primary bootloader for easy booting.

    Basic CLI: Interactive text-based interface for input and output.

🛠 Tech Stack

    Languages: C, x86 Assembly

    Bootloader: GRUB

    Format: Bootable ISO Image

🕹️ How to Run

You don't need a complex build environment to try this out. Just grab the ISO and go!

    Download the latest Void16.iso from the releases/repo.

    Fire up your favorite Virtual Machine ( QEMU, VirtualBox, or VMware).

    Create a new VM and set the OS type to "Unknown" or "Other".

    Mount the ISO and hit Start.

🚧 Project Status

This is currently a "Just for Fun" project. The main goal is to experiment with kernel-side logic and hardware interfacing. Expect more "useless but cool" features soon!



📚For How to RUN it in QEMU and VirtualBox

📁***QEMU***

Type: *qemu-system-x86_32 -cdrom Void16.iso*

💻***VirtualBox***

**First Open Your Program**

<img width="937" height="768" alt="Git" src="https://github.com/user-attachments/assets/136ecaa5-f556-4b29-8042-798bea43c403" />

**Second Click NEW**

<img width="1072" height="768" alt="Git2" src="https://github.com/user-attachments/assets/a3e7ac86-9af9-41b4-8660-1e91c006f681" />

**Third Setting Like This**
*Example*

ISO Image: /Root/User/Downloads/Void16OS.iso
OS: Other
OS Version: Other/Unknown

<img width="993" height="768" alt="Git3" src="https://github.com/user-attachments/assets/daa320d4-2130-4c04-aa91-33d9169ffcd1" />

**Final Press Start**

Select Void16 OS and **Enjoy!**

<img width="1093" height="758" alt="GIt4" src="https://github.com/user-attachments/assets/286fc9b6-6b71-4cf0-a6df-f587743d4044" />

# Virtual Memory Mechanisms

1. **Virtualization of Memory**: Similar to CPU virtualization, where limited direct execution is used, memory virtualization aims for both efficiency and control. The hardware transforms a program's virtual memory addresses into physical addresses, allowing the operating system (OS) to maintain control and prevent unauthorized memory access by different applications.

2. **Address Translation**: The hardware, with help from the OS, translates virtual addresses into physical addresses every time a memory reference (like an instruction or data access) occurs. This ensures that processes only access memory allocated to them.

3. **Dynamic Relocation**: This method involves two hardware registers, **base** and **bounds** (or limit). These registers allow the process to think it is operating from address 0, while the OS relocates its actual memory to a different part of physical memory. The **base register** holds the starting physical address, and the **bounds register** ensures the process does not access memory beyond its limits.

4. **Hardware and OS Support**: The CPU needs to support address translation with these registers and generate exceptions if a process tries to access memory outside its bounds. The OS sets up these registers for each process and manages memory allocation and deallocation through a **free list**.

5. **Efficiency and Protection**: This technique is efficient because it uses minimal hardware. It also offers protection by ensuring no process can access memory outside its allocated space. However, there is a potential for **internal fragmentation**, where unused space within allocated memory becomes wasted.

# Virtual Memory Paging

We have introduced the concept of paging as a solution to our challenge of virtualizing memory. Paging has many advantages over previous approaches (such as segmentation). First, it does not lead to external fragmentation, as paging (by design) divides memory into fixed-sized units. Second, it is quite flexible, enabling the sparse use of virtual address spaces

However, implementing paging support without care will lead to a slower machine (with many extra memory accesses to access the page table) as well as memory waste (with memory filled with page tables instead of useful application data). We’ll thus have to think a little harder to come up with a paging system that not only works, but works well

- virtual page number: is the part of a memory address that identifies a specific page in virtual memory, allowing for efficient mapping to physical memory locations

### Summary of the Chapter on Paging in Operating Systems

#### Introduction to Paging

- **Paging** is an approach used in operating systems to manage virtual memory by dividing it into fixed-sized units called **pages**. This method contrasts with segmentation, which divides memory into variable-sized segments, potentially leading to fragmentation

#### Basic Concepts

- **Virtual Memory**: The logical address space of a process, which is divided into pages
- **Physical Memory**: The actual RAM, viewed as a collection of fixed-sized slots known as **page frames**
- The core challenge of paging is effectively translating virtual addresses to physical addresses while minimizing space and time overhead

#### Address Space Example

- An example illustrates a simple 64-byte address space divided into four 16-byte pages. The virtual address is split into a **virtual page number (VPN)** and an **offset** within that page
- A **page table** is maintained to map each virtual page to its corresponding physical frame

#### Page Table Structure

- Each process has its own page table, containing entries that store translations from virtual to physical addresses. The table size can become large, especially with 32-bit address spaces
- The **page table entries (PTEs)** contain important bits like:
  - **Valid bit**: Indicates if the translation is valid
  - **Protection bits**: Determine access permissions
  - **Present bit**: Shows if the page is in physical memory or on disk
  - **Dirty bit**: Indicates if the page has been modified

#### Performance Considerations

- Paging introduces additional memory accesses (to fetch the page table entries), which can slow down memory access by a factor of two or more
- Careful design is needed to avoid excessive memory usage and performance degradation due to page table overhead

#### Memory Access Example

- A memory access example shows the flow of translating a virtual address through the page table and obtaining the corresponding physical address. Each access involves fetching the relevant PTE before accessing the desired data

#### Conclusion

- Paging offers advantages such as eliminating external fragmentation and supporting sparse address spaces. However, it requires careful management to prevent performance issues and excessive memory use due to large page tables

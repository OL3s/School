# Address Translation

## Main Points
- Adress Translation Concept
- Flexible addressing
- Segmentation

Processor -> Translation Lookaside Buffer (TLB) -> Page Table -> Physical Memory

## Address Translation Goals
- Memory Protection.
- Memory Sharing: Shared libraries, inter-process communication.
- Sparse addresses: Multiple regions of dynamic allocation (heap, stack, etc.).
- Efficiency: Memory placement, runtime lookup, Compact translation tables.
- Portability: Consistent behavior across different hardware and software environments.

Processor >> Virtual Address >> MMU >> Physical Address >> Memory

{Base, Physical Address, Base + Limit}

## Address translation uses

- Process isolation
- Efficient interprocess communication
- Shared code segments
- Program initialization
- Dynamic memory allocation

### More

- Program debugging
- Zwero-copy I/O
- Memory-mapped files
- Demand paged virtual memory

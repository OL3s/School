## Concurrency.

***Must*** know: fork, exec, wait;

**Paralization**: Also called concurrency. Doing multiple things at the same time.

**Threads**: Lightweight processes that share the same memory space. They can run concurrently, allowing for more efficient use of resources.

### Why concurrency?
- Servers: Handle multiple requests at the same time.
- User interfaces: Keep the UI responsive while performing background tasks.
- Parallel processing: Utilize multiple CPU cores for performance.
- Network and disk I/O: Overlap I/O operations with computation to improve efficiency.

*Example*: Word processor
- Thread for reading user input.
- Thread for spell checking.
- Thread for auto-saving documents.
- Thread for updating the display.
- Thread for handling network communication (e.g., cloud sync).

A thread is a single execution sequence within a process. A process can have multiple threads, all sharing the same memory space. OS can run or suspend threads at any time.

### Parralell vs Serial
- **Serial**: One task at a time.
- **Parallel**: Multiple tasks at the same time.

*Fork* is an example of parallel usage.
## Windows CreateProcess
- **Windows CreateProcess**: A function that creates a new process and its primary thread, allowing the execution of a specified program within the Windows operating system.

## Unix process management

- **UNIX fork**: Creates a new process by duplicating the calling process. The new process is called the child process.
- **UNIX exec**: Replaces the current process image with a new program, allowing execution of a different program within the same process.
- **UNIX wait**: Suspends execution of the calling process until one of its child processes terminates, enabling synchronization.
- **UNIX signal**: Provides a way to send notifications to processes, allowing them to handle asynchronous events such as interrupts or termination requests.

### Questions
- Can UNIX fork() return error? Yes, it can return -1 if the system is unable to create a new process.
- Can UNIX exec() return error? Yes, it can return -1 if the specified program cannot be executed.
- Can UNIX wait() return error? Yes, it can return -1 if there are no child processes to wait for or if an error occurs.
- Can UNIX signal() return error? Yes, it can return -1 if the signal cannot be sent or if an invalid signal number is specified.
- Can wait() execute immediately? Yes, if a child process has already terminated, wait() can return immediately with the child's exit status.

## Implementing unix fork
- Create and init the process control block in kernel.
- Create new address space.
- Init the address space with a copy of the content.
- Inherit exe content of the parent.
- Inform the scheduler that the new process is ready to run.

## I/O (Input/Output)
- Uniformity: All I/O devices are accessed in the same way.
- Open before use: A file descriptor is returned.
- Byte-oriented: Read and write one byte at a time.
- Kernel buffered read and write.
- Explicit close: Free resources.

## UNIX file system interface
- Unix file open a swiss army knife:
    - Open the file, return file descriptor.

## Implementing a shell

``` c
char *prog, **args;
int child_pid;

// Read and parse the input a line at a time
while(readAndParseCmdLine(&prog, &args)) {
    // Create a new process
    child_pid = fork();
    if(child_pid == 0) {
        // This is the child process
        exec(prog, args);
        // If exec returns, there was an error
        perror("exec failed");
        exit(1);
    } else if(child_pid > 0) {
        // This is the parent process
        wait(child_pid); // Wait for the child to finish
    } else {
        // Fork failed
        perror("fork failed");
    }
}
```
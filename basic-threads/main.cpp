#include <iostream>
#include <thread>
#include <sstream>

class MultithreadedConsoleWriter {
public:
    void writeLine(const std::string &text) {
        lock.lock();
        std::cout << text << std::endl;
        lock.unlock();
    }
private:
    std::mutex lock;
};

MultithreadedConsoleWriter threadSafeConsoleWriter;

void threadFunction() {
    std::stringstream textStream;
    textStream << "Thread function launched by thread " << std::this_thread::get_id();
    threadSafeConsoleWriter.writeLine(textStream.str());
}

class ThreadFunctionObject {
public:
    ThreadFunctionObject(MultithreadedConsoleWriter &consoleWriter): console(consoleWriter) {}
    void operator() () {
        std::stringstream textStream;
        textStream << "Thread functor launched by thread " << std::this_thread::get_id();
        console.writeLine(textStream.str());
    }

private:
    MultithreadedConsoleWriter &console;
};

int main() {
    std::thread threads[10];
    
    // Launch a group of threads with thread functions
    for (int i = 0; i <= 5; ++i) {
        threads[i] = std::thread(threadFunction);
    }

    // Launch a group of threads with thread functors
    for (int i = 6; i < 10; ++i) {
        threads[i] = std::thread(ThreadFunctionObject(threadSafeConsoleWriter));
    }
    
    // Waiting for threads to complete
    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }
    
    return 0;
}

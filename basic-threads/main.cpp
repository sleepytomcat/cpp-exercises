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

void threadFunction(int tid) {
    std::stringstream textStream;
    textStream << "Thread function launched by thread " << tid;
    threadSafeConsoleWriter.writeLine(textStream.str());
}

int main() {
    std::thread threads[10];
    
    //Launch a group of threads
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(threadFunction, i);
    }
    
    threadSafeConsoleWriter.writeLine("Writing text from the main()");
    
    // Waiting for threads to complete
    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }
    
    return 0;
}

#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <getopt.h>
#include <string>

static void signal_handler(int signum)
{
    std::cout<<"Received signal: "<<signum<<std::endl;

    exit(signum);
}
void print_help()
{
    std::cout << "\t-d [design pattern]" << std::endl;
    std::cout << "\t-l language feature" << std::endl;
    std::cout << "\t-a [algorithms]" << std::endl;
    std::cout << "\t-o os features" << std::endl;
}

extern void TestDesignMemoryAllocator();

int main(int argc, char **argv)
{
    signal(SIGINT,  signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGINT,  signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGFPE, signal_handler);

    const char* const short_opts = "d:l:a:o:h:";
    const option long_opts[] = {
        {"designPattern", required_argument, nullptr, 'd'},
        {"language", required_argument, nullptr, 'l'},
        {"algorithms", required_argument, nullptr, 'a'},
        {"os", optional_argument, nullptr, 'o'},
        {"help", no_argument, nullptr, 'h'}
    };

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt) {
            print_help();
            break;
        }

        std::string pattern;
        std::string algo;
        switch (opt)
        {
        case 'd':
            pattern = std::string(optarg);
            std::cout<<"run design pattern "<<pattern<<std::endl;
            break;
        case 'l':
            std::cout<<"run language features"<<std::endl;
            break;
        case 'a':
            algo = std::string(optarg);
            std::cout<<"run algorithms"<<std::endl;
            break;
        case 'o':
            std::cout<<"run os"<<std::endl;
            break;
        case 'h':
        default:
            print_help();
            break;
        }
    }
    std::cout << "input: " << std::endl;
    int input;
    std::cin >> input;
    std::cout << input << std::endl;
    std::cout << "Hello World" << std::endl;
    return 0;
}
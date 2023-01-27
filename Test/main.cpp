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

int main(int agrc, char **argv)
{
    signal(SIGINT,  signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGINT,  signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGFPE,  signal_handler);

    const char* const short_opts = "dp:l:a:o:h";
    const options long_opts[] = {
        {"designPattern", required_argument, nullptr, 'dp'},
        {"language", required_argument, nullptr, 'l'},
        {"algorithms", required_argument, nullptr, 'a'},
        {"os", optional_argument, nullptr, 'o'},
        {"help", no_argument, nullptr, 'h'}
    };

    while (true)
    {
        const auto = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        case 'dp':
            std::string pattern = std::string(optarg);
            std::cout<<"run design pattern"<<pattern<<std::endl;
            break;
        case 'l':
            std::cout<<"run language features"<<std::endl;
            break;
        case 'a':
            std::string algo = std::string(optarg);
            std::cout<<"run algorithms"<<std::endl;
            break;
        case 'o':
            std::cout<<"run os"<<std::endl;
            break;
        case 'h':
        default:
            printHelp();
            break;
        }
    }

    // std::raise(SIGINT);
    //while (1)
    //{
    //    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //}
    std::cout << "Hello World" << std::endl;
    return 0;
}
// Tick2Candle.cpp
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost::filesystem;
namespace po = boost::program_options;

// Config
struct Config
{
    path tickDirectory; 
    path outputDirectory; 

    unsigned int askColIndex; 
    unsigned int bidColIndex; 
    unsigned int dateTimeColIndex; 

    bool useAsk; 
    bool useBid;
    bool useMid; 
};

//----------------------------------------------------------------
// Name: main
// Desc: 
//----------------------------------------------------------------
int main(int argc, char** argv)
{
    // arguments
    // --t "path to tick file directory"
    // --o "path to candle output directory"
    // --ask col number
    // --bid col number
    // --time col number
    // --ua use ask
    // --ub use bid
    // --um  use mid

    po::options_description desc("Options"); 
    Config config; 

    desc.add_options()
        ("help", "Produce help message")
        ("t", po::value<std::string>(), "Path to tick directory")
        ("o", po::value<std::string>(), "Path to output directory")
        ("ask", po::value<int>(), "Index to Ask column")
        ("bid", po::value<int>(), "Index to Bid column")
        ("time", po::value<int>(), "Index to Time column")
        ("ua", "Use Ask prices to calculate candles")
        ("ub", "Use Bid prices to calculate candles")
        ("um", "Use Mid price to calculate candles")
    ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl; 

    } else {

        if (vm.count("t")) {
            config.tickDirectory = vm["t"].as<std::string>(); 
        }

        if (vm.count("o")) {
            config.outputDirectory = vm["o"].as<std::string>();
        }

        if (vm.count("ask")) {
            config.askColIndex = vm["ask"].as<int>(); 
        }

        if (vm.count("bid")) {
            config.bidColIndex = vm["bid"].as<int>(); 
        }

        if (vm.count("time")) {
            config.dateTimeColIndex = vm["time"].as<int>(); 
        }

        if (vm.count("ua")) {
            config.useAsk = true; 
        }

        if (vm.count("ub")) {
            config.useBid = true; 
        }

        if (vm.count("um")) {
            config.useMid = true; 
        }
    }

    std::cout << config.tickDirectory << std::endl; 
    std::cout << config.outputDirectory << std::endl;
    std::cout << config.askColIndex << std::endl;
    std::cout << config.bidColIndex << std::endl;
    std::cout << config.dateTimeColIndex << std::endl;
    std::cout << config.useAsk << std::endl;
    std::cout << config.useBid << std::endl;
    std::cout << config.useMid << std::endl;


    // get file paths

    // path p (argv[1]);

    // if (exists(p) && is_directory(p)) {

    //     for(directory_entry& d : recursive_directory_iterator(p)) {

    //         if (!is_directory(d.path())) {
    //             std::cout << d.path() << std::endl; 
    //         }
    //     }
    // }

    // print out the files found under directory

    return 0; 
}
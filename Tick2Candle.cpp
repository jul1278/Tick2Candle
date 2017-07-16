// Tick2Candle.cpp
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/interprocess/file_mapping.hpp>

// Config
struct Config {
    boost::filesystem::path tickDirectory; 
    boost::filesystem::path outputDirectory; 

    unsigned int askColIndex; 
    unsigned int bidColIndex; 
    unsigned int dateTimeColIndex; 

    unsigned int periodSec;
    unsigned int periodHours; 

    bool useAsk; 
    bool useBid;
    bool useMid; 
};

// ValidatedState
struct ValidatedState {
    bool isValid; 

    std::list<boost::filesystem::path> inputFiles; 
    Config config; 

    ValidatedState() {}
    ValidatedState(bool valid) : isValid(valid) {}
};

//----------------------------------------------------------------
// Name: FilesInDirectory
// Desc: 
//----------------------------------------------------------------
std::list<boost::filesystem::path> FilesInDirectory(const boost::filesystem::path& path) {
    std::list<boost::filesystem::path> files; 

    if (boost::filesystem::exists(path)) {
        if (boost::filesystem::is_directory(path)) {    
            for(auto& entry : boost::filesystem::recursive_directory_iterator(path)) {   
                if (boost::filesystem::is_regular_file(entry.path())) { files.push_back(entry.path()); }
            }
        }
    }

    return files; 
}
//----------------------------------------------------------------
// Name: main
// Desc: 
//----------------------------------------------------------------
ValidatedState ValidateConfig(const Config& config) {

    ValidatedState validatedState;
    validatedState.config = config; 

    // get file paths
    // check file paths exist
    if (boost::filesystem::exists(config.tickDirectory)) {
        if (boost::filesystem::is_directory(config.tickDirectory)) {
            // enumerate the files in directory
            validatedState.inputFiles = FilesInDirectory(config.tickDirectory);
        } else if (boost::filesystem::is_regular_file(config.tickDirectory)) {
            validatedState.inputFiles.push_back(config.tickDirectory); 
        }
    } else {
        std::cout << config.tickDirectory << " does not exist. Quitting." << std::endl; 
        
        validatedState.isValid = false; 
        return validatedState; 
    }

    validatedState.isValid = true; 
    return validatedState; 
}
//----------------------------------------------------------------
// Name: main
// Desc: 
//----------------------------------------------------------------
int main(int argc, char** argv) {
    // arguments
    // --t "path to tick file directory"
    // --o "path to candle output directory"
    // --ask col number
    // --bid col number
    // --time col number
    // --ua use ask
    // --ub use bid
    // --um  use mid
    // --ph period hours
    // --ps period second

    boost::program_options::options_description desc("Options"); 
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
        ("ps", "OHLC Period in hours")
        ("ph", "OHLC Period in seconds")
    ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    //po::store(po::command_line_parser(2, myArgv).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl; 
    } else {
        if (vm.count("t")) { config.tickDirectory = vm["t"].as<std::string>(); }
        if (vm.count("o")) { config.outputDirectory = vm["o"].as<std::string>(); }
        if (vm.count("ask")) { config.askColIndex = vm["ask"].as<int>(); }
        if (vm.count("bid")) { config.bidColIndex = vm["bid"].as<int>(); }
        if (vm.count("time")) { config.dateTimeColIndex = vm["time"].as<int>(); }
        if (vm.count("ua")) { config.useAsk = true; }
        if (vm.count("ub")) { config.useBid = true; }
        if (vm.count("um")) { config.useMid = true; }
        if (vm.count("ps")) { config.periodSec = vm["ps"].as<unsigned int>(); }
        if (vm.count("ph")) { config.periodHours = vm["ph"].as<unsigned int>(); }
    }

    // std::cout << config.tickDirectory << std::endl; 
    // std::cout << config.outputDirectory << std::endl;
    // std::cout << config.askColIndex << std::endl;
    // std::cout << config.bidColIndex << std::endl;
    // std::cout << config.dateTimeColIndex << std::endl;
    // std::cout << config.useAsk << std::endl;
    // std::cout << config.useBid << std::endl;
    // std::cout << config.useMid << std::endl;

    auto validatedState = ValidateConfig(config);

    for (auto& file : validatedState.inputFiles) {
        std::cout << file << std::endl; 
    }

    return 0; 
}

//-----------------------------------------------------------------------
// Name: Ticks2Candle
// Desc:
//-----------------------------------------------------------------------
bool Ticks2Candle(boost::filesystem::directory_entry& file, const Config& config) {
    // TODO
    return true; 
}
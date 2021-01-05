// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "crawler.hpp"

Crawler::Crawler(const int& argc, char **argv) {
  ac = argc;
  av = argv;
}

int Crawler::initChain() {
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Produce help message")
        ("url,u", po::value<std::string>(&param.host), "Parsed URL-address")
        ("depth,d", po::value<int>(&param.depth)->implicit_value(1),
         "Level of searching images")
        ("network_threads,n", po::value<int>(&param.networkThreads)
             ->default_value(boost::thread::hardware_concurrency()),
         "Number of ports to producer")
        ("parser_threads,p", po::value<int>(&param.parserThreads)
             ->default_value(boost::thread::hardware_concurrency()),
         "Number of ports to consumer")
        ("output,o", po::value<std::string>(&param.output)
             ->default_value("./result.log"),
         "Output file")
        ;
    po::positional_options_description p;
    p.add("input-file", -1);
    po::variables_map vm;
    po::store(po::command_line_parser(ac, av).
        options(desc).positional(p).run(), vm);
    po::notify(vm);
    std::cout << param.host << " " <<
        param.depth << " " <<
        param.networkThreads << " " <<
        param.parserThreads << " ";
    if (vm.count("help")) {
      std::cout << "Usage: options_description [options]\n";
      std::cout << desc;
      return 0;
    }
    Downloader test(param.host, param.networkThreads);
    test.downloadPage();
  }
  catch(std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
  return 0;
}

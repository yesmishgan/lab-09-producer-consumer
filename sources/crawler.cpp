// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "crawler.hpp"

Crawler::Crawler(const int& argc, char **argv) {
  ac = argc;
  av = argv;
}

int Crawler::initChain() {
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help,h", "Produce help message")
          ("url,u", po::value<std::string>(&param.host), "Parsed URL-address")
              ("depth,d", po::value<int>(&param.depth)->default_value(1),
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
  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);
  if (vm.count("help")) {
    std::cout << "Usage: crawler [options]\n";
    std::cout << desc;
    return 1;
  }
  if (!vm.count("url"))
    return 1;
  Downloader a(param.host, param.port, param.depth, param.networkThreads);
  a.downloadPage();
  return 0;
}

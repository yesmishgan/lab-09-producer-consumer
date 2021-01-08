// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include <crawler.hpp>

int main(int argc, char **argv){
  Crawler crawl(argc, argv);
  if (crawl.initChain())
    return EXIT_FAILURE;
  return 0;
}
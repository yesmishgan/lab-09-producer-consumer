// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "downloader.hpp"

Downloader::Downloader(const std::string& host,
                       const int& port,
                       const int& depth,
                       const int& thread):host(host),
                                            port(port),
                                            depth(depth),
                                            thread(thread){}

void Downloader::downloadPage(){

}

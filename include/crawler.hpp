// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#ifndef TEMPLATE_CRAWLER_HPP
#define TEMPLATE_CRAWLER_HPP

#include <ThreadPool.h>
#include <iostream>
#include <gumbo.h>
#include "boost/program_options.hpp"
#include <boost/thread.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <downloader.hpp>
#include <parser.hpp>

namespace po = boost::program_options;
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

struct params{
  std::string host;
  const int port = 80;
  int depth;
  int networkThreads;
  int parserThreads;
  std::string output;
};

class Crawler{
 public:
  Crawler(const int& argc, char **argv);
  int initChain();
 private:
  int ac;
  char **av;
  params param;
};

#endif  // TEMPLATE_CRAWLER_HPP

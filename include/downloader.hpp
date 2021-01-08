// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#ifndef TEMPLATE_DOWNLOADER_HPP
#define TEMPLATE_DOWNLOADER_HPP

#include <crawler.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/ssl.hpp>
#include "root_certificates.hpp"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp

class Downloader {
 public:
  Downloader();
  Downloader(const std::string& host,
             const int& port,
             const int& depth,
             const int& thread);
  void downloadPage();
 private:
  std::string host;
  int port;
  int depth;
  int thread;
};

#endif  // TEMPLATE_DOWNLOADER_HPP

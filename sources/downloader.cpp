// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "downloader.hpp"
#include <gumbo.h>

Downloader::Downloader(const std::string& url,
                       const int& port,
                       const int& depth,
                       const int& thread):url(url),
                                            port(port),
                                            depth(depth),
                                            thread(thread){}

std::string Downloader::urlToHost() {
  std::string host = url;
  if (host.find("https://") == 0)
    host = host.substr(8);
  size_t i = 0;
  for (; i < host.size(); ++i) {
    if ((host[i] == '/') || (host[i] == '?')) break;
  }
  host = host.substr(0, i);
  return host;
}

std::string Downloader::urlToTarget(){
  std::string target = url;
  if (target.find("https://") == 0){
    target = target.substr(8);
  }
  int pos = target.find('/');
  if (pos == -1)
    return "/";
  target = target.substr(pos);
  return target;
}

void Downloader::processing(){
//  GumboOutput* out = gumbo_parse(downloadPage(urlToHost(),
  //                                            urlToTarget()).c_str());

}

std::string Downloader::downloadPage(std::string host, std::string target){
  try {
    int version = 11;
    std::cout << "HOST: " << host << " TARGET: " << target << std::endl;
    boost::asio::io_context ioc;

    ssl::context ctx{ssl::context::sslv23_client};

    load_root_certificates(ctx);

    tcp::resolver resolver{ioc};
    ssl::stream<tcp::socket> stream{ioc, ctx};

    if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
      boost::system::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
      throw boost::system::system_error{ec};
    }

    auto const results = resolver.resolve(host.c_str(),
                                          std::to_string(port));

    boost::asio::connect(stream.next_layer(), results.begin(), results.end());

    stream.handshake(ssl::stream_base::client);

    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);

    boost::beast::flat_buffer buffer;

    http::response<http::string_body> res;

    http::read(stream, buffer, res);

    boost::system::error_code ec;

    if (ec == boost::asio::error::eof) {
      ec.assign(0, ec.category());
    }
    if (ec)
      throw boost::system::system_error{ec};

    std::cout << res.body() << std::endl;

    return res.body();

  }catch (std::exception const& e){
    std::cerr << e.what() << std::endl;
  }
  return "";
}

// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "downloader.hpp"

Downloader::Downloader(const std::string& hostSite, const int& th){
  host = hostSite;
  threads = th;
}

void Downloader::downloadPage(){
  // The io_context is required for all I/O
  net::io_context ioc;

  // The SSL context is required, and holds certificates
  ssl::context ctx(ssl::context::tlsv12_client);

  // This holds the root certificate used for verification
  load_root_certificates(ctx);

  // Verify the remote server's certificate
  ctx.set_verify_mode(ssl::verify_peer);

  // These objects perform our I/O
  tcp::resolver resolver(ioc);
  beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

  // Set SNI Hostname (many hosts need this to handshake successfully)
  if(! SSL_set_tlsext_host_name(stream.native_handle(), host))
  {
    beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
    throw beast::system_error{ec};
  }

  // Look up the domain name
  auto const results = resolver.resolve(host, port);

  // Make the connection on the IP address we get from a lookup
  beast::get_lowest_layer(stream).connect(results);

  // Perform the SSL handshake
  stream.handshake(ssl::stream_base::client);

  // Set up an HTTP GET request message
  http::request<http::string_body> req{http::verb::get, target, version};
  req.set(http::field::host, host);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  // Send the HTTP request to the remote host
  http::write(stream, req);

  // This buffer is used for reading and must be persisted
  beast::flat_buffer buffer;

  // Declare a container to hold the response
  http::response<http::dynamic_body> res;

  // Receive the HTTP response
  http::read(stream, buffer, res);

  // Write the message to standard out
  std::cout << res << std::endl;

  // Gracefully close the stream
  beast::error_code ec;
  stream.shutdown(ec);
  if(ec == net::error::eof)
  {
    // Rationale:
    // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
    ec = {};
  }
  if(ec)
    throw beast::system_error{ec};
}
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/core.hpp>

namespace bease = boost::beast;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class SmtpClient {
   public:
    SmtpClient(const std::string& smtp_server, int port)
        : smtp_server_(smtp_server), port_(port) {}

   private:
    const std::string& smtp_server_;
    int port_;
    asio::io_context ioc_;
    tcp::socket socket_;
    tcp::resolver resolver_;
};
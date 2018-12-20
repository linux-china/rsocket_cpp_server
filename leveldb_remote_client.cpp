#include <iostream>

#include <folly/init/Init.h>
#include <folly/io/async/ScopedEventBaseThread.h>
#include <folly/portability/GFlags.h>

#include <rsocket/RSocket.h>
#include <rsocket/examples/util/ExampleSubscriber.h>
#include <rsocket/transports/tcp/TcpConnectionFactory.h>

#include <yarpl/Single.h>

using namespace rsocket_example;
using namespace rsocket;
using namespace yarpl;
using namespace yarpl::single;

DEFINE_string(host, "localhost", "host to connect to");
DEFINE_int32(port, 42252, "host:port to connect to");

int main(int argc, char *argv[]) {
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;
    folly::init(&argc, &argv);

    folly::SocketAddress address;
    address.setFromHostPort(FLAGS_host, FLAGS_port);

    folly::ScopedEventBaseThread worker;
    auto client = RSocket::createConnectedClient(
            std::make_unique<TcpConnectionFactory>(
                    *worker.getEventBase(), std::move(address)))
            .get();

    client->getRequester()
            ->requestResponse(Payload("nick","get"))
            ->subscribe([](Payload p) {
                std::cout << "Received >> " << p.moveDataToString() << std::endl;
            });

    // Wait for a newline on the console to terminate the client.
    std::getchar();
    return 0;
}

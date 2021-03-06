#include <iostream>
#include <sstream>
#include <thread>

#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>

#include <rsocket/RSocket.h>
#include <rsocket/transports/tcp/TcpConnectionAcceptor.h>
#include <yarpl/Flowable.h>
#include <leveldb/db.h>

using namespace rsocket;
using namespace yarpl::flowable;
using namespace yarpl::single;
using std::string;

DEFINE_int32(port, 42252, "port to connect to");

/**
 * leveldb responder
 */
class LeveldbResponder : public rsocket::RSocketResponder {
public:

    LeveldbResponder() {
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, "/Users/linux_china/data/leveldb", &db);
    }

    ~ LeveldbResponder() {
        delete db;
    }

    std::shared_ptr<Single<Payload>> handleRequestResponse(
            Payload request, StreamId) override {
        auto metadata = request.moveMetadataToString();
        std::size_t posOfSeparator = metadata.find(" "); // position of " " separator
        string command = metadata.substr(0, posOfSeparator);
        string key = metadata.substr(posOfSeparator + 1);
        if (command == "get") {
            return Single<Payload>::create(
                    [name = std::move(key), database = db](auto subscriber) {
                        string value;
                        leveldb::Status s = database->Get(leveldb::ReadOptions(), name, &value);
                        subscriber->onSubscribe(SingleSubscriptions::empty());
                        subscriber->onSuccess(Payload(s.ok() ? value : "", s.ToString()));
                    });
        } else if (command == "put") {
            auto value = request.moveDataToString();
            return Single<Payload>::create(
                    [key = std::move(key), value = std::move(value), database = db](auto subscriber) {
                        leveldb::Status s = database->Put(leveldb::WriteOptions(), key, value);
                        subscriber->onSubscribe(SingleSubscriptions::empty());
                        subscriber->onSuccess(Payload("", s.ToString()));
                    });
        } else if (command == "delete") {
            return Single<Payload>::create(
                    [name = std::move(key), database = db](auto subscriber) {
                        leveldb::Status s = database->Delete(leveldb::WriteOptions(), name);
                        subscriber->onSubscribe(SingleSubscriptions::empty());
                        subscriber->onSuccess(Payload("", s.ToString()));
                    });
        } else {
            return Single<Payload>::create(
                    [](auto subscriber) {
                        subscriber->onSubscribe(SingleSubscriptions::empty());
                        subscriber->onSuccess(Payload("Unknow levelDB method!", "Error"));
                    });
        }
    }

    //todo Iteration level db according to key pattern.
    std::shared_ptr<Flowable<rsocket::Payload>> handleRequestStream(
            rsocket::Payload request,
            rsocket::StreamId) override {
        // string from payload data
        auto key = request.moveDataToString();
        return Flowable<>::range(1, 100)->map(
                [name = std::move(key)](int64_t v) {
                    std::stringstream ss;
                    ss << "Hello " << name << " " << v << "!";
                    string s = ss.str();
                    return Payload(s, "Ok");
                });
    }

    void handleFireAndForget(rsocket::Payload request, rsocket::StreamId streamId) override {
        auto command = request.moveMetadataToString();
        auto token = request.moveDataToString();
        //todo shutdown server, command is halt, and key is token
        if (command == "halt") {
            // shutdown logic
        }
    }

private:
    leveldb::DB *db;
};

int main(int argc, char *argv[]) {
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;
    folly::init(&argc, &argv);

    TcpConnectionAcceptor::Options opts;
    opts.address = folly::SocketAddress("::", FLAGS_port);
    opts.threads = 2;

    // RSocket server accepting on TCP
    auto rs = RSocket::createServer(
            std::make_unique<TcpConnectionAcceptor>(std::move(opts)));

    auto rawRs = rs.get();
    auto serverThread = std::thread([=] {
        // start accepting connections
        rawRs->startAndPark([](const rsocket::SetupParameters &) {
            return std::make_shared<LeveldbResponder>();
        });
    });

    // Wait for a newline on the console to terminate the server.
    std::getchar();

    rs->unpark();
    serverThread.join();

    return 0;
}

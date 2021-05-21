#include <pistache/endpoint.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class CRUDHandler : public Pistache::Http::Handler
{
public:
    HTTP_PROTOTYPE(CRUDHandler)
    
    void onRequest(const Pistache::Http::Request& req,
        Pistache::Http::ResponseWriter response) override {
        if (req.resource() == "/kv"){
            // Create (parent resource)
            // POST api.exmaple.com/kv/
            if (req.method() == Pistache::Http::Method::Post){
                response.send(Pistache::Http::Code::Ok, "ack-post");
            }
            // Read
            // GET api.exmaple.com/kv/{KEY}
            if (req.method() == Pistache::Http::Method::Get){
                response.send(Pistache::Http::Code::Ok, "value-get");
                response.send(Pistache::Http::Code::Not_Found, "invalid-get");
            }
            // Create / Update
            // PUT api.exmaple.com/kv/{KEY}
            if (req.method() == Pistache::Http::Method::Put){
                response.send(Pistache::Http::Code::Created, "ack-put");
                response.send(Pistache::Http::Code::Accepted, "ack-put");
            }
            // Delete
            // DELETE api.exmaple.com/kv/{KEY}
            if (req.method() == Pistache::Http::Method::Delete){
                response.send(Pistache::Http::Code::Ok, "ack-delete");
            }
        }
        else {
            response.send(Pistache::Http::Code::Not_Found, "not-found");
        }
    }
};

int main()
{
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options().threads(1);

    Pistache::Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Pistache::Http::make_handler<CRUDHandler>());
    server.serve();
}

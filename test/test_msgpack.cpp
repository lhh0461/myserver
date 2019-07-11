#include <iostream>
#include <string.h>
#include <msgpack.hpp>

using namespace std;

int main(void) {
    msgpack::sbuffer sbuf;
    
    msgpack::packer<msgpack::sbuffer> pk(&sbuf);
    pk.pack(string("hello world"));
    pk.pack(10);
    pk.pack(2);
    pk.pack(1.3);

    msgpack::unpacker unpacker;
    unpacker.reserve_buffer(4);

    memcpy(unpacker.buffer(), sbuf.data(), sbuf.size());
    unpacker.buffer_consumed(sbuf.size());

    msgpack::object_handle result;
    unpacker.next(result);
    msgpack::object obj = result.get();
    cout << obj << endl;
    cout << string(obj.via.str.ptr, obj.via.str.size)  << endl;

    unpacker.next(result);
    obj = result.get();
    cout << obj.via.u64  << endl;

    unpacker.next(result);
    obj = result.get();
    cout << obj.via.u64  << endl;

    unpacker.next(result);
    obj = result.get();
    cout << obj.via.f64 << endl;
    
    
    //msgpack::object_handle oh = msgpack::unpack(sbuf.data(), sbuf.size());

    //// deserialized object is valid during the msgpack::object_handle instance alive.
    //msgpack::object deserialized = oh.get();

    //// msgpack::object supports ostream.
    //std::cout << deserialized << std::endl;

    //msgpack::object obj = unpack.get();

    //cout << obj << endl;
//
//    int v1; 
//    oh.get().convert(v1);
//    .next(oh);
//
//    int v2; 
//    oh.get().convert(v2);
//
//    int v3; 
//    oh.get().convert(v3);
//
//    cout << v1  << v2 << v3 << endl;
//
    return 0;
}

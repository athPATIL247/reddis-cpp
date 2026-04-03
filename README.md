# Redis C++ 
This is a basic Redis-like server implemented in C++. It supports a subset of Redis functionality and supports in-memory data store

## Features

* TCP server using sockets (port 6379)
* Supports multiple client connections (handled sequentially)
* Basic commands:

  * `SET key value`
  * `GET key`
* RESP protocol parsing (compatible with `redis-cli`)
* In-memory key-value storage using hash map
* TTL support using `EX` (lazy expiration)

## Project Structure

```
redis-cpp/
├── src/
│   ├── main.cpp
│   ├── server.cpp / server.h
│   ├── datastore.cpp / datastore.h
│   ├── parser.cpp / parser.h
├── build/
├── Makefile
└── README.md
```

## Build and Run

```
make
make run
```

## Usage

Start the server and connect using:

```
redis-cli -p 6379
```

Example commands:

```
SET name xyz
GET name
SET temp value EX 5
```

## Notes

* Data is stored in memory only (no persistence)
* Expiry is implemented using lazy deletion
* Only string values are supported
* Server handles one client at a time

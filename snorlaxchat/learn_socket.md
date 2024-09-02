
## C++ `Socket` 讲解

### 摘要

本文探讨了 C++ 中的 `Socket` 编程，它是网络编程的基础，用于实现服务器与客户端之间的通信。`Socket` 封装了底层复杂的网络协议，使得程序能够简化地在网络中发送和接收数据。

### 类型

`Socket` 有两种常见类型：

- **流式 Socket (Stream Socket)**：使用 TCP 协议，提供面向连接的、可靠的、基于字节流的通信。
- **数据报 Socket (Datagram Socket)**：使用 UDP 协议，提供无连接的、不可靠的、基于数据报的通信。

### 基本流程

#### 1. 调用 `socket()` 创建 `Socket`

```cpp
int socket(int domain, int type, int protocol);
```

- `domain`: 协议族，例如 `AF_INET` (IPv4) 或 `AF_INET6` (IPv6)。
- `type`: `Socket` 类型，例如 `SOCK_STREAM` (TCP) 或 `SOCK_DGRAM` (UDP)。
- `protocol`: 通常设为 `0`，让系统自动选择适合的协议。

#### 2. 调用 `bind()` 将 `Socket` 绑定到特定的 IP 地址和端口号

```cpp
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

- `sockfd`: `Socket` 文件描述符。
- `addr`: 要绑定的地址和端口，通常使用 `sockaddr_in` 结构体设置。
- `addrlen`: 地址结构体的大小。

#### 3. 调用 `listen()` 使 `Socket` 进入监听状态，准备接受连接请求（服务器端）

```cpp
int listen(int sockfd, int backlog);
```

- `backlog`: 队列中允许等待的最大连接数。

#### 4. 使用 `accept()` 接受客户端的连接请求，并返回一个新的 `Socket` 文件描述符（服务器端）

```cpp
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

- `sockfd`: 服务器 `Socket` 文件描述符。
- `addr`: 存储客户端地址信息。
- `addrlen`: 地址结构体的大小。

#### 5. 使用 `connect()` 发起与服务器的连接请求（客户端）

```cpp
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

- `sockfd`: 客户端 `Socket` 文件描述符。
- `addr`: 服务器的地址信息。
- `addrlen`: 地址结构体的大小。

#### 6. 使用 `send()` 或 `recv()` 完成数据传输

```cpp
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

- `send()`: 向 `Socket` 发送数据。
- `recv()`: 从 `Socket` 接收数据。

#### 7. 使用 `close()` 关闭 `Socket` 以释放系统资源

```cpp
int close(int sockfd);
```

- `sockfd`: 需要关闭的 `Socket` 文件描述符。


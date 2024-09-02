## C++ `Socket`讲解
### 摘要

本文探讨了 C++ 中的 `Socket` 编程，它是网络编程的基础，用于实现服务器与客户端之间的通信。Socket 封装了底层复杂的网络协议，使得程序能够简化地在网络中发送和接收数据。
### 类型

Socket有两种常见类型：

-   流式Socket（Stream Socket）：使用TCP协议，提供面向连接的、可靠的、基于字节流的通信。
-  数据报Socket（Datagram Socket）：使用UDP协议，提供无连接的、不可靠的、基于数据报的通信。
### 基本流程
#### 调用`socket()`创建`Socket`
```
        int socket(int domain, int type, int protocol)
```
- `domain`:协议族，例如`AF_INET`(IPv4)或`AF_INET6`
- `type`:`Socket`类型，例如`SOCK_STREAM`(TCP)或`SOCK_DGRAM`
- `protocol`:通常设为`0`，让系统自动选择适合的协议
#### 调用`bind()`将`Socket`绑定到特定的IP地址和端口号
```
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
```
- `sockfd`:`Socket`文件描述符
- `addr`:要绑定的地址和端口，通常使用`sockaddr_in`结构体设置
- `addrlen`:地址结构体的大小

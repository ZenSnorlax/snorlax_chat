#include <iostream>
#include <string>
#include <vector>

// 基类，定义聊天房间的接口
class IChatRoom {
   public:
    virtual ~IChatRoom() = default;
    virtual void join(const std::string& user) = 0;  // 用户加入房间
    virtual void sendMessage(const std::string& message) = 0;  // 发送消息
};

// 双人聊天房间类
class DualChatRoom : public IChatRoom {
   private:
    std::string user1;
    std::string user2;

   public:
    DualChatRoom(const std::string& u1, const std::string& u2)
        : user1(u1), user2(u2) {}

    void join(const std::string& user) override {
        // 可添加逻辑以检查是否可以加入
    }

    void sendMessage(const std::string& message) override {
        // 发送消息给另一个用户
        // 这里可以实现消息发送逻辑
        std::cout << user1 << " and " << user2
                  << " received message: " << message << std::endl;
    }
};

// 多人聊天房间类
class MultiChatRoom : public IChatRoom {
   private:
    std::vector<std::string> users;

   public:
    void join(const std::string& user) override {
        users.push_back(user);
        std::cout << user << " joined the group chat." << std::endl;
    }

    void sendMessage(const std::string& message) override {
        // 发送消息给所有用户
        for (const auto& user : users) {
            std::cout << user << " received message: " << message << std::endl;
        }
    }
};

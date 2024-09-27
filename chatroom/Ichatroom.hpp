#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// 基类，定义聊天房间的接口
class IChatRoom {
   public:
    virtual ~IChatRoom() = default;
    virtual void join(const std::string& user) = 0;  // 用户加入房间
    virtual void sendMessage(const std::string& message,
                             const std::string& sender) = 0;  // 发送消息
   protected:
    std::vector<std::string> messages;  // 存储消息记录
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
        // 可添加逻辑以检查是否可以加入（例如：如果已经有两个用户，则拒绝）
    }

    void sendMessage(const std::string& message,
                     const std::string& sender) override {
        // 发送消息给另一个用户
        std::cout << sender << " to " << (sender == user1 ? user2 : user1)
                  << ": " << message << std::endl;
        messages.push_back(message);  // 记录消息
    }
};

// 多人聊天房间类
class MultiChatRoom : public IChatRoom {
   private:
    std::unordered_set<std::string> users;  // 使用集合避免重复用户

   public:
    void join(const std::string& user) override {
        users.insert(user);  // 添加用户
        std::cout << user << " joined the group chat." << std::endl;
    }

    void sendMessage(const std::string& message,
                     const std::string& sender) override {
        // 发送消息给所有用户
        for (const auto& user : users) {
            std::cout << sender << " to " << user << ": " << message
                      << std::endl;
        }
        messages.push_back(message);  // 记录消息
    }
};

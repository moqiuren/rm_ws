#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
using namespace std::chrono_literals;

class SimplePublisher : public rclcpp::Node
{
    public:
    SimplePublisher() : Node("simple_publisher")
    {
        // 创建发布者，发布到"/greeting"话题，消息类型为String，队列大小为10
        publisher_ = this->create_publisher<std_msgs::msg::String>("/greet", 10);
        
        // 创建定时器，每秒发布一次消息
        timer_ = this->create_wall_timer(
            1000ms,  // 1秒
            std::bind(&SimplePublisher::timer_callback, this));
        
        RCLCPP_INFO(this->get_logger(), "简单发布者节点已启动！");
    }
    private:
    void timer_callback()
    {
        // 创建消息
        auto message = std_msgs::msg::String();
        message.data = "你好，ROS2！时间: " + std::to_string(this->get_clock()->now().seconds());
        // 发布消息
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "发布消息: '%s'", message.data.c_str());
    }
    
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};
int main(int argc, char * argv[])
{
    // 初始化ROS2
    rclcpp::init(argc, argv);
    
// 创建节点并保持运行
auto node = std::make_shared<SimplePublisher>();
rclcpp::spin(node);
// 关闭ROS2
rclcpp::shutdown();
return 0;
}
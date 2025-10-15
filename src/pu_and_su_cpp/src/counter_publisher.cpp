#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <chrono>
using namespace std::chrono_literals;

class CounterPublisher : public rclcpp::Node
{
    public:
    CounterPublisher(std::string name) : Node(name), count_(0)
    {
        // 创建发布者
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("/number", 10);
        
        // 创建定时器，每1秒发布一次
        timer_ = this->create_wall_timer(
            1000ms,  
            std::bind(&CounterPublisher::timer_callback, this));
        
        RCLCPP_INFO(this->get_logger(), "计数器发布者已启动！");
    }
private:
    void timer_callback()
    {
        // 创建消息
        auto message = std_msgs::msg::Int32();
        message.data = count_++;
        
        // 发布消息
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "发布数字: %d", message.data);
    }
    
    int count_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CounterPublisher>("counter_publisher");
rclcpp::spin(node);
rclcpp::shutdown();
return 0;
 }
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <random>

class SimplePublisher:public rclcpp::Node
{
    public:
    SimplePublisher(std::string name):Node(name)
    {   
        init_random_generator();
        RCLCPP_INFO(this->get_logger(),"publisher has started.");

        command_publisher = this->create_publisher<std_msgs::msg::Int32>("/number",10);
        timer = this->create_wall_timer(std::chrono::milliseconds(1000),std::bind(&SimplePublisher::timer_callback,this));
    }

    private:

    std::mt19937 gen_;//random seed
    std::uniform_int_distribution<int> dist_;//Uniform distribution of integers

    void init_random_generator()
    {   
        std::random_device rd;
        gen_.seed(rd());
        dist_ = std::uniform_int_distribution<int>(0,100);

    }

    void timer_callback()
    {   
        std_msgs::msg::Int32 message;
        message.data = dist_(gen_);/*shili .*/
        RCLCPP_INFO(this->get_logger(),"send a number: %d",message.data);
        command_publisher->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr command_publisher;
    rclcpp::TimerBase::SharedPtr timer;
};


int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<SimplePublisher>("simple_publisher");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
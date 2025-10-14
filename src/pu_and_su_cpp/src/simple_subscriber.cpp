#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class SimpleSubscriber:public rclcpp::Node
{
    public:
    SimpleSubscriber(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"subscriber has started.");
        command_subscriber = this->create_subscription<std_msgs::msg::Int32>("publisher",10,std::bind(&SimpleSubscriber::subscriber_callback,this,std::placeholders::_1));
    }

    private:

    int sum = 0;
    double ave,number=0;

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr command_subscriber;

    void subscriber_callback(const std_msgs::msg::Int32::SharedPtr msg)
    {   
        sum += msg->data;/*zhizhen ->*/
        number +=1.0f;
        ave = sum/number;
        RCLCPP_INFO(this->get_logger(),"average:%f",ave);
    }
};


int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<SimpleSubscriber>("simple_subscriber");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
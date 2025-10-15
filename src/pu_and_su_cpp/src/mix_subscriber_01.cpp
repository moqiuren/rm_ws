#include"rclcpp/rclcpp.hpp"
#include"std_msgs/msg/string.hpp"
#include"std_msgs/msg/int32.hpp"

class TopicSubscribe01:public rclcpp::Node
{
    public:
    TopicSubscribe01(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"Hello everyone,I am %s",name.c_str());

        command_subscribe_01 = this->create_subscription<std_msgs::msg::String>("/greet",10,std::bind(&TopicSubscribe01::command_callback_01,this,std::placeholders::_1));
        command_subscribe_02 = this->create_subscription<std_msgs::msg::Int32>("/number",10,std::bind(&TopicSubscribe01::command_callback_02,this,std::placeholders::_1));
    }

    private:
        std::string msg_1 ="";
        std::int32_t msg_3 =0;

        bool has_msg_01 =false;
        bool has_msg_02 =false;

        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_01;
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr command_subscribe_02;

        void command_callback_01(const std_msgs::msg::String::SharedPtr msg)
        {
            msg_1 =msg->data;
            has_msg_01 =true;
            mix_msg();
        }

        void command_callback_02(const std_msgs::msg::Int32::SharedPtr msg)
        {
            msg_3 =msg->data;
            has_msg_02 =true;
            mix_msg();
        }

        void mix_msg()
        {
            if(has_msg_01 && has_msg_02)
            {
                std::string mix =msg_1+""+std::to_string(msg_3);
                RCLCPP_INFO(this->get_logger(),"mixed:%s",mix.c_str());
                has_msg_01 =false;
                has_msg_02 =false;
            }
        }
    
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
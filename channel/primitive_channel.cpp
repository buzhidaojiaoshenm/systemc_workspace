#include <systemc.h>
#include <string>

/**
 * @brief GENERATOR_IF 是一个中断生成器接口类，继承自 sc_interface。
 * 它包含一个纯虚函数 notify()，用于通知中断。
 *
 */
class GENERATOR_IF : public sc_interface
{
    public:
        virtual void notify() = 0;
};

/**
 * @brief RECEIVER_IF 是一个中断接收器接口类，继承自 sc_interface。
 * 它包含一个纯虚函数 default_event()，返回一个 sc_event 引用，用于在 sensitive 语句中使用。
 *
 */
class RECEIVER_IF : public sc_interface
{
    public:
        virtual const sc_event &default_event() const = 0; // needed for sensitive
};

/**
 * @brief INTERRUPT 类继承自 sc_prim_channel、GENERATOR_IF 和 RECEIVER_IF，实现了中断生成和接收功能。
 * 构造函数 INTERRUPT(sc_module_name name) 初始化基类 sc_prim_channel(name)。
 * notify() 方法实现了 GENERATOR_IF 接口，用于触发事件 e。
 * default_event() 方法实现了 RECEIVER_IF 接口，返回事件 e 的引用。
 * sc_event e 是一个私有事件，用于同步。
 */
class INTERRUPT : public sc_prim_channel, public GENERATOR_IF, public RECEIVER_IF
{ // interrupt class
    public:
        INTERRUPT(sc_module_name name) : sc_prim_channel(name) {} // constructor, construct sc_prim_channel
        void notify()
        { // implement GENERATOR_IF
            e.notify();
        }
        const sc_event &default_event() const
        { // implement RECEIVER_IF
            return e;
        }
    private:
        sc_event e; // private event for synchronization
};

/**
 * @brief 模块是一个中断生成器类。
 * sc_port<GENERATOR_IF> p 定义了一个中断生成器端口。
 * 构造函数 SC_CTOR(GENERATOR) 创建一个线程 gen_interrupt。
 * gen_interrupt 方法在一个无限循环中每隔1秒触发一次中断。
 */
SC_MODULE(GENERATOR)
{                            // interrupt generator class
    sc_port<GENERATOR_IF> p; // port to generate interrupt
    SC_CTOR(GENERATOR)
    { // constructor
        SC_THREAD(gen_interrupt);
    }
    void gen_interrupt()
    {
        while (true)
        {
            p->notify(); // calls notify function of the INTERRUPT channel
            wait(1, SC_SEC);
        }
    }
};

/**
 * @brief 模块是一个中断接收器类。
 * sc_port<RECEIVER_IF> p 定义了一个中断接收器端口。
 * 构造函数 SC_CTOR(RECEIVER) 创建一个线程 rcv_interrupt，并设置敏感信号 sensitive << p，监控端口 p 上的中断。
 * rcv_interrupt 方法在每次中断触发时被调用，输出时间戳和中断接收信息。
 */
SC_MODULE(RECEIVER)
{                           // interrupt receiver class
    sc_port<RECEIVER_IF> p; // port to receive interrupt
    SC_CTOR(RECEIVER)
    { // constructor
        SC_THREAD(rcv_interrupt);
        sensitive << p; // monitors interrupt on port p
        dont_initialize();
    }
    void rcv_interrupt()
    { // triggered upon interrupt
        while (true)
        {
            std::cout << sc_time_stamp() << ": interrupt received" << std::endl;
            wait();
        }
    }
};

int sc_main(int, char *[])
{
    GENERATOR generator("generator"); // instantiate generator
    RECEIVER receiver("receiver");    // instantiate receiver
    INTERRUPT interrupt("interrupt"); // instantiate interrupt
    generator.p(interrupt);           // port binding
    receiver.p(interrupt);            // port binding
    sc_start(5, SC_SEC);
    return 0;
}

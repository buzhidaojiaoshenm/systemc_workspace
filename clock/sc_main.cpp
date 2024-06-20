#include <systemc.h>

SC_MODULE(CLOCK)
{
    sc_port<sc_signal_in_if<bool>> clk; // a port to access clock
    SC_CTOR(CLOCK)
    {
        SC_THREAD(thread); // register a thread process
        sensitive << clk;  // sensitive to clock
        dont_initialize();
    }
    void thread()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << ", value = " << clk->read() << std::endl; // print current clock value
            wait();                                                                   // wait for next clock value change
        }
    }
};

int sc_main(int, char *[])
{
    sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, false);   // 10s period, 2s true, 8s false, start at 10s, start at false.
    CLOCK clock("clock");                                    // instantiate module
    clock.clk(clk);                                          // bind port
    sc_trace_file *file = sc_create_vcd_trace_file("trace"); // open trace file
    sc_trace(file, clk, "clk");                              // trace "s" under the name of "signal"
    sc_start(100, SC_NS);                                    // run simulation for 5 s
    sc_close_vcd_trace_file(file);                           // close trace file
    return 0;
}

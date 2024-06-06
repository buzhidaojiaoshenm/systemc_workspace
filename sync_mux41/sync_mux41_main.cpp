/**
 * sc_main生成用vcd格式的仿真波形记录文件，让仿真连续运行100ns。
 */
#include "sync_mux41_driver.h"
#include "sync_mux41_monitor.h"
#include "sync_mux41.h"

const int CLOCK_PERIOD = 2;

int sc_main(int argc, char *argv[])
{
    sc_signal<bool> t_reset;
    sc_signal<sc_uint<4>> t_inp;
    sc_signal<sc_uint<2>> t_sel;
    sc_signal<bool> t_out;

    sc_clock t_clock("clock", CLOCK_PERIOD);

    sync_mux41 m1("SyncMuxer4x1");
    m1(t_clock, t_reset, t_sel, t_inp, t_out);

    driver d1("GenerateWaveforms");
    d1(t_reset, t_sel, t_inp);

    monitor mo1("MonitorWaveforms");
    mo1(t_clock, t_reset, t_sel, t_inp, t_out);

    sc_trace_file *tf = sc_create_vcd_trace_file("sync_mux41");
    sc_trace(tf, t_clock, "clock");
    sc_trace(tf, t_reset, "reset");
    sc_trace(tf, t_inp, "input");
    sc_trace(tf, t_sel, "select");
    sc_trace(tf, t_out, "output");

    sc_start(100, SC_NS);

    sc_close_vcd_trace_file(tf);
    cout << "successful\n";
    return 0;
}
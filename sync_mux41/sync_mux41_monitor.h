/**
 * 只要多路器输入和输出端口的值发生任何改变，模块monitor将打印出所有输入端口和输出端口的值。
 */
#include <systemc.h>

SC_MODULE(monitor)
{
    sc_in<bool> m_clock, m_reset;
    sc_in<sc_uint<2>> m_sel;
    sc_in<sc_uint<4>> m_inp;
    sc_in<bool> m_out;

    void prc_monitor();

    SC_CTOR(monitor)
    {
        SC_METHOD(prc_monitor);
        sensitive << m_clock << m_reset << m_sel << m_inp << m_out;
    }
};

void monitor::prc_monitor()
{
    cout << "At time " << sc_simulation_time() << "::";
    cout << "(clock, reset, sel, inp): ";
    cout << m_clock.read() << "," << m_reset.read() << "," << m_sel.read() << "," << m_inp.read();
    cout << " out:" << m_out.read() << "\n";
}
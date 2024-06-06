/**
 * driver生成所有的可能的输入模式，每隔3ns向多路器施加其中一组输入模式。
 */
#include <systemc.h>
 
SC_MODULE(driver)
{
    sc_out<bool> d_reset;
    sc_out<sc_uint<2> > d_sel;
    sc_out<sc_uint<4> > d_inp;
 
    void prc_driver();
 
    SC_CTOR(driver)
    {
        SC_THREAD(prc_driver);
    }
};
 
void driver::prc_driver()
{
    d_reset =0;
    wait(7, SC_NS);
    d_reset =1;
 
    for(int i=0; i<=15; i++)
    {
        d_inp =i;
        for(int j=0; j<=3; j++)
        {
            d_sel = j;
            wait(3, SC_NS);
        }
    }
}
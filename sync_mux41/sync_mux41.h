/**
 * 带锁存输出的4选1多路器模型。输出在信号clock的正跳变沿时刻被锁存。
 */
#include <systemc.h>
 
SC_MODULE(sync_mux41)
{
    sc_in<bool> clock, reset;
    sc_in<sc_uint<2>> sel;
    sc_in<sc_uint<4>> inp;
    sc_out<bool> out;
 
    void prc_sync_mux41();
 
    SC_CTOR(sync_mux41)
    {
        SC_METHOD(prc_sync_mux41);
        sensitive << clock.pos();
        sensitive << reset.neg();
    }
 
};
 
void sync_mux41::prc_sync_mux41()
{
    sc_uint<4> temp_inp;
 
    temp_inp =inp.read();
 
    if(reset ==0)
    {
        out =0;
    }
    else
    {
        if(sel.read()==0) 
        {
            out = temp_inp[0];
        }
        else if(sel.read()==1) 
        {
            out = temp_inp[1];
        }
        else if(sel.read()==2) 
        {
            out = temp_inp[2];
        }
        else 
        {
            out = temp_inp[3];
        }
        
    }
 
}
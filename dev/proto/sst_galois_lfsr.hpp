#ifndef SST_GALOIS_LFSR_HPP
#define SST_GALOIS_LFSR_HPP

#include "sstscit.hpp"

#include <sst/core/component.h>
#include <sst/core/elementinfo.h>


class sst_galois_lfsr : public SST::Component {

public:

    sst_galois_lfsr(SST::ComponentId_t, SST::Params &);

    ~sst_galois_lfsr() override;

    void setup() override;

    void finish() override;

    bool tick(SST::Cycle_t);

    // Register the component
    SST_ELI_REGISTER_COMPONENT(
            sst_galois_lfsr, // class
            "sst_galois_lfsrSST", // element library
            "sst_galois_lfsr", // component
            SST_ELI_ELEMENT_VERSION(1, 0, 0),
            "Simple 4-bit Galois Linear Feedback Shift Register",
            COMPONENT_CATEGORY_UNCATEGORIZED
    )

private:

    // SST parameters
    SST::Output m_output;
    std::string m_proc;

    //  Prepare our context and socket
    zmq::context_t m_context;
    zmq::socket_t m_socket;

    zmq::message_t m_buf_in, m_buf_out;
    signal_packet m_data_in, m_data_out;

    msgpack::sbuffer m_sbuf;
    msgpack::packer<msgpack::sbuffer> m_packer;
    msgpack::unpacked m_unpacked_buf;

};

#endif

#ifndef FIB_SOCK_HPP
#define FIB_SOCK_HPP

#include "../../src/sstscit.hpp"

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/elementinfo.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>


class fib_lfsr : public SST::Component {

public:

    fib_lfsr(SST::ComponentId_t, SST::Params &);

    void setup() override;

    void finish() override;

    bool tick(SST::Cycle_t);

    void handle_event(SST::Event *);

    // Register the component
    SST_ELI_REGISTER_COMPONENT(
        fib_lfsr, // class
        "proto", // element library
        "fib_lfsr", // component
        SST_ELI_ELEMENT_VERSION(1, 0, 0),
        "Simple 4-bit Fibonacci Linear Feedback Shift Register",
        COMPONENT_CATEGORY_UNCATEGORIZED
    )

    // Port name, description, event type
    SST_ELI_DOCUMENT_PORTS(
        { "fib_din", "Fibonacci LFSR reset", { "sst.Interfaces.StringEvent" }},
        { "fib_dout", "Fibonacci LFSR data_out", { "sst.Interfaces.StringEvent" }},
    )

private:

    SST::Link *m_din_link, *m_dout_link;

    // SST parameters
    SST::Output m_output;
    std::string m_clock, m_proc, m_ipc_port;

    SignalSocket m_signal_io;

};

#endif

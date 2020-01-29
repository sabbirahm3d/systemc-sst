#!/usr/bin/env python
# -*- coding: utf-8 -*-

from random import SystemRandom
from string import ascii_uppercase, digits
import os

import sst

BASE_PATH = os.getcwd()

CLOCK = "1Hz"
SEED = 0

LINK_DELAY = "1ps"


def get_rand_tmp():
    return "/tmp/" + ''.join(
        SystemRandom().choice(ascii_uppercase + digits) for _ in range(8)
    )


# SystemC
systemc_main = sst.Component(
    "Strain Statistics", "plague.strain_stats")
systemc_main.addParams({
    "CLOCK": CLOCK,
})

severity_comp = sst.Component(
    "Severity Component (SystemC)", "plague.randf")
severity_comp.addParams({
    "clock": CLOCK,
    "proc": os.path.join(BASE_PATH, "randf.o"),
    "ipc_port": get_rand_tmp(),
})

infectivity_comp = sst.Component(
    "Infectivity Component (SystemC)", "plague.randf")
infectivity_comp.addParams({
    "clock": CLOCK,
    "proc": os.path.join(BASE_PATH, "randf.o"),
    "ipc_port": get_rand_tmp(),
})

lethality_comp = sst.Component(
    "Lethality Component (SystemC)", "plague.randf")
lethality_comp.addParams({
    "clock": CLOCK,
    "proc": os.path.join(BASE_PATH, "randf.o"),
    "ipc_port": get_rand_tmp(),
})

# # PyRTL
# pyrtl_main = sst.Component(
#     "Traffic Light (PyRTL)", "plague.traffic_light_pyrtl")
# pyrtl_main.addParams({
#     "CLOCK": CLOCK,
# })
# pyrtl_comp = sst.Component(
#     "PyRTL Component", "plague.pyrtl_fsm")
# pyrtl_comp.addParams({
#     "clock": CLOCK,
#     "proc": os.path.join(BASE_PATH, "../pyrtl/blackboxes/pyrtl_fsm_driver.py"),
#     "ipc_port": get_rand_tmp(),
# })

# Plague Simulation main driver
# plague = sst.Component("plague", "plague.plague")
# plague.addParams({
#     "CLOCK": CLOCK,
#     "SEED": SEED,
# })

# connect the subcomponents
sst.Link("severity_din").connect(
    (severity_comp, "randf_din", LINK_DELAY),
    (systemc_main, "severity_din", LINK_DELAY)
)
sst.Link("severity_dout").connect(
    (severity_comp, "randf_dout", LINK_DELAY),
    (systemc_main, "severity_dout", LINK_DELAY)
)

sst.Link("infectivity_din").connect(
    (infectivity_comp, "randf_din", LINK_DELAY),
    (systemc_main, "infectivity_din", LINK_DELAY)
)
sst.Link("infectivity_dout").connect(
    (infectivity_comp, "randf_dout", LINK_DELAY),
    (systemc_main, "infectivity_dout", LINK_DELAY)
)

sst.Link("lethality_din").connect(
    (lethality_comp, "randf_din", LINK_DELAY),
    (systemc_main, "lethality_din", LINK_DELAY)
)
sst.Link("lethality_dout").connect(
    (lethality_comp, "randf_dout", LINK_DELAY),
    (systemc_main, "lethality_dout", LINK_DELAY)
)

# sst.Link("py_din").connect(
#     (pyrtl_comp, "pyrtl_fsm_din", LINK_DELAY),
#     (pyrtl_main, "py_din", LINK_DELAY)
# )
# sst.Link("py_dout").connect(
#     (pyrtl_comp, "pyrtl_fsm_dout", LINK_DELAY),
#     (pyrtl_main, "py_dout", LINK_DELAY)
# )
# sst.Link("light1").connect(
#     (plague, "light1", LINK_DELAY),
#     (pyrtl_main, "light_state", LINK_DELAY)
# )

# sst.Link("cars0").connect(
#     (plague, "cars0", LINK_DELAY),
#     (car_generator0, "is_car", LINK_DELAY)
# )
# sst.Link("cars1").connect(
#     (plague, "cars1", LINK_DELAY),
#     (car_generator1, "is_car", LINK_DELAY)
# )

sst.setProgramOption("stopAtCycle", "20s")
/**
Car Generator for carWash simulator

This component generates "cars" which are sent to the carwash
*/

#include <sst/core/sst_config.h>
#include <sst/core/interfaces/stringEvent.h>
#include "carGenerator.h"

using SST::Interfaces::StringEvent;

carGenerator::carGenerator( SST::ComponentId_t id, SST::Params& params ) : SST::Component(id) {
	
	output.init("carGenerator-" + getName() + "-> ", 1, 0, SST::Output::STDOUT);

	// Get parameters
	clock = params.find<std::string>("delay", "1s");
	RandomSeed = params.find<int64_t>("randomseed", 151515);
        output.verbose(CALL_INFO, 1, 0, "Minimum Delay Between Cars=%gs, Random Number Seed=%ld\n",std::stof(clock),RandomSeed);

	// Register the clock
	registerClock(clock, new SST::Clock::Handler<carGenerator>(this, &carGenerator::clockTick));
	
	// Initialize random
	rng = new SST::RNG::MarsagliaRNG(11, RandomSeed);
	
	// Configure our port
	port = configureLink("port");
	if ( !port ) {
		output.fatal(CALL_INFO, -1, "Failed to configure port 'port'\n");
	}
}

carGenerator::~carGenerator() {

}

void carGenerator::setup() {
	
}

void carGenerator::finish() {
	
}

bool carGenerator::clockTick( SST::Cycle_t currentCycle ) {
	// generating a random number between 0 and 1
	// 0 = No Car
	// 1 = Car
	int rndNumber;
	rndNumber = (int)(rng->generateNextInt32());		
	rndNumber = (rndNumber & 0x0000FFFF) ^ ((rndNumber & 0xFFFF0000) >> 16);
	rndNumber = abs((int)(rndNumber % 2));

	port->send(new StringEvent(std::to_string(rndNumber)));
	return false;
}


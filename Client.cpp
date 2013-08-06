/*
 * Copyright (C) 2013 Andrea Zoli
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include"Client.h"
#include<Servant.h>
#include<iostream>
#include<cstdlib>
#include<signal.h>

int counter;
IceUtil::Time tm;
long size;

void sig_handler(int signo)
{

    if (signo == SIGINT)
	{
        tm = IceUtil::Time::now(IceUtil::Time::Monotonic) - tm;
		double mbit = counter * size * 8 / (tm.toSecondsDouble() * 1000000);
		std::cout << "Throughput: " << mbit << " mbps" << std::endl;
        exit(1);
	}
}

Client::Client() : Ice::Application(Ice::NoSignalHandling)
{
}

int Client::run(int argc, char* argv[])
{
    signal(SIGINT, sig_handler);

	counter = 0;
	size = 128000;
    if(argc > 1)
        size = std::atol(argv[1]);

	std::cout << "Using size " << size << std::endl;

    Ice::CommunicatorPtr ic = communicator();

    // creating a Servant proxy
    Ice::ObjectPrx objPrx = ic->propertyToProxy("Host.proxy");
    CIWS::ServantPrx servantPrx = CIWS::ServantPrx::checkedCast(objPrx);
	CIWS::ServantPrx onewayPrx = servantPrx->ice_oneway();
    if(!servantPrx)
        throw "Invalid Proxy";

	// creating the packet
    CIWS::Packet packet;
    for(long i=0; i<size; i++)
    {
        packet.push_back((char)(i%8));
    }

    tm = IceUtil::Time::now(IceUtil::Time::Monotonic);
    while(1)
	{
		counter++;
		std::pair<const Ice::Byte*, const Ice::Byte*> p;
		p.first = &packet[0];
		p.second = p.first + packet.size();
        onewayPrx->newPacket(p);
	}

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    Client cli;
    return cli.main(argc, argv, "Client.config");
}

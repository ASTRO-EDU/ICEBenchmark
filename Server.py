#
# Copyright (C) 2013 Andrea Zoli
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

import sys
import Ice
Ice.loadSlice('Servant.ice')
Ice.updateModules()
import CIWS

class ServantI(CIWS.Servant):

    def newPacket(self, packet, current=None):
		pass

class Application(Ice.Application):

    def run(self, args):
        ic = self.communicator()
        adapter = ic.createObjectAdapter("ServerAdapter")
        servant = ServantI()
        adapter.add(servant, ic.stringToIdentity("Servant"))
        adapter.activate()
        ic.waitForShutdown()

app = Application()
app.main(sys.argv, "Server.config")

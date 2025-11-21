//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

import ned.IdealChannel;


network TorrentNetwork
{
    submodules:
        source_A: mySource {
            @display("p=129,221");
        }
        sink_A: mySink {
            @display("p=129,163");
        }
        queue_A: myQueue {

            @display("p=245,193");
        }
        source_B: mySource {
            @display("p=346,69");
        }
        sink_B: mySink {
            @display("p=289,69");
        }
        queue_B: myQueue {

            @display("p=321,143");
        }
        source_C: mySource {
            @display("p=504,221");
        }
        sink_C: mySink {
            @display("p=504,163");
        }
        queue_C: myQueue {

            @display("p=400,193");
        }
        source_D: mySource {
            @display("p=346,324");
        }
        sink_D: mySink {
            @display("p=293,324");
        }
        queue_D: myQueue {

            @display("p=321,249");
        }
    connections:
        queue_A.out --> IdealChannel --> sink_A.in++;
        source_A.out --> IdealChannel --> queue_A.in++;
        queue_D.out --> IdealChannel --> sink_D.in++;
        source_D.out --> IdealChannel --> queue_D.in++;
        queue_C.out --> IdealChannel --> sink_C.in++;
        source_C.out --> IdealChannel --> queue_C.in++;
        queue_B.out --> IdealChannel --> sink_B.in++;
        source_B.out --> IdealChannel --> queue_B.in++;
}

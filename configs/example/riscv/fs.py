# Copyright (c) 2018 TU Dresden
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors: Robert Scheffel

'''
Full system script
'''

import argparse
import fssystem

import m5
from m5.objects import *

m5.util.addToPath('../..')
from common import MemConfig

cpu_types = {
    'atomic': AtomicSimpleCPU,
    'timing': TimingSimpleCPU,
    'minor': MinorCPU
}


def create(args):
    '''Create the system and configure it'''
    cpu_class = cpu_types[args.cpu]
    mem_mode = cpu_class.memory_mode()

    system = fssystem.SimpleSystem(cpu_class=cpu_class,
                                   wfgdb=args.wait_for_gdb,
                                   mem_mode=mem_mode,
                                   bootloader=args.binary)

    # some required stuff
    mem_type = 'DDR3_1600_8x8'
    mem_channels = 1
    args.mem_type = mem_type
    args.mem_channels = mem_channels

    MemConfig.config_mem(args, system)

    system.connect()

    return system


def run():
    '''Run the simulation'''
    exit_event = m5.simulate()
    print('Exiting because %s @ %d ' % (exit_event.getCause(), m5.curTick()))


def main():
    parser = argparse.ArgumentParser(epilog=__doc__)

    parser.add_argument('-b',
                        '--binary',
                        type=str,
                        default=None,
                        required=True,
                        help='The binary to run')
    parser.add_argument('--cpu',
                        type=str,
                        default='atomic',
                        help='CPU model to use')
    parser.add_argument('-w',
                        '--wait-for-gdb',
                        action='store_true',
                        help='Wait for remote gdb connection '
                        'before starting simulation')

    args = parser.parse_args()

    root = Root(full_system=True)
    root.system = create(args)

    m5.instantiate()

    run()


if __name__ == '__m5_main__':
    main()

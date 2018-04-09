/*
 * Copyright (c) 2013 ARM Limited
 * Copyright (c) 2014-2015 Sven Karlsson
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2016 The University of Virginia
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Andreas Hansson
 *          Sven Karlsson
 *          Alec Roelke
 */

#ifndef __ARCH_RISCV_ISA_TRAITS_HH__
#define __ARCH_RISCV_ISA_TRAITS_HH__

#include "arch/riscv/types.hh"
#include "base/types.hh"
#include "cpu/static_inst_fwd.hh"

namespace LittleEndianGuest {}

namespace RiscvISA
{

using namespace LittleEndianGuest;

const Addr PageShift = 12;
const Addr PageBytes = ULL(1) << PageShift;

// Memory accesses can be unaligned (at least for double-word memory accesses)
const bool HasUnalignedMemAcc = true;

const bool CurThreadInfoImplemented = false;
const int CurThreadInfoReg = -1;

////////////////////////////////////////////////////////////////////////
//
//  Interrupt types
//
enum InterruptTypes
{
    INT_USI =  0,  // user software interrupt
    INT_SSI =  1,  // supervisor software interrupt
    INT_MSI =  3,  // machine software interrupt

    INT_UTI =  4,  // user timer interrupt
    INT_STI =  5,  // supervisor timer interrupt
    INT_MTI =  7,  // machine time interrupt

    INT_UEI =  8,  // user external interrupt
    INT_SEI =  9,  // supervisor external interrupt
    INT_MEI = 11,   // machine external interrupt

    NumInterruptTypes = 12
};

}

#endif //__ARCH_RISCV_ISA_TRAITS_HH__

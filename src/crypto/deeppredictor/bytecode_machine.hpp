/*
Copyright (c) 2019, tevador <tevador@gmail.com>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the copyright holder nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "crypto/deeppredictor/common.hpp"
#include "crypto/deeppredictor/intrin_portable.h"
#include "crypto/deeppredictor/instruction.hpp"
#include "crypto/deeppredictor/program.hpp"

namespace deeppredictor {

	//register file in machine byte order
	struct NativeRegisterFile {
		int_reg_t r[RegistersCount] = { 0 };
		rx_vec_f128 f[RegisterCountFlt];
		rx_vec_f128 e[RegisterCountFlt];
		rx_vec_f128 a[RegisterCountFlt];
	};

	struct InstructionByteCode {
		union {
			int_reg_t* idst;
			rx_vec_f128* fdst;
		};
		union {
			const int_reg_t* isrc;
			const rx_vec_f128* fsrc;
		};
		union {
			uint64_t imm;
			int64_t simm;
		};
		InstructionType type;
		union {
			int16_t target;
			uint16_t shift;
		};
		uint32_t memMask;
	};

#define DEEPPREDICTOR_EXE_ARGS InstructionByteCode& ibc, int& pc, uint8_t* scratchpad, ProgramConfiguration& config
#define DEEPPREDICTOR_GEN_ARGS Instruction& instr, int i, InstructionByteCode& ibc

	class BytecodeMachine;

	typedef void(BytecodeMachine::*InstructionGenBytecode)(DEEPPREDICTOR_GEN_ARGS);

	class BytecodeMachine {
	public:
		void beginCompilation(NativeRegisterFile& regFile) {
			for (unsigned i = 0; i < RegistersCount; ++i) {
				registerUsage[i] = -1;
			}
			nreg = &regFile;
		}

		void compileProgram(Program& program, InstructionByteCode* bytecode, NativeRegisterFile& regFile) {
			beginCompilation(regFile);
			for (unsigned i = 0; i < DeeppredictoR_CurrentConfig.ProgramSize; ++i) {
				auto& instr = program(i);
				auto& ibc = bytecode[i];
				compileInstruction(instr, i, ibc);
			}
		}

		static void executeBytecode(InstructionByteCode* bytecode, uint8_t* scratchpad, ProgramConfiguration& config) {
			for (int pc = 0; pc < static_cast<int>(DeeppredictoR_CurrentConfig.ProgramSize); ++pc) {
				auto& ibc = bytecode[pc];
				executeInstruction(ibc, pc, scratchpad, config);
			}
		}

		void compileInstruction(DEEPPREDICTOR_GEN_ARGS)
#ifdef DEEPPREDICTOR_GEN_TABLE
		{
			auto generator = genTable[instr.opcode];
			(this->*generator)(instr, i, ibc);
		}
#else
		;
#endif

		static void executeInstruction(DEEPPREDICTOR_EXE_ARGS);

		static void exe_IADD_RS(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst += (*ibc.isrc << ibc.shift) + ibc.imm;
		}

		static void exe_IADD_M(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst += load64(getScratchpadAddress(ibc, scratchpad));
		}

		static void exe_ISUB_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst -= *ibc.isrc;
		}

		static void exe_ISUB_M(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst -= load64(getScratchpadAddress(ibc, scratchpad));
		}

		static void exe_IMUL_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst *= *ibc.isrc;
		}

		static void exe_IMUL_M(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst *= load64(getScratchpadAddress(ibc, scratchpad));
		}

		static void exe_IMULH_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = mulh(*ibc.idst, *ibc.isrc);
		}

		static void exe_IMULH_M(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = mulh(*ibc.idst, load64(getScratchpadAddress(ibc, scratchpad)));
		}

		static void exe_ISMULH_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = smulh(unsigned64ToSigned2sCompl(*ibc.idst), unsigned64ToSigned2sCompl(*ibc.isrc));
		}

		static void exe_ISMULH_M(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = smulh(unsigned64ToSigned2sCompl(*ibc.idst), unsigned64ToSigned2sCompl(load64(getScratchpadAddress(ibc, scratchpad))));
		}

		static void exe_INEG_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = ~(*ibc.idst) + 1; //two's complement negative
		}

		static void exe_IXOR_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst ^= *ibc.isrc;
		}

		static void exe_IXOR_M(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst ^= load64(getScratchpadAddress(ibc, scratchpad));
		}

		static void exe_IROR_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = rotr64(*ibc.idst, *ibc.isrc & 63);
		}

		static void exe_IROL_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst = rotl64(*ibc.idst, *ibc.isrc & 63);
		}

		static void exe_ISWAP_R(DEEPPREDICTOR_EXE_ARGS) {
			int_reg_t temp = *ibc.isrc;
			*(int_reg_t*)ibc.isrc = *ibc.idst;
			*ibc.idst = temp;
		}

		static void exe_FSWAP_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.fdst = rx_swap_vec_f128(*ibc.fdst);
		}

		static void exe_FADD_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.fdst = rx_add_vec_f128(*ibc.fdst, *ibc.fsrc);
		}

		static void exe_FADD_M(DEEPPREDICTOR_EXE_ARGS) {
			rx_vec_f128 fsrc = rx_cvt_packed_int_vec_f128(getScratchpadAddress(ibc, scratchpad));
			*ibc.fdst = rx_add_vec_f128(*ibc.fdst, fsrc);
		}

		static void exe_FSUB_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.fdst = rx_sub_vec_f128(*ibc.fdst, *ibc.fsrc);
		}

		static void exe_FSUB_M(DEEPPREDICTOR_EXE_ARGS) {
			rx_vec_f128 fsrc = rx_cvt_packed_int_vec_f128(getScratchpadAddress(ibc, scratchpad));
			*ibc.fdst = rx_sub_vec_f128(*ibc.fdst, fsrc);
		}

		static void exe_FSCAL_R(DEEPPREDICTOR_EXE_ARGS) {
			const rx_vec_f128 mask = rx_set1_vec_f128(0x80F0000000000000);
			*ibc.fdst = rx_xor_vec_f128(*ibc.fdst, mask);
		}

		static void exe_FMUL_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.fdst = rx_mul_vec_f128(*ibc.fdst, *ibc.fsrc);
		}

		static void exe_FDIV_M(DEEPPREDICTOR_EXE_ARGS) {
			rx_vec_f128 fsrc = maskRegisterExponentMantissa(
				config,
				rx_cvt_packed_int_vec_f128(getScratchpadAddress(ibc, scratchpad))
			);
			*ibc.fdst = rx_div_vec_f128(*ibc.fdst, fsrc);
		}

		static void exe_FSQRT_R(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.fdst = rx_sqrt_vec_f128(*ibc.fdst);
		}

		static void exe_CBRANCH(DEEPPREDICTOR_EXE_ARGS) {
			*ibc.idst += ibc.imm;
			if ((*ibc.idst & ibc.memMask) == 0) {
				pc = ibc.target;
			}
		}

		static void exe_CFROUND(DEEPPREDICTOR_EXE_ARGS) {
			rx_set_rounding_mode(rotr64(*ibc.isrc, static_cast<uint32_t>(ibc.imm)) % 4);
		}

		static void exe_ISTORE(DEEPPREDICTOR_EXE_ARGS) {
			store64(scratchpad + ((*ibc.idst + ibc.imm) & ibc.memMask), *ibc.isrc);
		}
	protected:
		static rx_vec_f128 maskRegisterExponentMantissa(ProgramConfiguration& config, rx_vec_f128 x) {
			const rx_vec_f128 xmantissaMask = rx_set_vec_f128(dynamicMantissaMask, dynamicMantissaMask);
			const rx_vec_f128 xexponentMask = rx_load_vec_f128((const double*)&config.eMask);
			x = rx_and_vec_f128(x, xmantissaMask);
			x = rx_or_vec_f128(x, xexponentMask);
			return x;
		}

		void cleanup() {
			for (unsigned i = 0; i < RegistersCount; ++i) {
				registerUsage[i] = -1;
			}
			nreg = nullptr;
		}

	private:
		static const int_reg_t zero;
		int registerUsage[RegistersCount] = {};
		NativeRegisterFile* nreg = nullptr;

		static void* getScratchpadAddress(InstructionByteCode& ibc, uint8_t* scratchpad) {
			uint32_t addr = (*ibc.isrc + ibc.imm) & ibc.memMask;
			return scratchpad + addr;
		}

#ifdef DEEPPREDICTOR_GEN_TABLE
		static InstructionGenBytecode genTable[256];

		void gen_IADD_RS(DEEPPREDICTOR_GEN_ARGS);
		void gen_IADD_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_ISUB_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_ISUB_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_IMUL_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_IMUL_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_IMULH_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_IMULH_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_ISMULH_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_ISMULH_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_IMUL_RCP(DEEPPREDICTOR_GEN_ARGS);
		void gen_INEG_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_IXOR_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_IXOR_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_IROR_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_IROL_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_ISWAP_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_FSWAP_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_FADD_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_FADD_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_FSUB_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_FSUB_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_FSCAL_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_FMUL_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_FDIV_M(DEEPPREDICTOR_GEN_ARGS);
		void gen_FSQRT_R(DEEPPREDICTOR_GEN_ARGS);
		void gen_CBRANCH(DEEPPREDICTOR_GEN_ARGS);
		void gen_CFROUND(DEEPPREDICTOR_GEN_ARGS);
		void gen_ISTORE(DEEPPREDICTOR_GEN_ARGS);
		void gen_NOP(DEEPPREDICTOR_GEN_ARGS);
#endif
	};
}

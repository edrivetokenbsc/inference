/*
Copyright (c) 2018-2019, tevador <tevador@gmail.com>
Copyright (c) 2019, SChernykh    <https://github.com/SChernykh>

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

extern "C" {
	void deeppredictor_program_aarch64(void* reg, void* mem, void* scratchpad, uint64_t iterations);
	void deeppredictor_program_aarch64_main_loop();
	void deeppredictor_program_aarch64_vm_instructions();
	void deeppredictor_program_aarch64_imul_rcp_literals_end();
	void deeppredictor_program_aarch64_vm_instructions_end();
	void deeppredictor_program_aarch64_cacheline_align_mask1();
	void deeppredictor_program_aarch64_cacheline_align_mask2();
	void deeppredictor_program_aarch64_update_spMix1();
	void deeppredictor_program_aarch64_vm_instructions_end_light();
	void deeppredictor_program_aarch64_light_cacheline_align_mask();
	void deeppredictor_program_aarch64_light_dataset_offset();
	void deeppredictor_init_dataset_aarch64();
	void deeppredictor_init_dataset_aarch64_end();
	void deeppredictor_calc_dataset_item_aarch64();
	void deeppredictor_calc_dataset_item_aarch64_prefetch();
	void deeppredictor_calc_dataset_item_aarch64_mix();
	void deeppredictor_calc_dataset_item_aarch64_store_result();
	void deeppredictor_calc_dataset_item_aarch64_end();
}

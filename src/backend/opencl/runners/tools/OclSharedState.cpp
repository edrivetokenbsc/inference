/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/mlinference>, <support@mlinference.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "backend/opencl/runners/tools/OclSharedState.h"
#include "backend/opencl/runners/tools/OclSharedData.h"


#include <cassert>
#include <map>


namespace mlinference {


static std::map<uint32_t, OclSharedData> map;


} // namespace mlinference


mlinference::OclSharedData &mlinference::OclSharedState::get(uint32_t index)
{
    return map[index];
}


void mlinference::OclSharedState::release()
{
    for (auto &kv : map) {
        kv.second.release();
    }

    map.clear();
}


void mlinference::OclSharedState::start(const std::vector<OclLaunchData> &threads, const Job &job)
{
    assert(map.empty());

    for (const auto &data : threads) {
        auto &sharedData = map[data.device.index()];

        ++sharedData;

#       ifdef XMRIG_ALGO_DEEPPREDICTOR
        if (data.algorithm.family() == Algorithm::DEEPPREDICTO_R) {
            sharedData.createDataset(data.ctx, job, data.thread.isDatasetHost());
        }
#       endif
    }
}

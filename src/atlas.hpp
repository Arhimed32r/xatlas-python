/**
 * MIT License
 * 
 * Copyright (c) 2021 Markus Worchel
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "utils.hpp"

#include <pybind11/pybind11.h>

#include <xatlas.h>

#include <cstdint>
#include <optional>
#include <tuple>

using MeshResult = std::tuple<ContiguousArray<std::uint32_t>, ContiguousArray<std::uint32_t>, ContiguousArray<float>>;

class Atlas
{
public:
    Atlas();

    virtual ~Atlas();

    void addMesh(ContiguousArray<float> const&         positions,
                 ContiguousArray<std::uint32_t> const& indices,
                 std::optional<ContiguousArray<float>> normals = std::nullopt,
                 std::optional<ContiguousArray<float>> uvs     = std::nullopt);

    void generate(xatlas::ChartOptions const& chartOptions = xatlas::ChartOptions(), xatlas::PackOptions const& packOptions = xatlas::PackOptions());

    MeshResult getMesh(std::uint32_t index);

    auto getAtlasCount() const
    {
        return m_atlas->atlasCount;
    }

    auto getMeshCount() const
    {
        return m_atlas->meshCount;
    }

    auto getChartCount() const
    {
        return m_atlas->chartCount;
    }

    auto getWidth() const
    {
        return m_atlas->width;
    }

    auto getHeight() const
    {
        return m_atlas->height;
    }

    auto getTexelsPerUnit() const
    {
        return m_atlas->texelsPerUnit;
    }

    auto getUtilization() const
    {
        return m_atlas->utilization;
    }

    static void bind(pybind11::module& m);

private:
    xatlas::Atlas* m_atlas;
};
#ifndef __KATO_FUNCTION_IMGUI_ADDONS_HPP__
#define __KATO_FUNCTION_IMGUI_ADDONS_HPP__

#pragma once

#include <string>
#include <algorithm>
#include "imgui.h"

namespace kato::function
{
    ImVec4 colorTable(const float input, const float min, const float max)
    {

        float output = (input - min) / (max - min);
        return {std::clamp(1 - (1 - 2 * output), 0.0f, 1.0f), 1 - abs(1 - 2 * output), std::clamp(2 - 2 * output, 0.0f, 1.0f), 1.0};
    }
    void HelpMarker(const std::string message)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(message.c_str());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
}

// # ==== imgui source file ==============================================================================================
// IMGUI_DIR = $(LIB_DIR)/imgui

// IMGUI_SOURCES = $(IMGUI_DIR)/backend/imgui_impl_glfw.cpp $(IMGUI_DIR)/backend/imgui_impl_opengl3.cpp
// IMGUI_SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/imgui_tables.cpp
// IMGUI_SOURCES += $(IMGUI_DIR)/addons/implot/implot.cpp $(IMGUI_DIR)/addons/implot/implot_items.cpp
// IMGUI_OBJS = $(addprefix .imgui_, $(addsuffix .o, $(basename $(notdir $(IMGUI_SOURCES)))))

// IMGUI_CXXFLAGS = -I$(IMGUI_DIR)
// # ==== imgui source file ==============================================================================================

#endif //__KATO_FUNCTION_IMGUI_ADDONS_HPP__
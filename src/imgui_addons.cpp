#include "kato/imgui_addons.h"

#include <algorithm>
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
void kato::function::HelpMarker(const std::string message)
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
// --------------------------------------------------------------------------------------------------------------------
ImVec4 kato::function::colorTable(const float input, const float min, const float max)
{
    
    float output = (input - min) / (max - min);
    return {std::clamp(1 - (1 - 2 * output), 0.0f, 1.0f), 1 - abs(1 - 2 * output), std::clamp(2 - 2 * output, 0.0f, 1.0f), 1.0};
}
// --------------------------------------------------------------------------------------------------------------------

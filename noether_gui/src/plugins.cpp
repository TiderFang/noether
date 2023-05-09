#include <noether_gui/plugin_interface.h>
#include <noether_gui/widgets/direction_generator_widgets.h>
#include <noether_gui/widgets/origin_generator_widgets.h>
#include <noether_gui/widgets/tool_path_modifier_widgets.h>
#include <noether_gui/widgets/blending_tool_path_modifier_widgets.h>
#include <noether_gui/widgets/raster_planner_widget.h>
#include <noether_gui/widgets/plane_slicer_raster_planner_widget.h>

#include <QWidget>
#include <QMessageBox>

namespace noether
{
template <typename T, typename BaseT>
struct WidgetPluginImpl : WidgetPlugin<BaseT>
{
  QWidget* create(QWidget* parent = nullptr, const YAML::Node& config = {}) const override final
  {
    auto widget = new T(parent);

    // Attempt to configure the widget
    if (!config.IsNull())
      widget->configure(config);

    return widget;
  }
};

// Direction Generators
using FixedDirectionGeneratorWidgetPlugin =
    WidgetPluginImpl<FixedDirectionGeneratorWidget, DirectionGeneratorWidgetPlugin>;

using PrincipalAxisDirectionGeneratorWidgetPlugin =
    WidgetPluginImpl<PrincipalAxisDirectionGeneratorWidget, DirectionGeneratorWidgetPlugin>;

// Origin Generators
using FixedOriginGeneratorWidgetPlugin = WidgetPluginImpl<FixedOriginGeneratorWidget, OriginGeneratorWidgetPlugin>;

using CentroidOriginGeneratorWidgetPlugin = WidgetPluginImpl<CentroidOriginGeneratorWidget, OriginGeneratorWidget>;

using AABBOriginGeneratorWidgetPlugin = WidgetPluginImpl<AABBOriginGeneratorWidget, OriginGeneratorWidget>;

// Tool Path Modifiers
using StandardEdgePathsOrganizationModifierWidgetPlugin =
    WidgetPluginImpl<StandardEdgePathsOrganizationModifierWidget, ToolPathModifierWidget>;

using RasterOrganizationModifierWidgetPlugin =
    WidgetPluginImpl<RasterOrganizationModifierWidget, ToolPathModifierWidget>;

using SnakeOrganizationModifierWidgetPlugin = WidgetPluginImpl<SnakeOrganizationModifierWidget, ToolPathModifierWidget>;

using FixedOrientationModifierWidgetPlugin = WidgetPluginImpl<FixedOrientationModifierWidget, ToolPathModifierWidget>;

using DirectionOfTravelOrientationModifierWidgetPlugin =
    WidgetPluginImpl<DirectionOfTravelOrientationModifierWidget, ToolPathModifierWidget>;

using UniformOrientationModifierWidgetPlugin =
    WidgetPluginImpl<UniformOrientationModifierWidget, ToolPathModifierWidget>;

using MovingAverageOrientationSmoothingModifierWidgetPlugin =
    WidgetPluginImpl<MovingAverageOrientationSmoothingModifierWidget, ToolPathModifierWidget>;

using ToolDragOrientationToolPathModifierWidgetPlugin =
    WidgetPluginImpl<ToolDragOrientationToolPathModifierWidget, ToolPathModifierWidget>;

using CircularLeadInToolPathModifierWidgetPlugin =
    WidgetPluginImpl<CircularLeadInToolPathModifierWidget, ToolPathModifierWidget>;

using CircularLeadOutToolPathModifierWidgetPlugin =
    WidgetPluginImpl<CircularLeadOutToolPathModifierWidget, ToolPathModifierWidget>;

// Raster Tool Path Planners
struct PlaneSlicerRasterPlannerWidgetPlugin : ToolPathPlannerWidgetPlugin
{
  QWidget* create(QWidget* parent = nullptr, const YAML::Node& config = {}) const override final
  {
    boost_plugin_loader::PluginLoader loader;
    loader.search_libraries.insert(NOETHER_GUI_PLUGINS);
    auto widget = new PlaneSlicerRasterPlannerWidget(std::move(loader), parent);

    // Attempt to configure the widget
    if (!config.IsNull())
      widget->configure(config);

    return widget;
  }
};

}  // namespace noether

EXPORT_DIRECTION_GENERATOR_WIDGET_PLUGIN(noether::FixedDirectionGeneratorWidgetPlugin, FixedDirectionGenerator)
EXPORT_DIRECTION_GENERATOR_WIDGET_PLUGIN(noether::PrincipalAxisDirectionGeneratorWidgetPlugin,
                                         PrincipalAxisDirectionGenerator)

EXPORT_ORIGIN_GENERATOR_PLUGIN(noether::FixedOriginGeneratorWidgetPlugin, FixedOriginGenerator)
EXPORT_ORIGIN_GENERATOR_PLUGIN(noether::CentroidOriginGeneratorWidgetPlugin, CentroidOriginGenerator)
EXPORT_ORIGIN_GENERATOR_PLUGIN(noether::AABBOriginGeneratorWidgetPlugin, AABBOriginGenerator)

EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::StandardEdgePathsOrganizationModifierWidgetPlugin,
                                        StandardEdgePathsOrganizationModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::RasterOrganizationModifierWidgetPlugin, RasterOrganizationModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::SnakeOrganizationModifierWidgetPlugin, SnakeOrganizationModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::FixedOrientationModifierWidgetPlugin, FixedOrientationModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::DirectionOfTravelOrientationModifierWidgetPlugin,
                                        DirectionOfTravelOrientationModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::UniformOrientationModifierWidgetPlugin, UniformOrientationModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::MovingAverageOrientationSmoothingModifierWidgetPlugin,
                                        MovingAverageOrientationSmoothingModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::ToolDragOrientationToolPathModifierWidgetPlugin,
                                        ToolDragOrientationToolPathModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::CircularLeadInToolPathModifierWidgetPlugin, CircularLeadInModifier)
EXPORT_TOOL_PATH_MODIFIER_WIDGET_PLUGIN(noether::CircularLeadOutToolPathModifierWidgetPlugin, CircularLeadOutModifier)

EXPORT_TPP_WIDGET_PLUGIN(noether::PlaneSlicerRasterPlannerWidgetPlugin, PlaneSlicerRasterPlanner)
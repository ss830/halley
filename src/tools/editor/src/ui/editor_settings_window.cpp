#include "editor_settings_window.h"


#include "halley/tools/project/project_loader.h"
#include "src/preferences.h"
using namespace Halley;

EditorSettingsWindow::EditorSettingsWindow(UIFactory& factory, Preferences& preferences, Project& project, ProjectLoader& projectLoader)
	: UIWidget("editor_settings_window", Vector2f(), UISizer())
	, factory(factory)
	, preferences(preferences)
	, project(project)
	, projectLoader(projectLoader)
{
	factory.loadUI(*this, "ui/halley/editor_settings");
}

void EditorSettingsWindow::onMakeUI()
{
	workingCopy.loadEditorPreferences(preferences);
	setSaveEnabled(false);

	auto platforms = getWidget("platforms");
	for (const auto& platform: projectLoader.getKnownPlatforms()) {
		const auto checkbox = std::make_shared<UICheckbox>(platform, factory.getStyle("checkbox"));
		checkbox->setEnabled(platform != "pc");
		
		platforms->add(checkbox);
		platforms->add(std::make_shared<UILabel>(platform + "_label", factory.getStyle("label").getTextRenderer("label"), LocalisedString::fromUserString(platform)));

		platforms->bindData(platform, !workingCopy.isPlatformDisabled(platform), [=] (bool value)
		{
			workingCopy.setPlatformDisabled(platform, !value);
			setSaveEnabled(true);
		});
	}

	setHandle(UIEventType::ButtonClicked, "save", [=] (const UIEvent& event)
	{
		save();
	});

	setHandle(UIEventType::ButtonClicked, "cancel", [=] (const UIEvent& event)
	{
		reset();
	});
}

void EditorSettingsWindow::save()
{
	preferences.loadEditorPreferences(workingCopy);
	projectLoader.setDisabledPlatforms(preferences.getDisabledPlatforms());
	projectLoader.selectPlugins(project);
	
	setSaveEnabled(false);
}

void EditorSettingsWindow::reset()
{
	workingCopy.loadEditorPreferences(preferences);

	auto platforms = getWidget("platforms");
	for (const auto& platform: projectLoader.getKnownPlatforms()) {
		platforms->getWidgetAs<UICheckbox>(platform)->setChecked(!workingCopy.isPlatformDisabled(platform));
	}

	setSaveEnabled(false);
}

void EditorSettingsWindow::setSaveEnabled(bool enabled)
{
	getWidget("save")->setEnabled(enabled);
	getWidget("cancel")->setEnabled(enabled);
}

#pragma once

#include "halley/core/api/halley_api.h"
#include "halley/ui/ui_factory.h"
#include "halley/ui/ui_widget.h"
#include "halley/ui/widgets/ui_list.h"
#include "halley/ui/widgets/ui_paged_pane.h"

namespace Halley {
	class ProjectWindow;
	class Project;
	class MetadataEditor;
	class AssetEditor;
	class AssetEditorWindow;
	
	class AssetsBrowser : public UIWidget {
    public:
        AssetsBrowser(UIFactory& factory, Project& project, ProjectWindow& projectWindow);
        void showAsset(AssetType type, const String& assetId);
		void showFile(const Path& path);

	private:
		UIFactory& factory;
		Project& project;
		ProjectWindow& projectWindow;

		std::map<AssetType, Path> curPaths;
		Path curSrcPath;
		AssetType curType = AssetType::Sprite;

		bool assetSrcMode = true;
		std::optional<std::vector<String>> assetNames;
		String filter;
        
		std::shared_ptr<UIList> assetList;
		std::shared_ptr<AssetEditorWindow> assetEditor;

        String lastClickedAsset;

		uint64_t curHash = 0;
		uint64_t curDirHash = 0;

        void loadResources();
        void makeUI();
		void setAssetSrcMode(bool enabled);
		void updateAddRemoveButtons();

		void listAssetSources();
		void listAssets(AssetType type);
		void setListContents(std::vector<String> files, const Path& curPath, bool flat);
		void refreshList();
		void setFilter(const String& filter);

		void loadAsset(const String& name, bool doubleClick);
		void refreshAssets(const std::vector<String>& assets);

		void addAsset();
		void removeAsset();

		Path getCurrentAssetPath() const;
		void openFileExternally(const Path& path);
		void showFileExternally(const Path& path);
	};
}

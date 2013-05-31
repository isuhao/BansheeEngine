#pragma once

#include "BsPrerequisites.h"
#include "BsGUISkin.h"
#include "CmModule.h"

namespace BansheeEngine
{
	class BS_EXPORT EngineGUI : public CamelotFramework::Module<EngineGUI>
	{
	public:
		EngineGUI();

		const GUISkin& getSkin() const { return mSkin; }
		const SpriteTexturePtr& getWindowBgTex() const { return mWindowBgTex; }

	private:
		GUISkin mSkin;
		SpriteTexturePtr mWindowBgTex;

		static const CM::String DefaultFontPath;
		static const UINT32 DefaultFontSize;

		static const CM::String WindowFramePrimaryTexture;
		static const CM::String WindowBackgroundTexture;

		static const CM::String ButtonNormalTex;
		static const CM::String ButtonHoverTex;
	};
}
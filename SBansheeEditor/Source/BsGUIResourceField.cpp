#include "BsGUIResourceField.h"
#include "BsGUIArea.h"
#include "BsGUILayout.h"
#include "BsGUILabel.h"
#include "BsGUIDropButton.h"
#include "BsGUIButton.h"
#include "BsBuiltinResources.h"
#include "BsGUIWidget.h"
#include "BsGUIMouseEvent.h"
#include "BsGUIResourceTreeView.h"
#include "BsGUIWidget.h"
#include "BsGameObjectManager.h"
#include "BsRuntimeScriptObjects.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsResources.h"
#include "BsProjectLibrary.h"
#include "BsProjectResourceMeta.h"
#include "BsManagedResourceMetaData.h"
#include "BsEditorGUI.h"

using namespace std::placeholders;

namespace BansheeEngine
{
	const UINT32 GUIResourceField::DEFAULT_LABEL_WIDTH = 100;

	GUIResourceField::GUIResourceField(const PrivatelyConstruct& dummy, const String& typeNamespace, const String& type, const GUIContent& labelContent, UINT32 labelWidth,
		const String& style, const GUILayoutOptions& layoutOptions, bool withLabel)
		:GUIElementContainer(layoutOptions, style), mLabel(nullptr), mClearButton(nullptr), mDropButton(nullptr), mType(type), mNamespace(typeNamespace)
	{
		mLayout = &addLayoutXInternal(this);

		if (withLabel)
		{
			mLabel = GUILabel::create(labelContent, GUIOptions(GUIOption::fixedWidth(labelWidth)), getSubStyleName(EditorGUI::ObjectFieldLabelStyleName));
			mLayout->addElement(mLabel);
		}

		mDropButton = GUIDropButton::create((UINT32)DragAndDropType::Resources, GUIOptions(GUIOption::flexibleWidth()), getSubStyleName(EditorGUI::ObjectFieldDropBtnStyleName));
		mClearButton = GUIButton::create(HString(L""), getSubStyleName(EditorGUI::ObjectFieldClearBtnStyleName));
		mClearButton->onClick.connect(std::bind(&GUIResourceField::onClearButtonClicked, this));

		mLayout->addElement(mDropButton);
		mLayout->addElement(mClearButton);

		mDropButton->onDataDropped.connect(std::bind(&GUIResourceField::dataDropped, this, _1));
	}

	GUIResourceField::~GUIResourceField()
	{

	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const GUIContent& labelContent, UINT32 labelWidth, const GUIOptions& layoutOptions,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, labelContent, labelWidth, *curStyle,
			GUILayoutOptions::create(layoutOptions), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const GUIContent& labelContent, const GUIOptions& layoutOptions,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, labelContent, DEFAULT_LABEL_WIDTH, *curStyle,
			GUILayoutOptions::create(layoutOptions), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const HString& labelText, UINT32 labelWidth, const GUIOptions& layoutOptions,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, GUIContent(labelText), labelWidth, *curStyle,
			GUILayoutOptions::create(layoutOptions), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const HString& labelText, const GUIOptions& layoutOptions,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, GUIContent(labelText), DEFAULT_LABEL_WIDTH, *curStyle,
			GUILayoutOptions::create(layoutOptions), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const GUIOptions& layoutOptions, const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, GUIContent(), 0, *curStyle,
			GUILayoutOptions::create(layoutOptions), false);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const GUIContent& labelContent, UINT32 labelWidth,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, labelContent, labelWidth, *curStyle,
			GUILayoutOptions::create(), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const GUIContent& labelContent,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, labelContent, DEFAULT_LABEL_WIDTH, *curStyle,
			GUILayoutOptions::create(), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const HString& labelText, UINT32 labelWidth,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, GUIContent(labelText), labelWidth, *curStyle,
			GUILayoutOptions::create(), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const HString& labelText,
		const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, GUIContent(labelText), DEFAULT_LABEL_WIDTH, *curStyle,
			GUILayoutOptions::create(), true);
	}

	GUIResourceField* GUIResourceField::create(const String& typeNamespace, const String& type, const String& style)
	{
		const String* curStyle = &style;
		if (*curStyle == StringUtil::BLANK)
			curStyle = &EditorGUI::ObjectFieldStyleName;

		return bs_new<GUIResourceField>(PrivatelyConstruct(), typeNamespace, type, GUIContent(), 0, *curStyle,
			GUILayoutOptions::create(), false);
	}

	HResource GUIResourceField::getValue() const
	{
		return Resources::instance().loadFromUUID(mUUID);
	}

	void GUIResourceField::setValue(const HResource& value)
	{
		if (value)
			setUUID(value.getUUID());
		else
			setUUID("");
	}

	void GUIResourceField::setUUID(const String& uuid)
	{ 
		mUUID = uuid;

		Path filePath;
		if (Resources::instance().getFilePathFromUUID(mUUID, filePath))
		{
			WString title = filePath.getWFilename(false) + L" (" + toWString(mType) + L")";
			mDropButton->setContent(GUIContent(HString(title)));
		}
		else
			mDropButton->setContent(GUIContent(HString(L"None (" + toWString(mType) + L")")));

		onValueChanged(mUUID);
	}

	void GUIResourceField::_updateLayoutInternal(INT32 x, INT32 y, UINT32 width, UINT32 height,
		RectI clipRect, UINT8 widgetDepth, UINT16 areaDepth)
	{
		mLayout->_updateLayoutInternal(x, y, width, height, clipRect, widgetDepth, areaDepth);
	}

	Vector2I GUIResourceField::_getOptimalSize() const
	{
		return mLayout->_getOptimalSize();
	}

	void GUIResourceField::dataDropped(void* data)
	{
		DraggedResources* draggedResources = reinterpret_cast<DraggedResources*>(data);
		UINT32 numResources = (UINT32)draggedResources->resourceUUIDs.size();

		if (numResources <= 0)
			return;

		MonoClass* acceptedClass = MonoManager::instance().findClass(mNamespace, mType);

		for (UINT32 i = 0; i < numResources; i++)
		{
			String uuid = draggedResources->resourceUUIDs[i];

			ProjectResourceMetaPtr meta = ProjectLibrary::instance().findResourceMeta(uuid);
			if (meta == nullptr)
				continue;

			bool found = false;
			UINT32 typeId = meta->getTypeID();
			switch (typeId)
			{
			case TID_Texture:
			{
				if (RuntimeScriptObjects::instance().getTextureClass()->isSubClassOf(acceptedClass))
				{
					setUUID(uuid);
					found = true;
				}
			}
				break;
			case TID_SpriteTexture:
			{
				if (RuntimeScriptObjects::instance().getSpriteTextureClass()->isSubClassOf(acceptedClass))
				{
					setUUID(uuid);
					found = true;
				}
			}
				break;
			case TID_ManagedResource:
			{
				ManagedResourceMetaDataPtr managedResMetaData = std::static_pointer_cast<ManagedResourceMetaData>(meta->getResourceMetaData());
				MonoClass* providedClass = MonoManager::instance().findClass(managedResMetaData->typeNamespace, managedResMetaData->typeName);

				if (providedClass->isSubClassOf(acceptedClass))
				{
					setUUID(uuid);
					found = true;
				}
			}
				break;
			default:
				BS_EXCEPT(NotImplementedException, "Unsupported resource type added to resource field.");
			}

			if (found)
				break;
		}
	}

	void GUIResourceField::styleUpdated()
	{
		if (mLabel != nullptr)
			mLabel->setStyle(getSubStyleName(EditorGUI::ObjectFieldLabelStyleName));

		mDropButton->setStyle(getSubStyleName(EditorGUI::ObjectFieldDropBtnStyleName));
		mClearButton->setStyle(getSubStyleName(EditorGUI::ObjectFieldClearBtnStyleName));
	}

	void GUIResourceField::onClearButtonClicked()
	{
		setValue(HResource());
	}

	const String& GUIResourceField::getGUITypeName()
	{
		static String typeName = "GUIResourceField";
		return typeName;
	}
}
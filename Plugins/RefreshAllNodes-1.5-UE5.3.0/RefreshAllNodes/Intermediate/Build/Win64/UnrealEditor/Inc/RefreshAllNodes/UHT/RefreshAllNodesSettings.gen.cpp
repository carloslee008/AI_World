// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RefreshAllNodes/Private/RefreshAllNodesSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRefreshAllNodesSettings() {}
// Cross Module References
	DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
	REFRESHALLNODES_API UClass* Z_Construct_UClass_URefreshAllNodesSettings();
	REFRESHALLNODES_API UClass* Z_Construct_UClass_URefreshAllNodesSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_RefreshAllNodes();
// End Cross Module References
	void URefreshAllNodesSettings::StaticRegisterNativesURefreshAllNodesSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URefreshAllNodesSettings);
	UClass* Z_Construct_UClass_URefreshAllNodesSettings_NoRegister()
	{
		return URefreshAllNodesSettings::StaticClass();
	}
	struct Z_Construct_UClass_URefreshAllNodesSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCompileBlueprints_MetaData[];
#endif
		static void NewProp_bCompileBlueprints_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCompileBlueprints;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRefreshLevelBlueprints_MetaData[];
#endif
		static void NewProp_bRefreshLevelBlueprints_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRefreshLevelBlueprints;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRefreshGameBlueprints_MetaData[];
#endif
		static void NewProp_bRefreshGameBlueprints_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRefreshGameBlueprints;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRefreshEngineBlueprints_MetaData[];
#endif
		static void NewProp_bRefreshEngineBlueprints_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRefreshEngineBlueprints;
		static const UECodeGen_Private::FNamePropertyParams NewProp_AdditionalBlueprintPaths_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AdditionalBlueprintPaths_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_AdditionalBlueprintPaths;
		static const UECodeGen_Private::FNamePropertyParams NewProp_ExcludeBlueprintPaths_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExcludeBlueprintPaths_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ExcludeBlueprintPaths;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URefreshAllNodesSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
		(UObject* (*)())Z_Construct_UPackage__Script_RefreshAllNodes,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Configure the Refresh All Nodes plugin\n */" },
#endif
		{ "IncludePath", "RefreshAllNodesSettings.h" },
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Configure the Refresh All Nodes plugin" },
#endif
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints_MetaData[] = {
		{ "Category", "Behavior" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Determines whether blueprints should be compiled after being refreshed.\n\x09\x09  * Enabling compilation will allow the plugin to catch errors in the blueprints,\n\x09\x09  * but it will take more time to process.\n\x09\x09  */" },
#endif
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Determines whether blueprints should be compiled after being refreshed.\nEnabling compilation will allow the plugin to catch errors in the blueprints,\nbut it will take more time to process." },
#endif
	};
#endif
	void Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints_SetBit(void* Obj)
	{
		((URefreshAllNodesSettings*)Obj)->bCompileBlueprints = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints = { "bCompileBlueprints", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URefreshAllNodesSettings), &Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints_MetaData), Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints_MetaData[] = {
		{ "Category", "Search" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Should the plugin refresh level blueprints? */" },
#endif
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Should the plugin refresh level blueprints?" },
#endif
	};
#endif
	void Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints_SetBit(void* Obj)
	{
		((URefreshAllNodesSettings*)Obj)->bRefreshLevelBlueprints = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints = { "bRefreshLevelBlueprints", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URefreshAllNodesSettings), &Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints_MetaData), Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints_MetaData[] = {
		{ "Category", "Search" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Should the plugin refresh blueprints in this project's game content folder? */" },
#endif
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Should the plugin refresh blueprints in this project's game content folder?" },
#endif
	};
#endif
	void Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints_SetBit(void* Obj)
	{
		((URefreshAllNodesSettings*)Obj)->bRefreshGameBlueprints = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints = { "bRefreshGameBlueprints", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URefreshAllNodesSettings), &Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints_MetaData), Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints_MetaData[] = {
		{ "Category", "Search" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Should the plugin refresh blueprints in the engine's content folder? */" },
#endif
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Should the plugin refresh blueprints in the engine's content folder?" },
#endif
	};
#endif
	void Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints_SetBit(void* Obj)
	{
		((URefreshAllNodesSettings*)Obj)->bRefreshEngineBlueprints = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints = { "bRefreshEngineBlueprints", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URefreshAllNodesSettings), &Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints_MetaData), Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints_MetaData) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths_Inner = { "AdditionalBlueprintPaths", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths_MetaData[] = {
		{ "Category", "Search" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09\x09 * Additional paths to search in for blueprints to refresh, good for plugins\n\x09\x09 * Example: Add \"Paper2D\" to not search the Paper2D plugin for blueprints to refresh.\n\x09\x09 */" },
#endif
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Additional paths to search in for blueprints to refresh, good for plugins\nExample: Add \"Paper2D\" to not search the Paper2D plugin for blueprints to refresh." },
#endif
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths = { "AdditionalBlueprintPaths", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URefreshAllNodesSettings, AdditionalBlueprintPaths), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths_MetaData), Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths_MetaData) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths_Inner = { "ExcludeBlueprintPaths", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths_MetaData[] = {
		{ "Category", "Search" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09\x09 * Blueprint paths to not search in for blueprints to refresh, good for\n\x09\x09 * blueprints with little dependencies that take lots of resources to\n\x09\x09 * load. Example: Add \"/Game/Marketplace\" to not search the \"Marketplace\"\n\x09\x09 * directory in the Content folder.\n\x09\x09 */" },
#endif
		{ "ModuleRelativePath", "Private/RefreshAllNodesSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint paths to not search in for blueprints to refresh, good for\nblueprints with little dependencies that take lots of resources to\nload. Example: Add \"/Game/Marketplace\" to not search the \"Marketplace\"\ndirectory in the Content folder." },
#endif
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths = { "ExcludeBlueprintPaths", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URefreshAllNodesSettings, ExcludeBlueprintPaths), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths_MetaData), Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URefreshAllNodesSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bCompileBlueprints,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshLevelBlueprints,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshGameBlueprints,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_bRefreshEngineBlueprints,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_AdditionalBlueprintPaths,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URefreshAllNodesSettings_Statics::NewProp_ExcludeBlueprintPaths,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URefreshAllNodesSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URefreshAllNodesSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_URefreshAllNodesSettings_Statics::ClassParams = {
		&URefreshAllNodesSettings::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_URefreshAllNodesSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::PropPointers),
		0,
		0x000000A6u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_URefreshAllNodesSettings_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URefreshAllNodesSettings_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_URefreshAllNodesSettings()
	{
		if (!Z_Registration_Info_UClass_URefreshAllNodesSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URefreshAllNodesSettings.OuterSingleton, Z_Construct_UClass_URefreshAllNodesSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_URefreshAllNodesSettings.OuterSingleton;
	}
	template<> REFRESHALLNODES_API UClass* StaticClass<URefreshAllNodesSettings>()
	{
		return URefreshAllNodesSettings::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(URefreshAllNodesSettings);
	URefreshAllNodesSettings::~URefreshAllNodesSettings() {}
	struct Z_CompiledInDeferFile_FID_Unreal_Projects_AI_World_Plugins_RefreshAllNodes_1_5_UE5_3_0_RefreshAllNodes_Source_RefreshAllNodes_Private_RefreshAllNodesSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_AI_World_Plugins_RefreshAllNodes_1_5_UE5_3_0_RefreshAllNodes_Source_RefreshAllNodes_Private_RefreshAllNodesSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_URefreshAllNodesSettings, URefreshAllNodesSettings::StaticClass, TEXT("URefreshAllNodesSettings"), &Z_Registration_Info_UClass_URefreshAllNodesSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URefreshAllNodesSettings), 3545987502U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_AI_World_Plugins_RefreshAllNodes_1_5_UE5_3_0_RefreshAllNodes_Source_RefreshAllNodes_Private_RefreshAllNodesSettings_h_4088206658(TEXT("/Script/RefreshAllNodes"),
		Z_CompiledInDeferFile_FID_Unreal_Projects_AI_World_Plugins_RefreshAllNodes_1_5_UE5_3_0_RefreshAllNodes_Source_RefreshAllNodes_Private_RefreshAllNodesSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_AI_World_Plugins_RefreshAllNodes_1_5_UE5_3_0_RefreshAllNodes_Source_RefreshAllNodes_Private_RefreshAllNodesSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS

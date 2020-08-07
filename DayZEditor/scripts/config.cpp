
class CfgPatches
{
	class Editor_Scripts
	{
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Scripts"};
	};
};

class CfgMods 
{
	class DZ_Editor
	{
		dir = "DayZEditor";
		credits = "InclementDab";
		creditsJson = "DayZEditor/Scripts/Data/Credits.json";
		versionPath = "DayZEditor/scripts/Data/Version.hpp";
		type = "mod";
		dependencies[] =
		{
			"Game", "World", "Mission"
		};
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"DayZEditor/gui/imagesets/dayz_editor_gui.imageset"
				};
			};
			class engineScriptModule
			{
				value = "";
				files[] =
				{
					"DayZEditor/scripts/common",
					"DayZEditor/scripts/1_core"
				};
			};

			class gameScriptModule
			{
				value="";
				files[] = 
				{
					"DayZEditor/scripts/common",
					"DayZEditor/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[] = 
				{
					"DayZEditor/scripts/common",
					"DayZEditor/scripts/4_World"
				};
			};

			class missionScriptModule 
			{
				value="";
				files[] = 
				{
					"DayZEditor/scripts/common",
					"DayZEditor/scripts/5_Mission"
				};
			};
		};
	};
};
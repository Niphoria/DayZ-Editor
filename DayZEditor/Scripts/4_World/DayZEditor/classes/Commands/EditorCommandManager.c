class EditorCommandManager
{
	ref map<int, EditorCommand> CommandShortcutMap = new map<int, EditorCommand>();
	
	// Editor Commands
	ref EditorNewCommand NewCommand;
	ref EditorOpenCommand OpenCommand;
	ref EditorSaveCommand SaveCommand;
	ref EditorSaveAsCommand SaveAsCommand;
	ref EditorCloseCommand CloseCommand;
	ref EditorExitCommand ExitCommand;
	ref EditorEscapeCommand EscapeCommand;
	
	ref EditorUndoCommand UndoCommand;
	ref EditorRedoCommand RedoCommand;
	ref EditorSelectAllCommand SelectAllCommand;
	ref EditorDeleteCommand DeleteCommand;
	
	ref EditorCutCommand CutCommand;
	ref EditorCopyCommand CopyCommand;
	ref EditorPasteCommand PasteCommand;
	
	ref EditorMagnetCommand MagnetCommand;
	ref EditorGroundCommand GroundCommand;
	ref EditorSnapCommand SnapCommand;
	ref EditorCollisionCommand CollisionCommand;
	
	ref EditorEnvironmentControlCommand EnvironmentControlCommand;
	ref EditorPreferencesCommand PreferencesCommand;
	ref EditorCameraControlsCommand CameraControlsCommand;
	ref EditorReloadHudCommand ReloadHudCommand;
	ref EditorReloadBrushesCommand ReloadBrushesCommand;
	ref EditorLootEditorCommand LootEditorCommand;
	ref EditorAddToFavoritesCommand AddToFavoritesCommand;
	
	ref EditorPlaceObjectCommand PlaceObjectCommand;
	
	ref EditorBrushPropertiesCommand BrushPropertiesCommand;
	ref EditorBrushToggleCommand BrushToggleCommand;	
	ref EditorBrushDensityCommand BrushDensityCommand;
	ref EditorBrushRadiusCommand BrushRadiusCommand;
	
	ref EditorObjectPropertiesCommand ObjectPropertiesCommand;
	ref EditorShowCommand ShowCommand;
	ref EditorHideCommand HideCommand;
	ref EditorLockCommand LockCommand;
	ref EditorUnlockCommand UnlockCommand;
	
	ref EditorExportToInitFile ExportToInitFile;
	ref EditorExportToExpansion ExportToExpansion;
	ref EditorExportToTerrainBuilder ExportToTerrainBuilder;
	ref EditorExportToVPP ExportToVPP;
	ref EditorExportToCOM ExportToCOM;
	
	ref EditorImportFromInit ImportFromInitFile;
	ref EditorImportFromExpansion ImportFromExpansionCommand;
	ref EditorImportFromTerrainBuilder ImportFromTerrainBuilderCommand;
	ref EditorImportFromVPP ImportFromVPPCommand;
	ref EditorImportFromCOM ImportFromCOM;
	
	ref EditorScriptEditorCommand ScriptEditorCommand;
	
	ref EditorJoinDiscordCommand JoinDiscordCommand;
	ref EditorOpenWikiCommand OpenWikiCommand;
	
	ref EditorDonateCommand DonateCommand;
	ref EditorHelpCommand HelpCommand;
	ref EditorSpawnGroup1 SpawnGroup1;
	ref EditorSpawnGroup2 SpawnGroup2;
	ref EditorSpawnGroup3 SpawnGroup3;
	ref EditorSpawnGroup4 SpawnGroup4;
	
	
	void EditorCommandManager()
	{			
		for (int i = 0; i < Type().GetVariableCount(); i++) {
			string variable_name = Type().GetVariableName(i);
			typename variable_type = Type().GetVariableType(i);
			if (variable_type.IsInherited(EditorCommand)) {
				EditorCommand command = variable_type.Spawn();
				EnScript.SetClassVar(this, variable_name, 0, command);
				if (command.GetShortcut()) {
					CommandShortcutMap.Insert(command.GetShortcut().GetMask(), command);
				}
			}
		}
	}
	
	void ~EditorCommandManager()
	{
		for (int i = 0; i < Type().GetVariableCount(); i++) {
			string variable_name = Type().GetVariableName(i);
			typename variable_type = Type().GetVariableType(i);
			if (variable_type.IsInherited(EditorCommand)) {
				EditorCommand command;
				EnScript.GetClassVar(this, variable_name, 0, command);
				delete command;
			}
		}
	}
}
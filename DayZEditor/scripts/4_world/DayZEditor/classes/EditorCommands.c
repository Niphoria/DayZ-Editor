
class EditorCommand: RelayCommand
{	
	protected Editor m_Editor = GetEditor();
	
	void Call();
	
	override void Execute(RelayCommandArgs args) {
		EditorLog.Trace("EditorCommand::Execute");
		super.Execute(args);
		Call();
	}
	
	string GetName();
	string GetIcon();
	string GetKeys();
}

class EditorNewCommand: EditorCommand
{
	override void Call() {
		m_Editor.New();
	}
		
	override string GetName() {
		return "New";
	}
	
	override string GetKeys() {
		return "Ctrl + N";
	}
}

class EditorSaveCommand: EditorCommand
{
	override void Call() {
		EditorWorldData world_data(m_Editor);
		m_Editor.Save(m_Editor.GetSaveFile(), world_data);
	}
		
	override string GetName() {
		return "Save";
	}

	override string GetKeys() {
		return "Ctrl + S";
	}
}

class EditorSaveAsCommand: EditorCommand
{
	override void Call() {	
		EditorFileSaveDialog save_dialog = new EditorFileSaveDialog(new EditorWorldData(m_Editor));
		string file = save_dialog.ShowFileDialog();
	}
		
	override string GetName() {
		return "Save As...";
	}
	
	override string GetKeys() {
		return "Ctrl + Shift + S";
	}
}

class EditorOpenCommand: EditorCommand
{
	override void Call() {
		m_Editor.Open();
	}
			
	override string GetName() {
		return "Open";
	}
		
	override string GetIcon() {
		return "dayz_editor_gui:building_icon";
	}
	
	override string GetKeys() {
		return "Ctrl + O";
	}
}

class EditorUndoCommand: EditorCommand
{
	override void Call() {
		m_Editor.GetObjectManager().Undo();
	}
	
	override string GetName() {
		return "Undo";
	}
	
	override string GetKeys() {
		return "Ctrl + Z";
	}
}

class EditorRedoCommand: EditorCommand
{
	override void Call() {
		m_Editor.GetObjectManager().Redo();
	}
		
	override string GetName() {
		return "Redo";
	}
	
	override string GetKeys() {
		return "Ctrl + Y";
	}
}

class EditorSelectAllCommand: EditorCommand
{
	override void Call() {
		EditorObjectSet placed_objects = m_Editor.GetPlacedObjects();
		foreach (EditorObject eo: placed_objects)
			m_Editor.SelectObject(eo);
	}
		
	override string GetName() {
		return "Select All...";
	}
	
	override string GetKeys() {
		return "Ctrl + A";
	}
}

class EditorDeleteCommand: EditorCommand
{
	override void Call() {
		m_Editor.GetObjectManager().DeleteObjects(m_Editor.GetSelectedObjects());
	}
		
	override string GetName() {
		return "Delete";
	}
	
	override string GetKeys() {
		return "Delete";
	}
}

class EditorExportCommand: EditorCommand
{
	override void Call() {
		m_Editor.Export();
	}

	override string GetName() {
		return "Export";
	}
	
	override string GetKeys() {
		return "Ctrl + E";
	}
}

class EditorImportCommand: EditorCommand
{
	override void Call() {
		m_Editor.Import();
	}

	override string GetName() {
		return "Import";
	}
	
	override string GetKeys() {
		return "Ctrl + I";
	}
}

class EditorCutCommand: EditorCommand
{
	override void Call() {
		m_Editor.Cut(m_Editor.GetSelectedObjects());
	}

	override string GetName() {
		return "Cut";
	}
	
	override string GetKeys() {
		return "Ctrl + X";
	}
}

class EditorCopyCommand: EditorCommand
{
	override void Call() {
		m_Editor.Copy(m_Editor.GetSelectedObjects());
	}

	override string GetName() {
		return "Copy";
	}
	
	override string GetKeys() {
		return "Ctrl + C";
	}
}

class EditorPasteCommand: EditorCommand
{
	override void Call() {
		m_Editor.Paste(m_Editor.CurrentMousePosition);
	}

	override string GetName() {
		return "Paste";
	}
	
	override string GetKeys() {
		return "Ctrl + V";
	}
}
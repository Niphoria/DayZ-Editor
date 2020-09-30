class GroupPrefab: PrefabBase<ref ObservableCollection<ref ScriptedViewBase>>
{
	ref ObservableCollection<ref ScriptedViewBase> collection_ref;
	
	protected WrapSpacerWidget EditorDialogOptionContent;
	
	void GroupPrefab(Widget parent = null, string caption = "", Controller binding_context = null, string binding_name = "")
	{
		collection_ref = new ObservableCollection<ref ScriptedViewBase>("Value", m_PrefabBaseController);
		m_PrefabBaseController.Value = collection_ref;
	}
	
	void Insert(ScriptedViewBase content)
	{
		m_PrefabBaseController.Value.Insert(content);
	}
	
	bool GroupCollapseExecute(ButtonCommandArgs args)
	{
		EditorDialogOptionContent.Show(!args.GetButtonState()); 
		return true;		
	}
	
	override void PrefabPropertyChanged(string property_name)
	{
	}
	
	override string GetLayoutFile() {
		return "DayZEditor/gui/Layouts/dialogs/prefabs/GroupPrefab.layout";
	}
}
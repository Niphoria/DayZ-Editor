
// Inherit this class, then put that class into ScriptClass for your View Model Widget
class ViewModel: Managed
{
	// Just stored for debug
	protected Widget m_LayoutRoot;
	
	// Hashed Variable Data
	protected ref map<string, typename> m_ModelHashMap;
	
	// View List
	protected ref map<string, ref EditorView> m_ViewList;
	
	void ViewModel() { EditorLog.Trace("ViewModel"); }
	void ~ViewModel() { EditorLog.Trace("~ViewModel"); }
	
	void OnWidgetScriptInit(Widget w)
	{
		EditorLog.Trace("ViewModel::OnWidgetScriptInit");	
		m_LayoutRoot = w;
		
		m_ModelHashMap = new map<string, typename>();
		m_ViewList = new map<string, ref EditorView>();

		typename vtype = Type();
		int vcnt = vtype.GetVariableCount();
		for (int i = 0; i < vcnt; i++)
			m_ModelHashMap.Insert(vtype.GetVariableName(i), vtype.GetVariableType(i));		
		
		
		NotifyOnPropertyChanged(OnPropertyChanged);
		NotifyOnCollectionChanged(OnCollectionChanged);
	}
	
	void InsertView(ref EditorView view)
	{
		string variable_name = view.GetVariableName();
		EditorLog.Trace("ViewModel::InsertView: " + variable_name);
		
		if (m_ViewList.Get(variable_name) != null) {
			EditorLog.Trace("View Found! Setting");
			m_ViewList.Set(variable_name, view);
		} else {
			m_ViewList.Insert(variable_name, view);
		}
		
	}
	
	
	void OnPropertyChanged(string property_name)
	{
		//EditorLog.Trace(string.Format("ViewModel::NotifyPropertyChanged: %1", property_name));
		
		EditorView view = m_ViewList.Get(property_name);
		if (view == null) {
			Error(string.Format("Invalid Property Name: %1 - View not found", property_name));
			return;
		}
		
		view.OnPropertyChanged();
	}
	
	
	void OnCollectionChanged(string property_name, CollectionChangedEventArgs args)
	{
		EditorLog.Trace(string.Format("ViewModel::OnCollectionChanged: %1", property_name));
		EditorView view = m_ViewList.Get(property_name);
		if (view == null) {
			//Error(string.Format("Invalid Collection Name: %1 - View not found", property_name));
			m_ViewList.Insert(property_name, null);
			return;
		}
		
		view.OnCollectionChanged(args);
	}

	
	ref map<string, typename> GetVariableHashMap() { return m_ModelHashMap; }
	typename GetVariableType(string var_name) { return m_ModelHashMap.Get(var_name); }
	
	bool OnClick(Widget w, int x, int y, bool button) { return true; }
	
	void DebugPrint()
	{
		EditorLog.Debug("ViewModel::DebugPrint: " + m_LayoutRoot.GetName());
		foreach (string name, ref EditorView view: m_ViewList)
			view.DebugPrint();
	}
}

// property_name = name of variable being changed
ref ScriptInvoker PropertyChanged;
void NotifyPropertyChanged(string property_name)
{
	PropertyChanged.Invoke(property_name);
}


void NotifyOnPropertyChanged(func action)
{	
	if (PropertyChanged == null)
		PropertyChanged = new ScriptInvoker();
	
	PropertyChanged.Insert(action);
}


// Called only when Collection is changed
// Use NotifyOnPropertyChanged to 'subscribe' to the Invoke
ref ScriptInvoker CollectionChanged;
void NotifyOnCollectionChanged(func action)
{
	if (CollectionChanged == null)
		CollectionChanged = new ScriptInvoker();
	
	CollectionChanged.Insert(action);
}
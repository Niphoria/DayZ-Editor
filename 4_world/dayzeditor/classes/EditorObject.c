class EditorObject: Managed
{
	Object WorldObject = null;
	ref EditorObjectMarker ObjectMarker = null;
	
	protected EntityAI m_BBoxLines[12];	
	protected EntityAI m_BBoxBase;
	
	bool IsSelected = false;
	
	void EditorObject(notnull Object world_object) 
	{
		WorldObject = world_object;
	}
	
	void ~EditorObject()
	{
		Print("~EditorObject");
		delete ObjectMarker;
		GetGame().ObjectDelete(WorldObject);

	}
	
	
	void OnSelected()
	{
		Print("EditorObject::OnSelected");
		IsSelected = true;
		ShowBoundingBox();
		if (ObjectMarker != null)
			ObjectMarker.Select();
	}
	
	void OnDeselected()
	{
		Print("EditorObject::OnDeselected");
		IsSelected = false;
		HideBoundingBox();
		if (ObjectMarker != null)
			ObjectMarker.Deselect();
	}
	
	
	void OnPlaced(vector position, vector orientation) 
	{
		Print("EditorObject::OnObjectPlaced");
		
		Widget editor_object_display = GetGame().GetWorkspace().CreateWidgets(layout_dir + "EditorObjectMarker.layout");
		editor_object_display.GetScript(ObjectMarker);
		if (ObjectMarker != null)
			ObjectMarker.SetObject(this);
	}
	
	void SetPosition(vector position)
	{
		WorldObject.SetPosition(position);
	}
	
	vector GetPosition()
	{
		return WorldObject.GetPosition();
	}
	
	vector GetOrientation()
	{
		return WorldObject.GetOrientation();
	}
	
	void SetOrientation(vector orientation)
	{
		WorldObject.SetOrientation(orientation);
	}
	
	bool OnDrag(Widget w, int x, int y)
	{
		GetGame().GetUpdateQueue(CALL_CATEGORY_GUI).Insert(DragUpdate);
		return true;
	}
	
	bool OnDrop(Widget w, int x, int y, Widget receiver)
	{
		GetGame().GetUpdateQueue(CALL_CATEGORY_GUI).Remove(DragUpdate);
		return true;
	}

	vector previous_direction = vector.Zero; /// store this outside the method! TODO: find a better way obvs
	
	void DragUpdate()
	{		
		vector object_position = WorldObject.GetPosition();
		vector size = GetObjectSize(WorldObject);
		set<Object> obj;
		vector cursor_projection = MousePosToRay(obj, WorldObject);
		Input input = GetGame().GetInput();
		
		
		// Handle Z only motion
		if (input.LocalValue("UALookAround")) {	
			float dist = vector.Distance(GetGame().GetCurrentCameraPosition(), object_position);
			cursor_projection = MousePosToRay(obj, WorldObject, dist);			
			foreach (EditorObject editor_positionup_object: Editor.SelectedObjects) {
				vector v3 = { object_position[0], cursor_projection[1] + size[1]/2, object_position[2] };
				editor_positionup_object.WorldObject.SetPosition(v3);
				editor_positionup_object.WorldObject.Update();
			}
			
		// Handle XY Plane Rotation
			// needs to be updated to use transformations
		} else if (input.LocalValue("UATurbo")) {
			
			

			// vector previous_direction = vector.Zero; /// store this outside the method! TODO: find a better way obvs
			
			/*vector center_up_axis = WorldObject.GetTransformAxis(1);
			
			vector direction = vector.Direction(object_position, cursor_projection);
			direction[1] = 0;

			  
			
			foreach (EditorObject editor_rotate_object: Editor.SelectedObjects) {
			    	
					float ang = direction.VectorToYaw();
					
					vector new_pos = vector.RotateAroundPoint(WorldObject.GetPosition(), editor_rotate_object.GetPosition(), WorldObject.GetTransformAxis(1), Math.Cos(ang), Math.Sin(ang));
					editor_rotate_object.WorldObject.SetPosition(new_pos);
			    }
			
			    editor_rotate_object.WorldObject.Update();
			
			
			previous_direction = direction;*/
			
			vector direction = vector.Direction(object_position, cursor_projection);
			direction[1] = 0;
			
			array< vector > positions = new array< vector >();
			
			foreach (EditorObject editor_rotate_object: Editor.SelectedObjects) {
			    if ( editor_rotate_object.WorldObject == WorldObject )
			        continue;
			
			    positions.Insert(WorldObject.WorldToModel(editor_rotate_object.WorldObject.GetPosition()));
			}
			
			WorldObject.SetDirection(direction);
			
			int index = 0;
			foreach (EditorObject editor_rotate_object1: Editor.SelectedObjects) {
			    if ( editor_rotate_object1.WorldObject == WorldObject )
			        continue;
			
			    editor_rotate_object1.WorldObject.SetPosition(WorldObject.ModelToWorld(positions[index]));
			    editor_rotate_object1.WorldObject.SetDirection(direction);
			    index++;
			}
			
			
		} else {
			
			cursor_projection[1] = cursor_projection[1] + size[1]/2;			
			
			foreach (EditorObject editor_position_object: Editor.SelectedObjects) { 
				vector pos_delta = editor_position_object.WorldObject.GetPosition() - object_position;
				editor_position_object.WorldObject.SetPosition(cursor_projection + pos_delta); 
				editor_position_object.WorldObject.Update();
			}
		}
	}
	
	void ShowBoundingBox()
	{
		Print("BoundingBox");
		vector line_centers[12]; vector line_verticies[8];
		vector clip_info[2];
		float radius = WorldObject.ClippingInfo(clip_info); // idk do something cool w/ radius		
		vector position = AverageVectors(clip_info[0], clip_info[1]);
		
		line_verticies[0] = clip_info[0];
		line_verticies[1] = Vector(clip_info[0][0], clip_info[0][1], clip_info[1][2]);
		line_verticies[2] = Vector(clip_info[1][0], clip_info[0][1], clip_info[1][2]);
		line_verticies[3] = Vector(clip_info[1][0], clip_info[0][1], clip_info[0][2]);		
		line_verticies[4] = Vector(clip_info[1][0], clip_info[1][1], clip_info[0][2]);
		line_verticies[5] = clip_info[1];		
		line_verticies[6] = Vector(clip_info[0][0], clip_info[1][1], clip_info[1][2]);
		line_verticies[7] = Vector(clip_info[0][0], clip_info[1][1], clip_info[0][2]);
		
		line_centers[0] = AverageVectors(line_verticies[0], line_verticies[1]);
		line_centers[1] = AverageVectors(line_verticies[1], line_verticies[2]);
		line_centers[2] = AverageVectors(line_verticies[2], line_verticies[3]);
		line_centers[3] = AverageVectors(line_verticies[3], line_verticies[4]);
		line_centers[4] = AverageVectors(line_verticies[4], line_verticies[5]);
		line_centers[5] = AverageVectors(line_verticies[5], line_verticies[6]);
		line_centers[6] = AverageVectors(line_verticies[6], line_verticies[7]);
		line_centers[7] = AverageVectors(line_verticies[0], line_verticies[3]);
		line_centers[8] = AverageVectors(line_verticies[7], line_verticies[4]);
		line_centers[9] = AverageVectors(line_verticies[2], line_verticies[5]);
		line_centers[10] = AverageVectors(line_verticies[1], line_verticies[6]);
		line_centers[11] = AverageVectors(line_verticies[0], line_verticies[7]);
				
	
		float line_width = 0.1;
		for (int i = 0; i < 12; i++) {
			
			vector size = GetObjectSize(WorldObject);
			vector transform[4];			
			transform[3] = line_centers[i];
			
			for (int j = 0; j < 3; j++) {
				transform[j][j] = ((position[j] == line_centers[i][j])*size[j]/2) + line_width;
			}
						
			 
			m_BBoxLines[i] = GetGame().CreateObjectEx("BoundingBoxBase", line_centers[i], ECE_NONE);
			m_BBoxLines[i].SetTransform(transform);
		
			WorldObject.AddChild(m_BBoxLines[i], -1);
			
		}
		
		//m_BBoxBase = GetGame().CreateObjectEx("BoundingBoxBase", vector.Zero, ECE_NONE);
		
		WorldObject.Update();
	}
	
	void HideBoundingBox()
	{
		for (int i = 0; i < 12; i++) {
			GetGame().ObjectDelete(m_BBoxLines[i]);
			m_BBoxLines[i].Update();
		}	
	}

	
	
}
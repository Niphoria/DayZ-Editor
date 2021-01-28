class EditorLootSpawn
{
	//ref array<ref EditorLootSpawnGroup> m_EditorLootSpawn = {};
	
	ref array<EditorObject> m_LootGroup1 = {};
	ref array<EditorObject> m_LootGroup2 = {};
	ref array<EditorObject> m_LootGroup3 = {};
	ref array<EditorObject> m_LootGroup4 = {};
	
	array<EditorObject> GetLootSpawnsG1() 
	{
		return m_LootGroup1;
	}
	array<EditorObject> GetLootSpawnsG2() 
	{
		return m_LootGroup2;
	}
	array<EditorObject> GetLootSpawnsG3() 
	{
		return m_LootGroup3;
	}
	array<EditorObject> GetLootSpawnsG4() 
	{
		return m_LootGroup4;
	}
	
	void InsertLootPointG1(EditorLootPoint loot_point)
	{
		EditorLog.Info("Inserting Loot Point %1", loot_point.GetPosition().ToString());
		vector loot_pos = loot_point.GetPosition();	
		EditorObject loot_display = GetEditor().CreateObject(EditorObjectData.Create("GiftBox_Small_1", loot_pos, vector.Zero, 1, EditorObjectFlags.OBJECTMARKER));

		// might be bad
		//m_Building.AddChild(loot_display.GetWorldObject(), -1);
				
		vector transform[4] = {
			Vector(1, 0, 0),
			Vector(0, 1, 0),
			Vector(0, 0, 1),
			loot_pos
		};
		
		transform[0][0] = loot_point.GetRange();
		transform[1][1] = loot_point.GetHeight();
		transform[2][2] = loot_point.GetRange();
		
		loot_display.SetTransform(transform);
		m_LootGroup1.Insert(loot_display);
		
		//m_Building.Update();
	}
	
	void InsertLootPointG2(EditorLootPoint loot_point)
	{
		EditorLog.Info("Inserting Loot Point %1", loot_point.GetPosition().ToString());
		vector loot_pos = loot_point.GetPosition();	
		EditorObject loot_display = GetEditor().CreateObject(EditorObjectData.Create("GiftBox_Small_2", loot_pos, vector.Zero, 1, EditorObjectFlags.OBJECTMARKER));

		// might be bad
		//m_Building.AddChild(loot_display.GetWorldObject(), -1);
				
		vector transform[4] = {
			Vector(1, 0, 0),
			Vector(0, 1, 0),
			Vector(0, 0, 1),
			loot_pos
		};
		
		transform[0][0] = loot_point.GetRange();
		transform[1][1] = loot_point.GetHeight();
		transform[2][2] = loot_point.GetRange();
		
		loot_display.SetTransform(transform);
		m_LootGroup2.Insert(loot_display);
		
		//m_Building.Update();
	}
	
	void InsertLootPointG3(EditorLootPoint loot_point)
	{
		EditorLog.Info("Inserting Loot Point %1", loot_point.GetPosition().ToString());
		vector loot_pos = loot_point.GetPosition();	
		EditorObject loot_display = GetEditor().CreateObject(EditorObjectData.Create("GiftBox_Small_3", loot_pos, vector.Zero, 1, EditorObjectFlags.OBJECTMARKER));

		// might be bad
		//m_Building.AddChild(loot_display.GetWorldObject(), -1);
				
		vector transform[4] = {
			Vector(1, 0, 0),
			Vector(0, 1, 0),
			Vector(0, 0, 1),
			loot_pos
		};
		
		transform[0][0] = loot_point.GetRange();
		transform[1][1] = loot_point.GetHeight();
		transform[2][2] = loot_point.GetRange();
		
		loot_display.SetTransform(transform);
		m_LootGroup3.Insert(loot_display);
		
		//m_Building.Update();
	}
	
	void InsertLootPointG4(EditorLootPoint loot_point)
	{
		EditorLog.Info("Inserting Loot Point %1", loot_point.GetPosition().ToString());
		vector loot_pos = loot_point.GetPosition();	
		EditorObject loot_display = GetEditor().CreateObject(EditorObjectData.Create("GiftBox_Small_4", loot_pos, vector.Zero, 1, EditorObjectFlags.OBJECTMARKER));

		// might be bad
		//m_Building.AddChild(loot_display.GetWorldObject(), -1);
				
		vector transform[4] = {
			Vector(1, 0, 0),
			Vector(0, 1, 0),
			Vector(0, 0, 1),
			loot_pos
		};
		
		transform[0][0] = loot_point.GetRange();
		transform[1][1] = loot_point.GetHeight();
		transform[2][2] = loot_point.GetRange();
		
		loot_display.SetTransform(transform);
		m_LootGroup4.Insert(loot_display);
		
		//m_Building.Update();
	}

}
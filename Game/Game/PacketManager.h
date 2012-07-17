class PacketsManager
{
public:
	enum Packets{NONE,HP_PACKET,MP_PACKET,AM_PACKET};
	vector<HealthPacket> HPpackets;
	vector<ManaPacket> MPpackets;
	vector<AmmoPacket> AMpackets;
	void DropPacket(Vector3 Pos)
	{
		int x = rand()%4;
		Pos.y = -20;
		HealthPacket HP(Pos,5);
		ManaPacket MP(Pos,5);
		AmmoPacket AM(Pos,5);
		switch(x)
		{
		case NONE:
			break;
		case HP_PACKET:		
			HPpackets.push_back(HP);
			break;
		case MP_PACKET:
			MPpackets.push_back(MP);
			break;
		case AM_PACKET:
			AMpackets.push_back(AM);
			break;
		}
	}
	void UpdatePackets(Hero &hero,Particle &P)
	{
		int numPac = HPpackets.size();
		for(int i = 0 ; i < numPac ; i++)
		{
			if(HPpackets[i].isTaken)
				continue;
			HPpackets[i].Update();
			if(HPpackets[i].GetAABB().IntersectsWith(hero.GetAABB()))
			{	
				HPpackets[i].isTaken = true;
				hero.HP += HPpackets[i].Value;
				hero.ValidateHP();
				hero.HealthPointDecreased = ((0.48-0.02)/100)*(100-hero.HP);
				P.StartAgain('g');
			}
		}
		numPac = MPpackets.size();
		for(int i = 0 ; i < numPac ; i++)
		{
			if(MPpackets[i].isTaken)
				continue;
			MPpackets[i].Update();
			if(MPpackets[i].GetAABB().IntersectsWith(hero.GetAABB()))
			{	
				MPpackets[i].isTaken = true;
				hero.MP += MPpackets[i].Value;
				hero.ValidateMP();
				hero.ManaPointDecreased = ((0.48-0.02)/100)*(100-hero.MP);
				P.StartAgain('b');
			}
		}
		//not complete
		numPac = AMpackets.size();
		for(int i = 0 ; i < numPac ; i++)
		{
			if(AMpackets[i].isTaken)
				continue;
			AMpackets[i].Update();
			if(AMpackets[i].GetAABB().IntersectsWith(hero.GetAABB()))
			{
				AMpackets[i].isTaken = true;
				P.StartAgain('y');
			}
		}
	}
};
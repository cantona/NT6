// qishang-quan

inherit SKILL;

mapping *action = ({
    ([  "action":"$N左手握拳護胸，右手使出一招「烘雲托月」，穿出擊向$n的$l",
        "lian"  :"$N左手握拳護胸，右手使出一招「烘雲托月」，慢慢體會其中韻味。",
        "zhaoshi":"「烘雲托月」",
        "jibie" : 5,
        "sen" : 5,
        "damage" : 5,
        "damage_type":  "瘀傷"
    ]),
    ([  "action":"$N右手虛晃，使出一招「虛敲實應」，左掌化虛為實擊向$n的$l",
        "lian"  :"$N右手虛晃，使出一招「虛敲實應」，左掌化虛為實，緩緩擊出。",
        "zhaoshi" : "「虛敲實應」",
        "jibie" : 10,
        "sen"  : 10,
        "damage" : 10,
        "damage_type":  "瘀傷"
    ]),
    ([  "action":"$N使出七傷拳法「行雲流水」，弓步上前，雙掌同時拍向$n的$l",
        "lian" : "$N使出七傷拳法「行雲流水」，弓步向前，雙掌向空中一拍。",
        "zhaoshi" : "「行雲流水」",
        "jibie" : 20,
        "sen" : 15,
        "damage" : 15,
        "damage_type":  "瘀傷"
    ]),
    ([  "action":"$N使出一招「大落墨」，身形騰空躍起，對準$n的$l連續拍出三掌",
        "lian"  :"$N使出一招「大落墨」，身形騰空躍起，對著空氣亂拍一通。",
        "zhaoshi" : "「大落墨」",
        "jibie" : 30,
        "sen" : 20,
        "damage" : 20,
        "damage_type":  "瘀傷"
    ]),
    ([  "action":"$N左掌揚起，右掌五指一伸一劃，一招「倒卷簾」擊向$n的$l",
        "lian"  :"$N左掌揚起，右掌五指一伸一劃，使出一招「倒卷簾」，好象在捏蒼蠅。",
        "zhaoshi" : "「倒卷簾」",
        "jibie" : 35,
        "sen" : 30,
        "damage" : 30,
        "damage_type":  "瘀傷"
    ]),
    ([  "action":"$N身形飛舞，一招「哨探尋」，雙掌同時向$n的$l出掌攻擊",
        "lian" : "$N身形飛舞，使出一招「哨探尋」，雙掌一出即回，虎虎生風。",
        "zhaoshi" : "「哨探尋」",
        "jibie" : 40,
        "sen" : 40,
        "damage" : 50,
        "damage_type":  "瘀傷"
    ]),
    ([  "action":"$N大喝一聲，一招「連山斷嶺」，掌力傾吐，掌風罩向$n全身",
        "lian" : "$N大喝一聲，一招「連山斷嶺」，掌力傾吐，化出一陣掌風，足以開碑裂石。",
        "zhaoshi" : "「連山斷嶺」",
        "jibie" : 50,
        "sen" : 50,
        "damage" : 60,
        "damage_type":  "瘀傷"
    ]),
});

string *parry_msg = ({
    "$n雙手輕點，一招「撥雲見日」，輕而易舉的擋開了$N的一擊。\n",
    "只見$n足不點地，一招「順水推舟」，將$N的攻勢化于無形。\n",
    "但見$n不退反進，雙手一揚，使出一招「葉底摘花」，立刻化險為夷。\n",
});
    
int valid_lian(object me)
{   
    if (me->query_temp("weapon"))
        return notify_fail("練七傷拳必須空手。\n");
    if ( me->query("str") < 18 )
        return notify_fail("你體質太弱，無法練七傷拳。\n");
    if ( me->query("force") < 5 )
        return notify_fail("你內力不足，一練便有生命危險。\n");
    me->receive_damage("kee",5);
    me->add("force",-5);
    return 1;
}

int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
            return notify_fail("師父說道：“你先把手中兵器放下。”\n");
    if ( (int)me->query("max_force") < 100 )
            return notify_fail("你的內力太弱，練七傷拳會走火入魔。\n");
    return 1;
}

mapping query_action(int jibie)
{ 	
    int i, size;
	size = sizeof( action );
	for ( i = 0; i < sizeof( action ); i++ )
		if ( action[ i ][ "jibie" ] > jibie )
		{
			size = i;
			break;
		}
    return action[ random( size ) ];
}

string query_parry_msg(object weapon)
{   
    return parry_msg[random(sizeof(parry_msg))];
}

string perform_action_file(string action)
{   
    return SKILL_D("qishang-quan/") + action;
}

string query_xiuwei_type() { return "unarmed"; }

int query_dengji() { return 5; }

string query_zhaoshi( int jibie )
{
    int i;
    for ( i = 0; i < sizeof(action); i++ )
    {
        if ( action[ i ][ "jibie" ] >= jibie )
            return action[ i ][ "zhaoshi" ];
    }
    return "";
}

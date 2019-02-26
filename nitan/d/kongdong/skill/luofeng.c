// 落風六式    luofeng.c
//   created by qyz on Feb 4, 1997

inherit SKILL;

mapping *action = ({
        ([     
                "action":               
"只見$n身隨意轉，一招「浮雲無定」，倏地往一旁挪開了三尺，避過了$N這一招。",
                "lian" :
"$N身隨意轉，一招「浮雲無定」，倏地往一旁挪開了三尺。",
                "jibie":          8,
                "sen"  :      5,
                "dodge":                0,
                "parry":                0,
                "damage":                15,
                "damage_type":  "瘀傷"
        ]),
        ([      "action":
"$n使出一招「輕舟泛月」，向一旁飄然縱出，輕輕着地。",
                "lian" :
"$N使出一招「輕舟泛月」，向一旁飄然縱出，輕輕着地。",
                "jibie":15,
                "sen"  :5,
                "dodge":                0,
                "parry":                0,
                "damage":                20,
                "damage_type":  "瘀傷"
        ]),
        ([      
                "action":               
"$n身形微晃，一招「落日浮雲」，有驚無險地避開了$N這一招。",
                "lian" :
"$N身形微晃，一招「落日浮雲」，向一邊閃去。",
                "jibie":25,
                "sen"  : 5,
                "dodge":                0,
                "parry":                0,
                "damage":                15,
                "damage_type":  "瘀傷"
        ]),
        ([    
                "action":               
"$n漫不經心的向左一個「日落沙明」，剛好避過$N的凌厲攻勢。",
                "lian" :
"$N漫不經心的向左一個「日落沙明」飄了過去。",
                "jibie":33,
                "sen"  : 5,
                "dodge":                0,
                "parry":                0,
                "damage":                20,
                "damage_type":  "瘀傷"
        ]),
        ([      
                "action":               
"$n身形向後一縱，使出一招「落葉秋風」，避過了$N的攻擊。",
                "lian" :
"$N身形向後一縱，使出一招「落葉秋風」，退後丈餘。",
                "jibie":40,
                "sen"  : 6,
                "dodge":                0,
                "parry":         0,
                "damage":                15,
                "damage_type":  "瘀傷"
        ]),
        ([      
                "action":               
"可是$n使一招「風飄落日」，身子輕輕飄了開去。",
                "lian" :
"$N使一招「風飄落日」，身子輕輕向後飄了開去。",
                "jibie":50,
                "sen"  : 6,
                "dodge":                0,
                "parry":         0,
                "damage":                15,
                "damage_type":  "瘀傷"
        ]),
});
/*
string *parry_msg = ({
        "$n一招「盤古開天」，提腿立足，雙掌變爪，架開了$N。\n",
        "$n右拳全力擊出，迫使$N不得不收招自衞。\n",
        "$n架開了$N的攻勢。\n",
});
*/
int valid_learn(object me)
{
    return 1;
}

int valid_lian( object me )
{
//        int encu;
//        encu=me->query_encumbrance() * 100 / me->query_max_encumbrance();
//        if( encu < 10 )
//        return notify_fail("輕功必須負重練習。\n");

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

string query_xiuwei_type()
{
	return "dodge";
}

// 返回這路武功的等級, 第十等返回0, 第一等返回9.
int query_dengji()
{
	return 3;
}
/*
string query_parry_msg(object weapon)
{   
    if(!weapon)
        return parry_msg[random(sizeof(parry_msg))];
}
*/
int effective_level(){  return 10; }

string *query_lian()
{
	string *lian_msg;
	mapping lian_act;

	lian_msg = allocate( sizeof( action ) );
	for ( int i = 0; i < sizeof( action ); i++ )
	{
		lian_act = action[ i ];
		lian_msg[ i ] = (string)lian_act[ "lian" ];
	}
	return lian_msg;
}


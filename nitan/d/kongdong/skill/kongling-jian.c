// kongling-jian.c
//  空靈劍法
inherit SKILL;

mapping *action = ({
    ([  "action":"$N一招「匪神之靈」，高舉手中$w，向$n迎頭一劈",
        "lian"  :"$N一招「匪神之靈」，手中$w凌空一劈。",
        "sen"   :3,
        "jibie" :5,
        "dodge" :20,
        "parry" :30,
        "zhaoshi":"「匪神之靈」",
        "damage":20,
        "damage_type":"割傷"    ]),
    ([  "action":"$N反手一招「匪機之微」，手中$w向$n的$l一抹",
        "lian"  :"$N手握$w，使出一招「匪機之微」向前順勢一抹。",
        "sen"   :10,
        "jibie" :10,
        "dodge" :10,
        "parry" :0,
        "zhaoshi":"「匪機之微」",
        "damage":40,
        "damage_type":"割傷" ]),
    ([  "action":"只見$N弓步上前，雙手緊握$w，一招「亂山喬木」，向$n的頭部由下而上一撩",
        "lian"  :"$N一個弓步，使出一招「亂山喬木」，手中$w往上一撩。",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"「亂山喬木」",
        "damage":50,
        "damage_type":"割傷"    ]),
    ([  "action":"$N手拿$w，一招「碧苔芳暉」，向$n的$l飛速一擊",
        "lian"  :"$N手拿$w，一招「碧苔芳暉」，快速擊出。",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"「碧苔芳暉」",
        "damage":60,
        "damage_type":"割傷"    ]),
	([	"action":
"$N使出「清風與歸」，$w連揮劍光霍霍斬向$n的$l",
                "lian" :
"$N使出「清風與歸」，$w連揮，只見劍光霍霍，煞是驚人......",
                "zhaoshi":"「清風與歸」",
                "jibie":20,
                "sen" :12,
		"dodge":		30    ,
		"damage":		30,
		"damage_type":	"割傷"
	]),
	([	"action":
"$N一招「誦之思之」，縱身飄開數尺，手中$w斬向$n的$l",
                "lian":
"$N一招「誦之思之」，縱身飄開數尺，手中$w大開大闕，揮洒飄逸......",
                "jiebie":30,
                "zhaoshi":"「誦之思之」",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"割傷"
	]),
	([	"action":
"$N縱身一躍，手中$w一招「終與俗違」，對準$n的氣海斜斜刺出一劍",
                "lian" :
"$N縱身一躍，手中$w一招「終與俗違」，斜斜地向右下方刺去......",
                "jibie":50,
                "zhaoshi":"「終與俗違」",
                "sen"  :13,
		"dodge":40,
                "limb":"小腹",
                "damage":80,
		"damage_type":	"刺傷",
	]),
});

string *parry_msg = ({
        "$n使出一招「如將白雲」，手中的$v化做漫天雪影，封住了全身。。\n",
        "$n使出「反手」訣，身形拔起，$w反手刺出，登時瓦解了$N的攻勢。。\n",
        "$n使出一招「脫帽看詩」，手中的$v飄忽不定，照出點點劍花，晃得$N睜不開眼睛。。\n",
        "$n手中的$v一抖，一招「但知旦暮」，向$N的左肩反削上去。\n",
});

string *unarmed_parry_msg = ({
        "$n使出一招「如將白雲」，封住了$N的攻勢。\n",
        "$n反手一招「脫帽看詩」，整個人化做一團幻影。\n",
        "$n使出一招「但知旦暮」，化掌為劍，拍向$N左肩。。\n",
        "$n雙掌一揮，內力逼出，迫得$N連連後退。\n",
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("你的內力不夠，沒有辦法練空靈劍法。\n");
	return 1;
}

int valid_lian( object me )
{
	object weapon;

	weapon = me->query_temp( "weapon" );
    if ( !weapon || weapon->query("weapon_type") != "sword" )
        return notify_fail("你必須先找一把劍才能練習劍法。\n");

	return 1;
}
string query_xiuwei_type() { return "sword";}      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 3; } //1~~ 10

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
    if ( weapon )
        return parry_msg[random(sizeof(parry_msg))];
    else
        return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

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

int query_youxiao_jibie() { return 12;}

int query_parry_ratio() { return 12; }

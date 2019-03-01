// liuyun-jian.c
// 	nerd     Dec 9,1996 create

inherit SKILL;

mapping	* action=({
	([	"action":
        "$N使一招「仙人拱手」，手中$w幻一條疾光刺向$n的$l",
        "lian" :
        "$N使一招「仙人拱手」，手中$w幻一條疾光刺向左前方......",
                "jibie":7,
                "zhaoshi":"「仙人拱手」",
                "sen"  :8  ,
		"dodge":		20  ,
		"damage":		40   ,
		"damage_type":	"刺傷"
	]),
	([	"action":
        "$N一招「日月輝煌」，縱身飄開數尺，手中$w斬向$n的$l",
                "lian":
        "$N一招「日月輝煌」，縱身飄開數尺，手中$w大開大闕，揮洒飄逸......",
                "jiebie":30,
                "zhaoshi":"「日月輝煌」",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"割傷"
	]),
	([	"action":
        "$N手中$w中宮直進，一式「白蛇吐信」對準$n的肩井穴刺出一劍",
                "lian":
        "$N手中$w中宮直進，一式「白蛇吐信」對準左前方斜刺一劍......",
                "jibie":40,
                "limb":"肩頭",
                "zhaoshi":"白蛇吐信",
                "sen": 12,
		"dodge":30 ,
                "damage":50,
		"damage_type":	"刺傷"
	]),
	([	"action":
        "$N的$w憑空一指，一招「金針指南」，$w跳動著刺向$n的頸部.......",
                "lian":
        "$N的$w憑空一指，一招「金針指南」，$w跳動著刺向上方.......",
                "jibie":62,
                "zhaoshi":"「金針指南」",
                "sen": 10,
                "limb":"頸部",
		"dodge":		20,
		"damage":		70,
		"damage_type":	"刺傷"
	]),
    ([  "action":"$N左手捏了個劍訣，右手一招「二郎擔山」，手中$w對準$n一點",
        "lian"  :"$N左手捏了個劍訣，右手一招「二郎擔山」，手中$w輕輕一點。",
        "sen"   :4,
        "jibie" :20,
        "dodge" :40,
        "parry" :30,
        "zhaoshi":"「二郎擔山」",
        "damage":5,
        "damage_type":"刺傷"    ]),
    ([  "action":"只見$N弓步上前，雙手緊握$w，一招「鳳凰展翼」，向$n的頭部由下而上一撩",
        "lian"  :"$N一個弓步，使出一招「鳳凰展翼」，手中$w往上一撩。",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"「鳳凰展翼」",
        "damage":50,
        "damage_type":"割傷"    ]),
    ([  "action":"$N手拿$w，一招「猛虎擺尾」，向$n的$l飛速一擊",
        "lian"  :"$N手拿$w，一招「猛虎擺尾」，快速擊出。",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"「猛虎擺尾」",
        "damage":60,
        "damage_type":"割傷"    ]),
});

string *parry_msg = ({
    "$n使出一招「順風掃葉」，手中的$v化作一條長虹，磕開了$N的$w。\n",
    "$n使出一招「左右提爐」，手中的$v化做漫天雪影，盪開了$N的$w。\n",
    "$n手中的$v一抖，一招「雲雀飛空」，向$N拿$w的手腕削去。\n",
    "$n使出一招「跪跳撲虎」，$w直刺$N的雙手。\n",
});

string *unarmed_parry_msg = ({
    "$n雙手舞得密不透風，使出「順風掃葉」，封住了$N的攻勢。\n",
    "$n反手一招「左右提爐　梗□蕓□□N的這一招。\n",
    "$n使出一招「雲雀飛空」，架住了$N的攻勢。\n",
    "但見$n一招「跪跳撲虎」，迫得$N連連後退。\n",
});

int valid_learn(object me)
{
    return 1;
}

int valid_lian( object me )
{   
    object ob = me->query_temp("weapon");
    if ( !ob || (string)ob->query("weapon_type") != "sword" )
    {   
        write("你必須先找一把劍才能練劍法。\n");
        return 0;
    }
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
    if ( weapon )
        return parry_msg[random(sizeof(parry_msg))];
    else
        return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_xiuwei_type() { return "sword"; }      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 2; }

int query_youxiao_jibie() { return 9; }

int query_parry_ratio() { return 12; }

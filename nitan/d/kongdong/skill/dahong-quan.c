// dahong.c
// 大洪拳

inherit SKILL;

mapping *action = ({
([	"action"    :"$N雙掌一錯，使出「十指點兵」，對準$n的$l連續拍出三掌",
    "lian"      :"$N雙掌一錯，使出「十指點兵」，結果左手把右手打得生疼",
    "jibie"     :16,      
    "zhaoshi":"「十指點兵」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N使出一招「守將接印」，腳踩七星步，一拳向$n$l擊去",
    "lian"      :"$N慢慢使出一招「守將接印」，仔細揣摩每一個變化",
    "jibie"     :48,
    "zhaoshi":"「守將接印」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N使出一招「武鬆上銬」，左掌虛按，右拳下擊，直奔$n的$l而去",
    "lian"      :"$N左掌虛按，右拳下擊，體會「武鬆上銬」的感覺..",
    "jibie"     :56,  
    "zhaoshi":"「武鬆上銬」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N使出「推窗望月」，大步跨前，立右拳，挽左拳向$n的$l擊去",
    "lian"      :"$N大步跨前，立右拳，挽左拳，尋找「推窗望月」的感覺",
    "jibie"     :64, 
    "zhaoshi":"「推窗望月」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :30,
	"damage_type":	"瘀傷"
]),
    ([   "action"  :"$N使出一招「烏風進洞」，左掌直立，右掌穿出擊向$n的$l",
         "lian"    :"$N使出一招「烏風進洞」，左掌直立，右掌向前擊出。",
         "zhaoshi" : "「烏風進洞」",
         "sen"   : 6,
         "parry" : 20,
         "dodge" : 15,
         "jibie" : 0,
         "damage": 5,
         "damage_type":  "瘀傷"
    ]),
    ([   "action"  :"$N一招「烏風掃地」，左掌化虛為實擊向$n的$l",
         "lian"    :"$N一招「烏風掃地」，左掌虛虛實實擊出。",
         "zhaoshi" : "「烏風掃地」",
         "damage" : 20,
         "sen"    : 8,
         "parry"  : 20,
         "dodge"  : 20,
         "jibie"  : 5,   
         "damage_type":  "瘀傷"
    ]),
    ([   "action": "$N雙掌一錯，使出「鷹爪捉食」，身形飛起，對準$n的$l連續拍出",
         "lian"  :"$N雙掌一錯，使出「鷹爪捉食」，身形飛起數尺。",
         "zhaoshi" : "「鷹爪捉食」",
         "damage":  20,
         "sen"  :  8,
         "parry" : 60,
         "dodge" : 60,
         "jibie":    20,
         "damage_type":  "瘀傷"
    ]),
    ([   "action": "$N左掌上揚，右掌推出，一招「繞手躲步」擊向$n$l",
         "lian"  : "$N左掌上揚，右掌推出，一招「繞手躲步」快速拍出。",
         "zhaoshi" : "「繞手躲步」",
         "sen"  : 6,
         "jibie": 30,
         "parry" : 50,
         "dodge" : 40,
         "damage": 60,
         "damage_type":  "瘀傷"
    ]),
});

string * parry_msg = ({
    "$n一招「雙撲心」，雙掌翻舞，$N眼前一花，失去了$n的蹤影。\n",
    "$n兩手握拳，一招「單撲心」，格開了$N的一擊。\n",
    "但見$n一招「犀牛獻角」，跟上一步，化開了$N的攻勢。\n",
});
    
int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    {    
        write("練拳必須空手。\n");
        return 0;
    }
    return 1;
}

int valid_lian( object me )
{   
    return valid_learn(me);
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

string query_xiuwei_type() { return "unarmed"; }

int query_dengji() { return 3; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }

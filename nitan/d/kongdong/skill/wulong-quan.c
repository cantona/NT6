// wulong-quan.c
// 烏龍拳

inherit SKILL;

mapping *action = ({
([	"action"    :"$N坐馬拉弓，擊出一拳，正是一招烏龍拳中的「烏龍出水」",
    "lian"      :"$N坐馬拉弓，擊出一招「烏龍出水」，卻總覺得有些不得要領",
    "jibie"     :8,
    "zhaoshi":"「烏龍出水」",
    "sen"       :1,
	"dodge"     :0,
    "parry"     :0,
    "damage"     :10,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N雙掌一錯，使出「烏龍奪珠」，對準$n的$l連續拍出三掌",
    "lian"      :"$N雙掌一錯，使出「烏龍奪珠」，連續拍出三掌，結果左手把右手打得生疼",
    "jibie"     :16,      
    "zhaoshi":"「烏龍奪珠」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N吐氣揚聲，一招「烏龍吸水」，雙手奔$n的頭頸搶去",
    "lian"      :"$N一招「烏龍吸水」，雙手向假象中的敵人的頭頸搶去",
    "jibie"     :24,
    "zhaoshi":"「烏龍吸水」",
    "limb":"頭頸",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N一招「烏龍翻雲」,起手向$n$l拍去...",
    "lian"      :"$N一招「烏龍翻雲」，起手向前拍去...",
    "jibie"     :32,    
    "zhaoshi":"「烏龍翻雲」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :10,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N左掌一翻，右掌推出，一招「烏龍翻江」擊向$n$l",
    "lian"      :"$N右掌慢慢推出，左掌一翻，配合右掌的變化，來了個「烏龍翻江」..",
    "jibie"     :40,
    "zhaoshi":"「烏龍翻江」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :25,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N使出一招「烏龍擺尾」，腳踩七星步，一拳向$n$l擊去",
    "lian"      :"$N慢慢使出一招「烏龍擺尾」，仔細揣摩每一個變化",
    "jibie"     :48,
    "zhaoshi":"「烏龍擺尾」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀傷"
]),
([	"action"    :"$N使出一招「烏龍入洞」，左掌虛按，右拳下擊，直奔$n的$l而去",
    "lian"      :"$N左掌虛按，右拳下擊，體會「烏龍入洞」的氣勢",
    "jibie"     :56,  
    "zhaoshi":"「烏龍入洞」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"瘀傷"
]),
});

string * parry_msg = ({
    "$n一招「烏龍翻雲」，雙掌翻舞，$N眼前一花，失去了$n的蹤影。\n",
    "$n兩手握拳，一招「烏龍擺尾」，格開了$N的一擊。\n",
    "但見$n一招「烏龍絞柱」，身子一個翻滾，化開了$N的攻勢。\n",
});
    
int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    {    
        write("練烏龍拳必須空手。\n");
        return 0;
    }
    if ( me->query("max_force") < 300 )
    {   
        write("你的內力太弱，無法練烏龍拳。\n");
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

int query_dengji() { return 4; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }

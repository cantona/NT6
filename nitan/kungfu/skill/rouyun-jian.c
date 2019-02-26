#include <ansi.h>

inherit SKILL;

mapping *action = ({
([   "action" : "$N面露微笑，手中$w一抖，一招「杏花春雨」，劍光頓時暴長，灑向$n的$l",
     "force"  : 50,
     "attack" : 15,
     "dodge"  : 10,
     "parry"  : 25,
     "damage" : 10,
     "lvl"    : 0,
     "skill_name" : "杏花春雨",
     "damage_type":  "刺傷"
]),
([   "action" : "$N身形突閃，劍招陡變，手中$w從一個絕想不到的方位斜刺向$n的$l",
     "force"  : 70,
     "attack" : 25,
     "dodge"  : 25,
     "parry"  : 30,
     "damage" : 5,
     "lvl"    : 10,
     "skill_name" : "春雲乍展",
     "damage_type":  "刺傷"
]),
([   "action" : "$N暴退數尺，低首撫劍，隨後手中$w驟然穿上，正是一招「朝天一柱香」，刺向$n",
     "force"  : 75,
     "attack" : 33,
     "dodge"  : 22,
     "parry"  : 32,
     "damage" : 20,
     "lvl"    : 20,
     "skill_name" : "朝天一柱香",
     "damage_type":  "刺傷"
]),
([   "action" : "$N身形一晃，疾掠而上，一招「白雲蒼狗」，手中$w龍吟一聲，對準$n的$l連遞數劍",
     "force"  : 90,
     "attack" : 39,
     "dodge"  : 40,
     "parry"  : 35,
     "damage" : 25,
     "lvl"    : 30,
     "skill_name" : "白雲蒼狗",
     "damage_type":  "刺傷"
]),
([   "action" : "$N神色微變，一招「滿天花雨」，劍招頓時變得凌厲無比，手中$w如匹鏈般灑向$n的$l",
     "force"  : 180,
     "attack" : 71,
     "dodge"  : 30,
     "parry"  : 52,
     "damage" : 40,
     "lvl"    : 70,
     "skill_name" : "滿天花雨",
     "damage_type":  "刺傷"
]),
([   "action" : "$N緩緩低首，接着一招「秋風襲人」，手中$w中宮直進，迅捷無比地往$n的$l刺去",
     "force"  : 200,
     "attack" : 85,
     "dodge"  : 20,
     "parry"  : 54,
     "damage" : 35,
     "lvl"    : 80,
     "skill_name" : "秋風襲人",
     "damage_type":  "刺傷"
]),
([   "action" : "$N矮身側步，一招「寒月當空照」，手中$w反手疾挑而出，“唰”的一聲往$n的$l刺去",
     "force"  : 240,
     "attack" : 91,
     "dodge"  : 65,
     "parry"  : 65,
     "damage" : 58,
     "lvl"    : 100,
     "skill_name" : "寒月當空照",
     "damage_type":  "刺傷"
]),
([   "action" : "$N驀地疾退一步，又衝前三步，一招「辰星點綴」，手中$w化為一道弧光往$n的$l刺去",
     "force"  : 265,
     "attack" : 93,
     "dodge"  : 40,
     "parry"  : 68,
     "damage" : 72,
     "lvl"    : 110,
     "skill_name" : "辰星點綴",
     "damage_type":  "刺傷"
]),
([   "action" : "$N縱身躍起，一招「雲湧四方」，不見蹤影，接着卻又從半空中穿下，$w直逼$n的$l",
     "force"  : 290,
     "attack" : 97,
     "dodge"  : 60,
     "parry"  : 72,
     "damage" : 78,
     "lvl"    : 120,
     "skill_name" : "雲湧四方",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「銀河橫空」，手中$w遙指蒼空，猛然劃出一道劍芒，往$n的$l刺去",
     "force"  : 310,
     "attack" : 100,
     "dodge"  : 45,
     "parry"  : 75,
     "damage" : 86,
     "lvl"    : 130,
     "skill_name" : "銀河橫空",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「天外來雲」，左手虛擊，右手$w猛的自下方挑起，激起一股勁風反挑$n的$l",
     "force"  : 330,
     "attack" : 105,
     "dodge"  : 50,
     "parry"  : 82,
     "damage" : 95,
     "lvl"    : 140,
     "skill_name" : "天外來雲",
     "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本劍法火候不夠，無法學習柔雲劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("rouyun-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的柔雲劍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("rouyun-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練習柔雲劍法。\n");

        addn("qi", -50, me);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"rouyun-jian/" + action;
}
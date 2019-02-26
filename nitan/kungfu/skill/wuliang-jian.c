#include <ansi.h>

inherit SKILL;

mapping *action = ({
([   "action" : "$N面露微笑，手中$w一抖，一招「德無量」，劍光暴長，灑向$n的$l",
     "force"  : 50,
     "attack" : 15,
     "dodge"  : 10,
     "parry"  : 25,
     "damage" : 10,
     "lvl"    : 0,
     "skill_name" : "德無量",
     "damage_type":  "刺傷"
]),
([   "action" : "$N身形突閃，劍招陡變，一招「心無量」，手中$w從左位反刺$n的$l",
     "force"  : 70,
     "attack" : 25,
     "dodge"  : 25,
     "parry"  : 30,
     "damage" : 5,
     "lvl"    : 20,
     "skill_name" : "心無量",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「緣無量」，暴退數尺，低首撫劍，隨後手中$w驟然穿上，刺向$n的$l",
     "force"  : 75,
     "attack" : 33,
     "dodge"  : 22,
     "parry"  : 32,
     "damage" : 20,
     "lvl"    : 40,
     "skill_name" : "緣無量",
     "damage_type":  "刺傷"
]),
([   "action" : "$N身形一晃疾掠而上，手中$w龍吟一聲，一招「大海無量」，對準$n$l連遞數劍",
     "force"  : 90,
     "attack" : 39,
     "dodge"  : 40,
     "parry"  : 35,
     "damage" : 25,
     "lvl"    : 60,
     "skill_name" : "大海無量",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「天地無量」撲向$n，如影相隨，手中$w“錚”然有聲，往$n的$l刺去",
     "force"  : 100,
     "attack" : 43,
     "dodge"  : 60,
     "parry"  : 40,
     "damage" : 25,
     "lvl"    : 80,
     "skill_name" : "天地無量",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一個側身，一招「日月無量」，手中$w疾往斜上挑起，直指$n的$l",
     "force"  : 130,
     "attack" : 51,
     "dodge"  : 50,
     "parry"  : 45,
     "damage" : 30,
     "lvl"    : 100,
     "skill_name" : "日月無量",
     "damage_type":  "刺傷"
]),
([   "action" : "$N微微一個轉身，手中$w卻已自肋下穿出，一招「乾坤無量」，罩向$n的$l",
     "force"  : 150,
     "attack" : 62,
     "dodge"  : 40,
     "parry"  : 47,
     "damage" : 30,
     "lvl"    : 120,
     "skill_name" : "乾坤無量",
     "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 20)
                return notify_fail("你的基本劍法火候不夠，無法學習苗家劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wuliang-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的無量劍法。\n");

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
        level   = (int) me->query_skill("wuliang-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<30 )
                return notify_fail("你的體力不夠，無法練習無量劍法。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠，無法練習無量劍法。\n");
        
        addn("qi", -20, me);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuliang-jian/" + action;
}
int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) )
                return 0;
                
        if( query("skill_type", weapon) != "sword" )
                return 0;
                
        lvl = me->query_skill("wuliang-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
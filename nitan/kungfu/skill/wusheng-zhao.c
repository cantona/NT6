#include <ansi.h>
inherit SKILL;

mapping *action = ({
([     "action" : "$N左爪前伸，帶著絲絲藍陰鬼氣，一式「元神出竅」，猛得向$n的頂門插下",
       "force" : 150,
       "damage" : 30,
       "dodge" : 5,
       "lvl" : 0,
       "weapon" : "五指",
       "damage_type" : "抓傷"
]),
([     "action" : "$N雙掌連拍，築起一道氣牆推向$n，忽然一爪「鬼魅穿心」沖破氣牆直插$n的$l",
       "force" : 160,
       "dodge" : 10,
       "damage": 30,
       "lvl" : 0,
       "weapon" : "指尖",
       "damage_type" : "刺傷"
]),
([     "action" : "$N使出「血鬼鎖」雙爪遊向$n扣住$l，氣勁激發往左右兩下一拉，便要將$n割成碎片",
       "force" : 170,
       "dodge" : 0,
       "damage": 40,
       "lvl" : 20,
       "weapon" : "指甲",
       "damage_type" : "割傷"
]),
([     "action" : "$N雙爪攏住$n，使一式「煉獄鬼嚎」，陰毒內功隨爪尖透入$n體內，直襲各大關節",
       "force" : 180,
       "dodge" : 5,
       "damage": 60,
       "lvl" : 30,
       "damage_type" : "內傷"
]),
([     "action" : "$N力透指尖，向$n虛虛實實連抓十五爪，「妖風襲體」帶動無數陰氣纏住$n",
       "force" : 200,
       "dodge" : 15,
       "damage": 60,
       "weapon" : "陰風",
       "lvl" : 40,
       "damage_type" : "拉傷"
]),
([     "action" : "$N一式「索命妖手」，左爪上下翻動形成無數爪影，右臂一伸，鬼魅般抓向$n的$l",
       "force" : 240,
       "dodge" : 5,
       "damage": 67,
       "weapon" : "右抓",
       "lvl" : 50,
       "damage_type" : "抓傷"
]),
([     "action" : "$N探手上前，順著$n的手臂攀緣直上，變手為爪，一招「孤魂馭魔」抓向$n的$l",
       "force" : 260,
       "dodge" : 5,
       "damage": 70,
       "lvl"   : 70,
       "weapon": "五爪",
       "damage_type" : "抓傷"
]),
});

int valid_enable(string usage)
{
        return usage == "claw" ||  usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "tianchan-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
            return notify_fail("練五聖毒爪必須空手。\n");

        if( query("max_neili", me)<200 )
            return notify_fail("你的內力太弱，無法練五聖毒爪。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("wusheng-zhao", 1))
            return notify_fail("你的基本爪法水平有限，無法領會更高深的五聖毒爪。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("wusheng-zhao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 5, level/5)];

}

int practice_skill(object me)
{
        object* ob;
        int i,skill,damage;

        skill = me->query_skill("wusheng-zhao",1);
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練五聖毒爪。\n");

        me->receive_damage("qi", 30);
        addn("neili", -31, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wusheng-zhao/" + action;
}
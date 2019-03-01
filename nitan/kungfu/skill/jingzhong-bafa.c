//jingzhong-bafa 井中八法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N橫立不動，手中$w橫推，一招「不攻」，由上至下向$nl慢慢推去",
        "force"  : 232,
        "attack" : 157,
        "dodge"  : 123,
        "parry"  : 221,
        "damage" : 389,
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「沙鷗掠波」，刀鋒自下而上劃了個半弧，$w一提一收，平刃揮向$n的頸部",
        "force"  : 285,
        "attack" : 183,
        "dodge"  : 123,
        "parry"  : 221,
        "damage" : 421,
        "damage_type" : "割傷",
]),
([      "action" : "$N使出一招「天設牢籠」，將$w舞得如白霧一般壓向$n",
        "force"  : 297,
        "attack" : 179,
        "dodge"  : 123,
        "parry"  : 221,
        "damage" : 435,
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「閉門鐵扇」，$w緩緩的斜著向$n推去",
        "force"  : 334,
        "attack" : 191,
        "dodge"  : 123,
        "parry"  : 221,
        "damage" : 451,
        "damage_type" : "割傷",
]),
([      "action" : "$N手拖$w，轉身躍起，一招「翼德闖帳」，一道白光射向$n的胸口",
        "force"  : 382,
        "attack" : 207,
        "dodge"  : 121,
        "parry"  : 211,
        "damage" : 479,
        "damage_type" : "割傷",
]),
([      "action" : "$N揮舞$w，使出一招「白鶴舒翅」，上劈下撩，左擋右開，齊齊罩向$n",
        "force"  : 397,
        "attack" : 223,
        "dodge"  : 123,
        "parry"  : 221,
        "damage" : 483,
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「春風送暖」，左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "force"  : 421,
        "attack" : 257,
        "dodge"  : 133,
        "parry"  : 213,
        "damage" : 534,
        "damage_type" : "割傷",
]),
([      "action" : "$N驀的使一招「八方藏刀」，頓時劍光中無數朵刀花從四面八方湧向$n全身",
        "force"  : 423,
        "attack" : 271,
        "dodge"  : 173,
        "parry"  : 221,
        "damage" : 589,
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("character", me) != "狡黠多變" )
                return notify_fail("你心中暗想：哼，這種刀法沒半點章法，練來何用？\n");

        if( query("int", me)<36 )
                return notify_fail("你覺得井中八法過于艱深，難以理解。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武學修養沒有辦法理解井中八法的精神奧義。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力不足，沒有辦法練井中八法，多練些內力再來吧。\n");

        if ((int)me->query_skill("blade", 1) < 250)
                return notify_fail("你的基本刀法火候太淺，沒有辦法練井中八法。\n");

        if ((int)me->query_skill("force") < 350)
                return notify_fail("你的內功火候太淺，沒有辦法練井中八法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("jingzhong-bafa", 1))
                return notify_fail("你的基本刀法水平還不夠，無法領會更高深的井中八法。\n");

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
        level   = (int) me->query_skill("jingzhong-bafa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<500 )
                return notify_fail("你的體力不夠，練不了井中八法。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠，練不了井中八法。\n");

        me->receive_damage("qi", 300);
        addn("neili", -300, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jingzhong-bafa/" + action;
}

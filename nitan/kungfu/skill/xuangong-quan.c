#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「劃手」，雙手劃了個半圈，按向$n的$l",
        "force"  : 37,
        "dodge"  : 35,
        "parry"  : 38,
        "attack" : 5,
        "damage" : 1,
        "lvl" : 0,
        "skill_name"  : "劃手",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使一招「單鞭」，右手收置肋下，左手向外揮出，劈向$n的$l",
        "force"  : 48,
        "dodge"  : 51,
        "parry"  : 53,
        "attack" : 7,
        "damage" : 2,
        "lvl" : 10,
        "skill_name"  : "單鞭",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左手回收，右手由鉤變掌，由右向左，使一招「印掌」，向$n的$l打去",
        "force"  : 62,
        "dodge"  : 45,
        "parry"  : 57,
        "attack" : 9,
        "damage" : 3,
        "lvl" : 20,
        "skill_name"  : "印掌",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙手劃弧，右手向上，左手向下，使一招「拗鞭」，分擊$n的面門和$l",
        "force"  : 74,
        "dodge"  : 53,
        "parry"  : 62,
        "attack" : 11,
        "damage" : 5,
        "lvl" : 30,
        "skill_name"  : "拗鞭",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左手由胸前向下，身體微轉，劃了一個大圈，使一招「摔碑手」，擊向$n的$l",
        "force"  : 92,
        "dodge"  : 76,
        "parry"  : 88,
        "attack" : 15,
        "damage" : 8,
        "lvl" : 50,
        "skill_name"  : "摔碑手",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左手由下上挑，右手內合，使一招「撥雲見日」，向$n的$l打去",
        "force"  : 120,
        "dodge"  : 81,
        "parry"  : 97,
        "attack" : 19,
        "damage" : 11,
        "lvl" : 70,
        "skill_name"  : "撥雲見日",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左手變掌橫于胸前，右拳由肘下穿出，一招「七星拳」，錘向$n的$l",
        "force"  : 152,
        "dodge"  : 95,
        "parry"  : 108,
        "attack" : 21,
        "damage" : 14,
        "lvl" : 100,
        "skill_name"  : "七星拳",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左腳前踏半步，右手使一招「海底針」，指由下向$n的$l戳去",
        "force"  : 183,
        "dodge"  : 105,
        "parry"  : 113,
        "attack" : 31,
        "damage" : 17,
        "lvl" : 130,
        "skill_name"  : "海底針",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N招「倒騎龍」，左腳一個弓箭步，右手上舉向外撇出，向$n的$l揮去",
        "force"  : 212,
        "dodge"  : 115,
        "parry"  : 138,
        "attack" : 39,
        "damage" : 21,
        "lvl" : 160,
        "skill_name"  : "倒騎龍",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練無極玄功拳必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學無極玄功拳。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練無極玄功拳。\n");

        if ((int)me->query_skill("unarmed", 1) < 60)
                return notify_fail("你的基本拳腳火候不夠，無法學無極玄功拳。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("xuangong-quan", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的無極玄功拳。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuangong-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練無極玄功拳。\n");

        me->receive_damage("qi", 40);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xuangong-quan/" + action;
}
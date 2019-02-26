#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N縱步上前，手中$w斜斜刺出，竟似不要命一般，疾斬$n而去",
        "force" : 290,
        "attack": 171,
        "parry" : -240,
        "dodge" : -231,
        "damage": 260,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w猛的反身遞出，疾刺$n的$l，所施全為拼命的招數",
        "force" : 340,
        "attack": 152,
        "parry" : -241,
        "dodge" : -192,
        "damage": 232,
        "damage_type" : "刺傷"
]),
([      "action": "$N面不露色，身形陡然加快，手中$w一劍快過一劍，盡數向$n刺去",
        "force" : 320,
        "attack": 158,
        "parry" : -245,
        "dodge" : -183,
        "damage": 220,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中$w光芒閃爍，在許許劍芒中遞出殺着，完全出自$n意料之外",
        "force" : 390,
        "attack": 168,
        "parry" : -193,
        "dodge" : -175,
        "damage": 230,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，無法學習同歸劍法。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功火候不夠，無法學習同歸劍法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的劍法修為不足，無法學習同歸劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tonggui-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的同歸劍法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tonggui-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練同歸劍法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練同歸劍法。\n");

        me->receive_damage("qi", 40);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tonggui-jian/" + action;
}
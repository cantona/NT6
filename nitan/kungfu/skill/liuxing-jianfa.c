// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N冷哼一聲，劍法突然加快，如同流星劃破夜空一般，刺向$n的$l",
        "force" : 126,
        "parry" : -3,
        "dodge" : -5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "群星閃耀",
        "damage_type":  "刺傷"
]),
([      "action": "$N劍式突然變緩，劍身發出濃重的殺氣，刷地一下突然刺向$n的$l",
        "force" : 149,
        "parry" : -13,
        "dodge" : -10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "明星千裡",
        "damage_type":  "割傷"
]),
([      "action": "$N縱身躍起，手中$w化做流星，直刺向$n的$l",
        "force" : 167,
        "parry" : -12,
        "dodge" : -15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "懷中抱星",
        "damage_type":  "刺傷"
]),
([      "action": "$N冷笑一聲，劍法突然忽快忽慢，如同鬼魅一般刺向$n的$l",
        "force" : 187,
        "parry" : -23,
        "dodge" : -19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "星歸月象",
        "damage_type":  "割傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，不能學習流星劍法。\n");

        if (me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本劍法火候不夠，不能學習流星劍法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠，不能學習流星劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("liuxing-jianfa", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的流星劍法。\n");

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
        level = (int) me->query_skill("liuxing-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練流星劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練流星劍法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuxing-jianfa/" + action;
}

inherit SKILL;

mapping *action = ({
([      "action":"$N使一式「春暖花開」，手中$w由左至右橫掃向向$n的$l",
        "force" : 60,
        "attack": 5,
        "dodge" : 10,
        "damage": 33,
        "lvl" : 0,
        "damage_type":  "割傷"
]),
([      "action":"$N踏上一步，「夏日炎炎」，手中$w盤旋飛舞出一道劍光刺向$n的$l",
        "force" : 120,
        "attack": 15,
        "dodge" : 20,
        "damage": 51,
        "lvl" : 40,
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w一抖，一招「秋風蕭瑟」，斜斜一劍反腕撩出，攻向$n的$l",
        "force" : 150,
        "attack": 64,
        "dodge" : 25,
        "damage": 85,
        "lvl" : 80,
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w連繞數個大圈，一式「冬掣寒星」，一道劍光飛向$n的$l",
        "force" : 180,
        "attack": 95,
        "dodge" : 30,
        "damage": 125,
        "lvl" : 120,
        "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不到，無法學習四季劍法。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不到，無法學習四季劍法。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力太差，無法學習四季劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("siji-jianfa", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的四季劍法。\n");

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
        level = (int) me->query_skill("siji-jianfa",1);
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

        if( query("qi", me)<150 )
                return notify_fail("你的體力不夠練四季劍法。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠練四季劍法。\n");

        me->receive_damage("qi", 125);
        addn("neili", -125, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"siji-jianfa/" + action;
}

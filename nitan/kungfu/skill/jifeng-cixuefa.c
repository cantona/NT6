inherit SKILL;

mapping *action = ({
([      "action":"$N身形一展，施出一招「蠍尾針」，手中$w疾風般刺向$n的$l",
        "force" : 30,
        "attack": 15,
        "dodge" : 10,
        "parry" : 12,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "蠍尾針",
        "damage_type" : "刺傷"
]),
([      "action":"$N一聲叱喝，$w如靈蛇吞吐，施一招「蛾眉刺」向$n的$l刺去",
        "force" : 53,
        "attack": 21,
        "dodge" : 12,
        "parry" : 13,
        "damage": 37,
        "lvl"   : 10,
        "skill_name" : "蛾眉刺",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身一躍而起，手中$w使出「電光勁」，三刺連環，射向$n$l",
        "force" : 71,
        "attack": 24,
        "dodge" : 15,
        "parry" : 22,
        "damage": 45,
        "lvl"   : 20,
        "skill_name" : "電光勁",
        "damage_type" : "刺傷"
]),
([      "action":"$N手中$w閃電般一晃，陡然使出一招「回峰蜿蜒勢」，颼的刺向$n$l",
        "force" : 98,
        "attack": 35,
        "dodge" : 15,
        "parry" : 13,
        "damage": 54,
        "lvl"   : 40,
        "skill_name" : "回峰蜿蜒勢",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身躍起，一式「九轉連環勢」，手中$w連環九刺，盡數射向$n而去",
        "force" : 140,
        "attack": 46,
        "dodge" : 11,
        "parry" : 9,
        "damage": 65,
        "lvl"   : 60,
        "skill_name" : "九轉連環勢",
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage)
{
        return usage == "dagger" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<150 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("dagger", 1) < (int)me->query_skill("jifeng-cixuefa", 1))
                return notify_fail("你的基本短兵水平有限，無法領會更高深的疾風刺穴法。\n");

    return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("jifeng-cixuefa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所持的武器無法練習疾風刺穴法。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練疾風刺穴法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練疾風刺穴法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jifeng-cixuefa/" + action;
}
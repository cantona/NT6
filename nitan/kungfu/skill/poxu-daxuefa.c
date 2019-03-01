inherit SKILL;

mapping *action = ({
([      "action":"$N身形一展，施出一招「橫峰斷雲勢」，$w疾風般刺向$n的$l",
        "force" : 30,
        "attack": 15,
        "dodge" : 10,
        "parry" : 12,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "橫峰斷雲勢",
        "damage_type" : "刺傷"
]),
([      "action":"$N一聲叱喝，$w如靈蛇吞吐，施一招「青龍嘯」向$n的$l刺去",
        "force" : 53,
        "attack": 21,
        "dodge" : 12,
        "parry" : 13,
        "damage": 37,
        "lvl"   : 10,
        "skill_name" : "青龍嘯",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身一躍而起，$w使出一式「琉璃刃」，三刺連環，射向$n$l",
        "force" : 71,
        "attack": 24,
        "dodge" : 15,
        "parry" : 22,
        "damage": 45,
        "lvl"   : 20,
        "skill_name" : "琉璃刃",
        "damage_type" : "刺傷"
]),
([      "action":"$N$w閃電般一晃，陡然使出一招「虛空無盡勢」，颼的刺向$n$l",
        "force" : 98,
        "attack": 35,
        "dodge" : 15,
        "parry" : 13,
        "damage": 54,
        "lvl"   : 40,
        "skill_name" : "虛空無盡勢",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身躍起，一式「天地重元勢」，$w連環九刺，盡數射向$n而去",
        "force" : 140,
        "attack": 46,
        "dodge" : 11,
        "parry" : 9,
        "damage": 65,
        "lvl"   : 60,
        "skill_name" : "天地重元勢",
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage)
{
        return usage == "dagger" || usage == "finger" || usage == "parry";
}

int valid_learn(object me)
{
        int skill;

        skill = me->query_skill("poxu-daxuefa", 1);

        if( query("max_neili", me)<650 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("dagger", 1) < 50
           && (int)me->query_skill("finger", 1) < 50)
                return notify_fail("你基本短兵和基本指法水平有限，無法學習破"
                                   "虛打穴法。\n");

        if ((int)me->query_skill("dagger", 1) < skill
           && (int)me->query_skill("finger", 1) < skill)
                return notify_fail("你基本短兵或基本指法水平有限，無法領會更"
                                   "高深的破虛打穴法。\n");

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

        level = (int) me->query_skill("poxu-daxuefa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( objectp(weapon=query_temp("weapon", me) )
            && query("skill_type", weapon) != "dagger" )
                return notify_fail("你所持的武器無法練習破虛打穴法。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練破虛打穴法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練破虛打穴法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poxu-daxuefa/" + action;
}
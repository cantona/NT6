// This program is a part of NITAN MudLIB

inherit SKILL;

mapping *action = ({
([      "action": "$N身行不住的飄動，手中$w幻起道道寒光，一招「獅嘯蒼天」刺向$n",
        "force" : 126,
        "parry" : -3,
        "dodge" : -5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "獅嘯蒼天",
        "damage_type":  "刺傷"
]),
([      "action": "$N身行突然變了數個變化，手中$w也隨之變化，一招「金獅裂地」刺向$n的$l",
        "force" : 149,
        "parry" : -13,
        "dodge" : -10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "金獅裂地",
        "damage_type":  "割傷"
]),
([      "action": "$N抽身後退，一招「王者無情」,$w向波浪般的刺向$n的致命之處",
        "force" : 167,
        "parry" : -12,
        "dodge" : -15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "王者無情",
        "damage_type":  "刺傷"
]),
([      "action": "$N身行忽坐忽右，手中$w忽上忽下，一招「獅王怒吼」攻向$n的$l",
        "force" : 187,
        "parry" : -23,
        "dodge" : -19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "獅王怒吼",
        "damage_type":  "割傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，不能學習金獅狂劍。\n");

        if (me->query_skill("sword", 1) < 80)
                return notify_fail("你的基本劍法火候不夠，不能學習金獅狂劍。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠，不能學習金獅狂劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshi-kuangjian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的金獅狂劍。\n");

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
        level = (int) me->query_skill("jinshi-kuangjian",1);
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
                return notify_fail("你的體力不夠練金獅狂劍。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練金獅狂劍。\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jinshi-kuangjian/" + action;
}

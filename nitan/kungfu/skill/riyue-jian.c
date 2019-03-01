// riyue-jian.c 日月劍法

inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w上挑刺向$n。",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 30,
        "lvl"    : 0,
        "damage_type": "刺傷"
]),
([      "action" : "$N一挽手中$w，劍尖斜斜地向$n的$l揮去。",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 35,
        "lvl"    : 10,
        "damage_type": "刺傷"
]),
([      "action" : "只見$N手中$w閃出點點劍光，連成一線，刺向$n的臉部。",
        "force"  : 140,
        "dodge"  : 15,
        "damage" : 40,
        "lvl"    : 10,
        "damage_type": "刺傷"
]), 
([      "action" : "$N碎步急進，提劍沿劍身方向疾速上崩，一招「白蛇吐信」直取$n的$l",
        "force"  : 150,
        "dodge"  : 15,
        "damage" : 45,
        "lvl"    : 30,
        "damage_type": "刺傷"
]),
([      "action" : "只見$N舞動手中$w,從一個意想不到的角度突然挑出一劍，向$n的$l直刺。",
        "force"  : 130,
        "dodge"  : 25,
        "damage" : 45,
        "lvl"    : 40,
        "damage_type": "刺傷"
]),
([      "action" : "$N手臂往前一伸，$w向$n急刺過去。",
        "force"  : 120,
        "dodge"  : 25,
        "damage" : 50,
        "lvl"    : 50,
        "damage_type": "刺傷"
]),
([      "action" : "$N手拿$w，向$n的$l飛速一擊。",
        "force"  : 110,
        "dodge"  : 15,
        "damage" : 70,
        "lvl"    : 60,
        "damage_type": "刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
    object ob;

    if( query("max_neili", me)<100 )
        return notify_fail("你的內力不夠。\n");

    if ((int)me->query_skill("force") < 20)
        return notify_fail("你的內功火候太淺。\n");

    if( !objectp(ob=query_temp("weapon", me) )
        || query("skill_type", ob) != "sword" )
        return notify_fail("你必須先找一把劍才能學習劍法。\n"); 

    if ((int)me->query_skill("sword", 1) < (int)me->query_skill("riyue-jian", 1))
        return notify_fail("你的基本劍法水平有限，無法領會更高深的日月劍法。\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("riyue-jian", 1);
    for (i = sizeof(action); i > 0; i--)
        if (level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
    object weapon;

    if( !objectp(weapon=query_temp("weapon", me)) || 
       query("skill_type", weapon) != "sword" )
          return notify_fail("你使用的武器不對。\n");

    if( query("qi", me)<40 )
          return notify_fail("你的體力不夠練日月劍法。\n");

    if( query("neili", me)<10 )
          return notify_fail("你的內力不夠練日月劍法。\n");

    me->receive_damage("qi", 25);
    addn("neili", -10, me);

    return 1;
}

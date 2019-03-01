// wuyun-jianfa.c
inherit SKILL;

mapping *action = ({
([      "action" : "$N左小指輕彈，一招「宮韻」悄然劃向$n的後心",
        "force" : 100,
        "dodge" : 20,
        "damage" : 20,
        "lvl" : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N右手無名指若有若無的一劃，將琴弦並做一處，[商韻]已將$n籠罩",
        "force" : 120,
        "dodge" : 15,
        "damage" : 30,
        "lvl" : 20,
        "damage_type" : "刺傷"
]),
([      "action" : "$N五指疾揮，一式[角韻]無形的刺向$n的左肋",
        "force" : 150,
        "dodge" : 15,
        "damage" : 40,
        "lvl" : 40,
        "damage_type" : "刺傷"
]),
([      "action" : "$N將手中劍橫掃，同時左右手如琵琶似的疾彈，正是一招[支韻]",
        "force" : 180,
        "dodge" : 10,
        "damage" : 50,
        "lvl" : 60,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「羽韻」，將劍提至唇邊，如同清音出簫，劍掌齊出，劃向$n的$l",
        "force" : 210,
        "dodge" : 10,
        "damage" : 60,
        "lvl" : 80,
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry")
; }

int valid_learn(object me)
{
        if( query("max_neili", me)<400 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("wuyun-jianfa",1);
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

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練五韻七弦劍。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的體力不夠練五韻七弦劍。\n");

        me->receive_damage("qi", 40);
        addn("neili", -38, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuyun-jianfa/" + action;
}
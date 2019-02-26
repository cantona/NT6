inherit SKILL;

mapping *action = ({
([      "action" : "$N腳踏八卦方位，手中$w橫推，由上至下向$n砍去",
        "force"  : 145,
        "attack" : 35,
        "dodge"  : 30,
        "parry"  : 12,
        "lvl"    : 0,
        "damage" : 12,
        "damage_type" : "割傷",
]),
([      "action" : "$N刀鋒自下而上劃了個半弧，$w一提一收，平刃揮向$n的頸部",
        "force"  : 153,
        "attack" : 42,
        "dodge"  : 40,
        "parry"  : 15,
        "lvl"    : 20,
        "damage" : 18,
        "damage_type" : "割傷",
]),
([      "action" : "$N腳踏八卦方位，斜步上前，將$w舞得如白霧一般壓向$n",
        "force"  : 168,
        "attack" : 51,
        "dodge"  : 45,
        "parry"  : 17,
        "lvl"    : 40,
        "damage" : 24,
        "damage_type" : "割傷",
]),
([      "action" : "$N轉“嵌”位至“易”位，$w緩緩的斜着向$n推去",
        "force"  : 187,
        "attack" : 55,
        "dodge"  : 55,
        "parry"  : 21,
        "lvl"    : 60,
        "damage" : 35,
        "damage_type" : "割傷",
]),
([      "action" : "$N手拖$w，轉身躍起，一道白光射向$n的胸口",
        "force"  : 201,
        "attack" : 55,
        "dodge"  : 27,
        "parry"  : 32,
        "lvl"    : 80,
        "damage" : 35,
        "damage_type" : "割傷",
]),
([      "action" : "$N揮舞$w，上劈下撩，左擋右開，齊齊罩向$n",
        "force"  : 227,
        "attack" : 70,
        "dodge"  : 30,
        "parry"  : 35,
        "lvl"    : 100,
        "damage" : 40,
        "damage_type" : "割傷",
]),
([      "action" : "$N左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "force"  : 260,
        "attack" : 80,
        "dodge"  : 45,
        "parry"  : 35,
        "lvl"    : 120,
        "damage" : 46,
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<350 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的基本內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("shangjia-dao", 1))
                return notify_fail("你的基本刀法火候有限，無法領會更高深的商家刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("shangjia-dao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練商家刀法。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的體力不夠練商家刀法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shangjia-dao/" + action;
}
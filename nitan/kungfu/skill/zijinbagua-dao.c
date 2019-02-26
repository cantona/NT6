// zijinbagua-dao.c
// Designed by qdz
//

inherit SKILL;

mapping *action = ({
([      "action" : "$N腳踏八卦方位，手中$w橫推，由上至下向$n砍去",
        "force"  : 145,
        "attack" : 35,
        "dodge"  : 30,
        "parry"  : 12,
        "lvl"    : 0,
        "damage" : 32,
        "damage_type" : "割傷",
]),
([      "action" : "$N刀鋒自下而上劃了個半弧，$w一提一收，平刃揮向$n的頸部",
        "force"  : 173,
        "attack" : 42,
        "dodge"  : 40,
        "parry"  : 15,
        "lvl"    : 30,
        "damage" : 38,
        "damage_type" : "割傷",
]),
([      "action" : "$N腳踏八卦方位，斜步上前，將$w舞得如白霧一般壓向$n",
        "force"  : 198,
        "attack" : 51,
        "dodge"  : 45,
        "parry"  : 17,
        "lvl"    : 50,
        "damage" : 44,
        "damage_type" : "割傷",
]),
([      "action" : "$N轉“嵌”位至“易”位，$w緩緩的斜着向$n推去",
        "force"  : 237,
        "attack" : 55,
        "dodge"  : 55,
        "parry"  : 21,
        "lvl"    : 80,
        "damage" : 50,
        "damage_type" : "割傷",
]),
([      "action" : "$N手拖$w，轉身躍起，一道白光射向$n的胸口",
        "force"  : 261,
        "attack" : 55,
        "dodge"  : 27,
        "parry"  : 32,
        "lvl"    : 100,
        "damage" : 65,
        "damage_type" : "割傷",
]),
([      "action" : "$N揮舞$w，上劈下撩，左擋右開，齊齊罩向$n",
        "force"  : 287,
        "attack" : 70,
        "dodge"  : 30,
        "parry"  : 35,
        "lvl"    : 120,
        "damage" : 70,
        "damage_type" : "割傷",
]),
([      "action" : "$N左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "force"  : 360,
        "attack" : 80,
        "dodge"  : 45,
        "parry"  : 35,
        "lvl"    : 140,
        "damage" : 86,
        "damage_type" : "割傷",
]),
([      "action" : "$N驀的使一招「八卦八陣」，頓時劍光中無數朵刀花從四面八方湧向$n全身",
        "force"  : 410,
        "attack" : 95,
        "dodge"  : 64,
        "parry"  : 32,
        "lvl"    : 160,
        "damage" : 89,
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為尚淺，無法練習紫金八卦刀。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 120 )
                return notify_fail("你的基本刀法水平有限，無法練習紫金八卦刀。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("zijinbagua-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的紫金八卦刀。\n");

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
        level   = (int) me->query_skill("zijinbagua-dao", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<90 )
                return notify_fail("你的體力不夠，練不了紫金八卦刀。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠，練不了紫金八卦刀。\n");

        me->receive_damage("qi", 85);
        addn("neili", -100, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zijinbagua-dao/" + action;
}


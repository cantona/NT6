inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「星光燦爛」，雙拳閃動, 攻向$n的$l",
        "force"  : 120,
        "dodge"  : 10,
        "damage" : 2,
        "lvl"    : 0,
        "skill_name" : "星光燦爛",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招「搖光易位」，一拳橫掃，氣勢如虹，擊向$n的$l",
        "force"  : 140,
        "dodge"  : 12,
        "damage" : 5,
        "lvl"    : 20,
        "skill_name" : "搖光易位",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身影向飄動，臉浮微笑，一招「星過長空」，右拳快速拍向$n的$l",
        "force"  : 150,
        "dodge"  : 16,
        "damage" : 15,
        "lvl"    : 40,
        "skill_name" : "星過長空",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招「群星閃爍」，雙拳數分數合，$n只覺到處是$N的拳影",
        "force"  : 160,
        "dodge"  : 18,
        "damage" : 22,
        "lvl"    : 60,
        "skill_name" : "群星閃爍",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N施展開「千變萬化」繞著$n一轉，飛身遊走，拳出如風，不住的擊向$n。",
        "force"  : 170,
        "dodge"  : 21,
        "damage" : 26,
        "lvl"    : 80,
        "skill_name" : "千變萬化",
        "damage_type" : "瘀傷"
]),
([      "action" : "只見$N突然猛跨兩步，已到$n面前，右拳陡出，迅如崩雷，"
                   "一招「流星雨」擊向$n的前胸",
        "force"  : 220,
        "dodge"  : 22,
        "damage" : 30,
        "lvl"    : 100,
        "skill_name" : "點石成金",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招「北鬥生採」，拳影交錯，上中下一齊攻向$n。",
        "force"  : 250,
        "dodge"  : 25,
        "damage" : 35,
        "lvl"    : 120,
        "skill_name" : "北鬥生採",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練七星拳法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法練七星拳法。\n");

        if( query("max_neili", me)<120 )
                return notify_fail("你的內力太弱，無法練七星拳法。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("qixing-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的七星拳法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qixing-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠練七星拳法。\n");

        me->receive_damage("qi", 36);
        addn("neili", -18, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qixing-quan/" + action;
}
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N向上躍起，一招「穹內繁星」，手中$w自下而上，擊向$n的臉頰",
        "force" : 100,
        "dodge" : 0,
        "damage": 20,
        "lvl"   : 15,
        "skill_name" : "穹內繁星",
        "damage_type":  "抽傷"
]),
([      "action": "$N一招「星光奪目」，手中$w騰空一卷，直繞向$n的$l而去",
        "force" : 110,
        "dodge" : -10,
        "damage": 30,
        "lvl"   : 20,
        "skill_name" : "星光奪目",
        "damage_type":  "抽傷"
]),
([      "action": "$N一招「搖光換位」，手中$w騰空一卷，一聲脆響，猛地向$n劈頭打下",
        "force" : 120,
        "dodge" : -15,
        "damage": 40,
        "lvl"   : 40,
        "skill_name" : "搖光換位",
        "damage_type":  "抽傷"
]),
([      "action": "$N踏上一步，手中$w毫不停留，一招「七星聚月」，掃向$n的$l",
        "force" : 130,
        "dodge" : -30,
        "damage": 60,
        "lvl"   : 50,
        "skill_name" : "七星聚月",
        "damage_type":  "抽傷"
]),
([      "action": "$N半空一招「北斗生採」，手中$w如游龍洗空，長鳳戲羽，分點$n左右",
        "force" : 150,
        "dodge" : -35,
        "damage": 70,
        "lvl"   : 60,
        "skill_name" : "北斗生採",
        "damage_type":  "抽傷"
]),
([      "action": "$N向前急進，手中$w圈轉如虹，一招「朝拜天罡」，罩向$n前胸",
        "force" : 170,
        "dodge" : -40,
        "damage": 85,
        "lvl"   : 75,
        "skill_name" : "朝拜天罡",
        "damage_type":  "抽傷"
])
});

int valid_enable(string usage)
{
        return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條長鞭才能練鞭法。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候太淺，無法練天罡塵法。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力修為太弱，無法練天罡塵法。\n");

        if ((int)me->query_skill("whip") < 20)
                return notify_fail("你的基本鞭法等級太低，無法學天罡塵法。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("tiangang-chenfa", 1))
                return notify_fail("你的基本鞭法水平有限，無法領會更高深的天罡塵法。\n");

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

        level = (int) me->query_skill("tiangang-chenfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練天罡塵法。\n");

        if( query("neili", me)<45 )
                return notify_fail("你的內力不夠練天罡塵法。\n");

        me->receive_damage("qi", 30);
        addn("neili", -39, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tiangang-chenfa/" + action;
}
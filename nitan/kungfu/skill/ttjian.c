// yunlong-jian.c 雲龍劍
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"\n$N使一式"GRN"「第一招」"NOR"，手中$w嗡嗡微振，幻成一條白光刺向$n的$l",
        "lvl" : 0,
                "dodge"       : -100000,
                "parry"       : -100000,
                "force"       : 1,
                "damage"      : 1,
        "skill_name" : "悠悠順自然"
]),
([        "action" : "$N募的使一招"HIR"「第二招」"NOR"，頓時劍光中幾朵血花洒向$n全身",
                "dodge"       : 100000,
                "parry"       : 100000,
                "force"       : 1,
                "damage"      : 1,
        "lvl" : 0,
        "skill_name" : "紅葉舞秋山"
]),
([        "action" : "$N募的使一招"HIR"「第三招」"NOR"，頓時劍光中幾朵血花洒向$n全身",
                "dodge"       : -100000,
                "parry"       : 100000,
                "force"       : 1,
                "damage"      : 1,
        "lvl" : 0,
        "skill_name" : "紅葉舞秋山"
]),
([        "action" : "$N募的使一招"HIR"「第四招」"NOR"，頓時劍光中幾朵血花洒向$n全身",
                "dodge"       : 100000,
                "parry"       : -100000,
                "force"       : 1,
                "damage"      : 1,
        "lvl" : 0,
        "skill_name" : "紅葉舞秋山"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("yunlong-shengong", 1) < 20)
                return notify_fail("你的雲龍神功火候太淺。\n");
        if ((int)me->query_skill("yunlong-xinfa", 1) < 20)
                return notify_fail("你的雲龍心法火候太淺。\n");
        if ((int)me->query_skill("force", 1) < 40)
                return notify_fail("你的基本內功火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if ((int)me->query_skill("yunlong-shengong", 1) < 20)
                return notify_fail("你的雲龍神功火候太淺。\n");
        if( query("qi", me)<55 || query("neili", me)<40 )
                return notify_fail("你的內力或氣不夠練雲龍劍法。\n");
        me->receive_damage("qi", 50);
        addn("neili", -35, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point() { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"yunlong-jian/" + action;
}
int help(object me)
{
        write(HIC"\n雲龍劍法："NOR"\n");
        write(@HELP

    天地會看家本領，其特殊攻擊法威力奇大，堪稱武林一絕。

        學習要求：
                基本內功40級
                雲龍神功20級
                雲龍心法20級
                內力200
HELP
        );
        return 1;
}

// This program is a part of NT MudLIB
// liehuo-jian.c 烈火劍

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一招「四海雲飄」，$w似幻出片片白雲，四面八方的罩向$n",
        "lvl" : 0,
        "skill_name" : "四海雲飄",
]),
([        "action" : "$N一招「四通八達」，劍鋒亂指，攻向$n，$n根本不能分辯$w的來路",
        "lvl" : 19,
        "skill_name" : "四通八達",
]),
([        "action" : "$N使出「在天一方」，$w幻一條飛練，帶着一股寒氣划向$n的$l",
        "lvl" : 29,
        "skill_name" : "在天一方",
]),
([        "action" : "$N身子向上彈起，左手下指，一招「怪蟒翻身」，右手$w帶着一團劍花，逼向$n的$l",
        "lvl" : 39,
        "skill_name" : "怪蟒翻身",
]),
([        "action" : "$N一招「飛瀑倒懸」，左腳躍步落地，右手$w幻成一條雪白的瀑布，掃向$n的$l",
        "lvl" : 59,
        "skill_name" : "飛瀑倒懸",
]),
([        "action" : "$N右腿半屈般蹲，$w平指，一招「無聲無色」，劍尖無聲無色的慢慢的刺向$n的$l",
        "lvl" : 79,
        "skill_name" : "無聲無色",
]),
([  "action" : "$N一招「萬川歸海」，$w在$n的周身飛舞，令$n眼花繚亂，劍身在半空中突然停住刺向$n的$l",
        "lvl" : 99,
        "skill_name" : "萬川歸海",
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候不到，無法學習烈火劍法。\n");

        if (me->query_skill("force", 1) < me->query_skill("liehuo-jian", 1))
                return notify_fail("你的內功底子還不夠，無法領會更高深的烈火劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("liehuo-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的烈火劍法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = query_temp("weapon", me)) ||
                (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的武器不對。\n");
        if( (int)query("qi", me) < 35 )
                return notify_fail("你的氣不夠練烈火劍法。\n");
        me->receive_damage("qi", 30);
        return 1;
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 55;
        int d_e2 = 35;
        int p_e1 = 25;
        int p_e2 = 5;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liehuo-jian", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "劈傷" : "刺傷",
        ]);
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"liehuo-jian/" + action;
}

int help(object me)
{
        write(HIR"\n烈火劍法："NOR"\n");
        write(@HELP

    烈火劍法是明教的劍法。

        學習要求：
                基本內功10級
                內力修為10
HELP
        );
        return 1;
}
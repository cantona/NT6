// Last Modified by winder on May. 29 2001
// shaolin-leg.c 少林彈腿 與少林南拳互備

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"BLU"「落燕式」"NOR"，右腿支地，左腿畫弧，直踢$n的頭部",
        "lvl"    : 0,
        "skill_name" : "落燕式"
]),
([        "action" : "$N身形一閃，已從$n身邊掠過，右足反踢，正是一招"HIW"「撫平式」"NOR"，踹向$n的背心",
        "lvl"    : 20,
        "skill_name" : "撫平式"
]),
([        "action" : "$N身體半蹲，右足畫出個半圓，使出"HIC"「追月式」"NOR"，掃向$n的膝部",
        "lvl"    : 40,
        "skill_name" : "追月式"
]),
([        "action" : "$N上身微側，左足倏地彈出，踢向$n的頭部，襠部，正是一式"GRN"「連環式」"NOR"",
        "lvl"    : 60,
        "skill_name" : "連環式"
]),
([        "action" : "$N右足獨立，左足隨身形反轉橫掃，又左足立定，右足橫掃向前，一招"HIG"「掃葉式」"NOR"，踢向$n的$l",
        "lvl"    : 80,
        "skill_name" : "掃葉式"
]),
([        "action" : "$N躍起在半空，雙足亂舞，帶起無數勁風，"HIY"「盤龍式」"NOR"！迅捷無倫地卷向$n",
        "lvl"    : 100,
        "skill_name" : "盤龍式"
]),
});

int valid_enable(string usage) { return usage=="leg" || usage=="parry"; }
int valid_combine(string combo) { return combo=="shaolin-cuff"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學少林彈腿時手裏不能拿武器。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 1)
                return notify_fail("你的站樁功火候不夠，無法學少林彈腿。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練少林彈腿。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -30;
        int d_e2 = 0;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 100;
        int f_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shaolin-leg", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n少林彈腿："NOR"\n");
        write(@HELP

    彈腿是南少林入門腿法，注重腿法練習。

        學習要求：
                站樁功
HELP
        );
        return 1;
}

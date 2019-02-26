// songyang-strike.c 大嵩陽掌
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N身軀微欠，中宮一掌緩緩拍出，光明正大，是此套掌法的起首式"HIR"「大嵩陽」"NOR"",
        "lvl" : 0,
        "skill_name" : "大嵩陽"
]),
([        "action" : "$N忽拳忽掌，忽指忽抓，一式取自嵩山飛瀑的"HIC"「天河水」"NOR"，拍向$n的片刻間已變了十來種招數",
        "lvl" : 10,
        "skill_name" : "天河水"
]),
([        "action" : "$N大喝一聲，使出一路大嵩陽掌法中的"BLU"「鐵樑道」"NOR"，雙掌上下翻飛、大開大闔，連續擊向$n",
        "lvl" : 30,
        "skill_name" : "鐵樑道"
]),
([        "action" : "$N運勁於臂，大吼一聲"HIB"「萬仞壑」"NOR"，左掌拍出，右手成抓，同時襲到，兩股巨力排山倒海般向$n壓了過來",
        "lvl" : 50,
        "skill_name" : "萬仞壑",
]),
([        "action" : "$N運起丹田之氣猛喝一聲，一式"GRN"「觀勝峯」"NOR"，右掌挾帶着狂風，向前斜推，掌勢如劈山排雲搬壓向$n",
        "lvl" : 70,
        "skill_name" : "觀勝峯"
]),
([        "action" : "$N雙手忽而抓，忽而戳，忽而拳，忽而掌，連變數種，使一套"MAG"「小鐵樑」"NOR"手法，左手一晃，右掌向$n的$l按去",
        "lvl" : 90,
        "skill_name" : "小鐵樑"
]),
([        "action" : "$N氣沉丹田，猛然怒喝一聲，向前一個弓步，雙掌合成"HIM"「朝天閘」"NOR"，帶着風雷之聲奮力擊向$n",
        "lvl" : 110,
        "skill_name" : "朝天閘"
]),
([        "action" : "$N右腿向前弓步，一招"CYN"「千丈淵」"NOR"，左手化拳為掌，勁氣十足，閃電般地由上向下劈$n",
        "lvl" : 130,
        "skill_name" : "千丈淵"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="poyun-hand"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大嵩陽掌必須空手。\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 10)
                return notify_fail("你的寒冰真氣火候不夠，無法學大嵩陽掌。\n");
        if( query("max_neili", me)<10 )
                return notify_fail("你的內力太弱，無法練大嵩陽掌。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練大嵩陽掌。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
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
        int d_e1 = -35;
        int d_e2 = -10;
        int p_e1 = 10;
        int p_e2 = 35;
        int f_e1 = 170;
        int f_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("songyang-strike", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"songyang-strike/" + action;
}

int help(object me)
{
        write(HIC"\n大嵩陽掌："NOR"\n");
        write(@HELP

    大嵩陽掌為嵩山派守山掌法。可與破雲手互備。

        學習要求：
                寒冰真氣10級
                內力10
HELP
        );
        return 1;
}

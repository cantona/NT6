// yunlong-bian.c 雲龍鞭法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": "$N單手一揚，一招"MAG"「開天闢地」"NOR"，手中$w抖得筆直，對準$n當頭罩下",
        "lvl" : 0,
        "skill_name" : "開天闢地",
]),
([        "action": "$N身形一轉，一招"BLU"「龍騰四海」"NOR"，手中$w如矯龍般騰空一卷，猛地擊向$n太陽穴",
        "lvl" : 10,
        "skill_name" : "龍騰四海",
]),
([        "action": "$N唰的一抖長鞭，一招"HIM"「矯龍出水」"NOR"，手中$w抖得筆直，刺向$n雙眼",
        "lvl" : 20,
        "skill_name" : "矯龍出水",
]),
([        "action": "$N力貫鞭梢，一招"HIC"「破雲見日」"NOR"，手中$w舞出滿天鞭影，排山倒海般掃向$n全身",
        "lvl" : 30,
        "skill_name" : "破雲見日",
]),
([        "action": "$N運氣於腕，一招"HIY"「開山裂石」"NOR"，手中$w象一根銅棍般直擊向$n",
        "lvl" : 40,
        "skill_name" : "開山裂石",
]),
([        "action": "$N單臂一揮，一招"HIW"「玉帶圍腰」"NOR"，手中$w直擊向$n腰肋",
        "lvl" : 50,
        "skill_name" : "玉帶圍腰",
]),
([        "action": "$N高高躍起，一招"HIB"「大漠孤煙」"NOR"，手中$w筆直向$n當頭罩下",
        "lvl" : 60,
        "skill_name" : "大漠孤煙",
])
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }
int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
              || query("skill_type", weapon) != "whip" ) 
                return notify_fail("你必須先找一條鞭子才能練鞭法。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不足，沒有辦法練雲龍鞭法。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < 10)
                return notify_fail("你的基本鞭法火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("yunlong-bian", 1))
                return notify_fail("你的基本鞭法水平有限，無法領會更高深的雲龍鞭法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if ((int)me->query_skill("yunlong-shengong", 1) < 40)
                return notify_fail("你的雲龍神功火候太淺。\n");
        if( query("qi", me)<30 || query("neili", me)<30 )
                return notify_fail("你的體力不夠練雲龍鞭法。\n");
        me->receive_damage("qi", 25);
        addn("neili", -25, me);
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
        int d_e1 = -50;
        int d_e2 = -40;
        int p_e1 = -5;
        int p_e2 = 10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 300;
        int m_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yunlong-bian", 1);
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
                "damage_type" : random(2) ? "劈傷" : "瘀傷",
        ]);
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"yunlong-bian/" + action;
}
int help(object me)
{
        write(HIC"\n雲龍鞭法："NOR"\n");
        write(@HELP

    雲龍鞭法為天地會雲龍門武功。

        學習要求：
                雲龍神功40級
                內力200
HELP
        );
        return 1;
}

// taishan-sword.c 泰山劍法
// Last Modified by suncity may 31st,2002
// Modified by Java Sep.1998

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" :"朗月無雲",
        "action":  "$N手中$w一晃，向右滑出三步，一招"HIB"「朗月無雲」"NOR"，轉過身來，身子微矮，$w向$n斜斜刺去",
        "lvl" : 0
]),
([        "skill_name" :"峻嶺橫空",
        "action":  "$N手中$w圈轉，一招"HIC"「峻嶺橫空」"NOR"去勢奇疾，無數劍光刺向$n的$l",
        "lvl" : 10
]),
([        "skill_name" :"來鶴清泉",
        "action": "$N突然腰一彎，挺$w向$n刺去，這一劍力勁劍疾，正是一招"HIC"「來鶴清泉」"NOR"",
        "lvl" : 20
]),
([        "name":    "石關回馬",
        "action":  "$N手中$w刷的一聲，反手砍向$n，劍勢圓潤如意："HIY"「石關回馬」"NOR"！",
        "lvl" : 30
]),
([        "skill_name" : "泰山十八盤",
        "action":  "$N展開劍勢，身隨劍走，左邊一拐，右邊一彎，越轉越急。猛地$w劍光暴長，一招"HIM"「泰山十八盤」"NOR"往$n$l刺去",
        "lvl" : 40
]),
([        "skill_name" :"快活三裡",
        "action": "$N手臂暴長，手中$w豁豁展開，刷刷兩劍，指向$n，正是"GRN"「快活三裡」"NOR"",
        "lvl" : 50
]),
([        "skill_name" :  "七星落長空",
        "action":  "$N一招"HIR"「七星落長空」"NOR"挺$w向$n當胸刺去，劍光閃爍，$w發出嗡嗡之聲，罩住了$n胸口“膻中”、“神藏”、“靈墟”、“神封”、“步廊”、“幽門”、“通谷”七處大穴",
        "lvl" : 60
]),
([        "skill_name" :"五大夫劍",
        "action":  "$N手中$w倏地刺出，一連五劍，每一劍的劍招皆蒼然有古意。招數古樸，內藏奇變，正是"HIW"「五大夫劍」"NOR"",
        "lvl" : 70
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;
        if( query("max_neili", me)<150 )
                return notify_fail("你的內力不夠，沒有辦法練泰山劍法。\n");

        if( (int)me->query_skill("force") < 30 )
                return notify_fail("你的內力不夠，沒有辦法練泰山劍法。\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠，沒法練習泰山劍法。\n");
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
        int d_e1 = 5;
        int d_e2 = 30;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 110;
        int m_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("taishan-sword", 1);
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
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
        return __DIR__"taishan-sword/" + action;
}
int help(object me)
{
        write(HIC"\n泰山劍法："NOR"\n");
        write(@HELP

    泰山劍法為泰山本門劍法。

        學習要求：
                磐石神功20級
                內力修為20
HELP
        );
        return 1;
}

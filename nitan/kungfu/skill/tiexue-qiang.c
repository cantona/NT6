// tiexue-qiang.c 鐵血槍法
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N暴喝一聲，眶齜欲裂，手中$w狂野揮出，正是一式"RED"「血戰千里」"NOR"",
        "lvl"   : 0,
        "skill_name" : "血戰千里"
]),
([        "action":"$N腳下玄奧地連踏幾步，使出"CYN"「怒揮北斗」"NOR"，手中$w橫掃$n的$l",
        "lvl"   : 10,
        "skill_name" : "怒揮北斗"
]),
([        "action":"$N雙腿微蹲，使出一式"YEL"「干戈刺天」"NOR"，手中$w遙搖指向$n的頭部",
        "lvl"   : 20,
        "skill_name" : "干戈刺天"
]),
([        "action":"$N縱身躍起，一式"HIR"「屍橫遍野」"NOR"，手中$w帶起一團嘯聲揮向$n",
        "lvl"   : 30,
        "skill_name" : "屍橫遍野"
]),
([        "action":"$N手中$w中宮直進，一式"HIY"「直搗黃龍」"NOR"，對準$n的胸口刺出",
        "lvl"   : 50,
        "skill_name" : "直搗黃龍"
]),
([        "action":"$N手中$w一式"HIB"「拔山舉鼎」"NOR"，對準$n的$l自下而上猛挑。",
        "lvl"   : 80,
        "skill_name" : "拔山舉鼎"
]),
([        "action":"$N手中$w幻起一團白芒，一式"HIC"「破釜沉舟」"NOR"，脱手飛刺$n胸口",
        "lvl"   : 100,
        "skill_name" : "破釜沉舟"
]),
([        "action":"$N一式"GRN"「玉石俱焚」"NOR"，飛躍至$n身後，手中$w如疾電刺向自己胸口",
        "lvl"   : 120,
        "skill_name" : "玉石俱焚"
]),
});

int valid_enable(string usage) { return usage=="club" || usage=="parry"; }
int valid_learn(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "club" )
                return notify_fail("練鐵血槍法必須執棍。\n");
        if ((int)me->query_skill("guiyuan-tunafa", 1) < 20)
                return notify_fail("你歸元吐納法火候不夠，無法學鐵血槍法。\n");
        if( query("max_neili", me)<20 )
                return notify_fail("你的內力太弱，無法練鐵血槍法。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<50 )
                return notify_fail("你的內力或氣不夠練鐵血槍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -30, me);
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
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 300;
        int m_e2 = 500;  //鐵掌真牛逼 -_-b --qingyun
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tiexue-qiang", 1);
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
                "damage_type" : "挫傷", 
        ]);
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 0; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"tiexue-qiang/" + action;
}

int help(object me)
{
        write(HIC"\n鐵血槍法："NOR"\n");
        write(@HELP

    鐵血槍法是鐵掌幫主上官劍南所創。此槍法出自岳家槍法，當年
上官幫主一心抗金，圖復中原，槍法招式多與此相關。

        學習要求：
                歸元吐納法20級
                內力修為40
HELP
        );
        return 1;
}

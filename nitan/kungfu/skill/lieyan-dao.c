// lieyan-dao.c 烈焰刀
// Last Modified by winder on Sep. 27 2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一招「黑龍現身」，$w有如一條黑龍在$n的周身旋遊，勿快勿慢，變化若神",
        "lvl" : 0,
        "skill_name" : "黑龍現身",
]),
([        "action" : "$N一招「萬水千山」，左右腿一前一後，$w亂披風勢向$n的$l斬去",
        "lvl" : 8,
        "skill_name" : "萬水千山",
]),
([        "action" : "$N縱身躍落，一招「橫掃千里」，$w帶着疾風呼的一聲便向$n橫掃過去",
        "lvl" : 16,
        "skill_name" : "橫掃千里",
]),
([        "action" : "$N一招「左右開弓」，$w大開大闔，左右並進，左一刀，右一刀向$n的兩肩砍落",
        "lvl" : 24,
        "skill_name" : "左右開弓",
]),
([        "action" : "$N手中$w自上而下，一招「百丈飛瀑」，刀光流瀉，如一片雪白瀑布砍向$n的頭部",
        "lvl" : 33,
        "skill_name" : "百丈飛瀑",
]),
([        "action" : "$N揮舞$w，使出一招「直摧萬馬」，上劈下撩，左擋右開，如千軍萬馬般罩向$n",
        "lvl" : 42,
        "skill_name" : "直摧萬馬",
]),
([        "action" : "$N帶得刀風勁疾，一招「靈貓翻身」，一個猛轉身，連刀帶人往$n的$l的劈去",
        "lvl" : 51,
        "skill_name" : "靈貓翻身",
]),
([        "action" : "$N向前一個弓步，一招「上步劈山」，$w直直的劈出，一片流光般的刀影向$n的全身罩去",
        "lvl" : 60,
        "skill_name" : "上步劈山",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("shenghuo-shengong", 1) < 20)
                return notify_fail("你的聖火神功火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練烈焰刀法。\n");
        me->receive_damage("qi", 30);
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
        int d_e1 = 50;
        int d_e2 = 30;
        int p_e1 = 0;
        int p_e2 = -20;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 70;
        int m_e2 = 180;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("lieyan-dao", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);         /* 選擇出手招數序號 */
        return ([
                "action"        : action[seq]["action"],
                "dodge"         : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"         : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"         : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"        : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "割傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1; }
string perform_action_file(string action)
{
//        return __DIR__"lieyan-dao/" + action;
}
int help(object me)
{
        write(HIC"\n烈焰刀法："NOR"\n");
        write(@HELP

    烈焰刀法是明教的刀法。

        學習要求：
                九陽神功20級
                內力修為10
HELP
        );
        return 1;
}

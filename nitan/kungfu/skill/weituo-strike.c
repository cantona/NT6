// Last Modified by winder on May. 29 2001
// weituo-strike.c 韋陀掌 與如來千葉手互備

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙眼微睜，袍袖微微鼓氣，雙掌齊推，一招"HIC"「開天闢地」"NOR"，一股排山之勢壓向$n",
        "lvl"   : 0,
        "skill_name" : "開天闢地"
]),
([        "action" : "$N口中阿彌陀佛，一招"HIW"「即世即空」"NOR"，左掌擊向$n面門，另一掌卻按向$n的小腹",
        "lvl"   : 15,
        "skill_name" : "即世即空"
]),
([        "action" : "$N雙掌互錯，變幻莫測，一招"MAG"「無相無色」"NOR"，瞬息之間向$n攻出了三四一十二招",
        "lvl"   : 30,
        "skill_name" : "無相無色"
]),
([        "action" : "$N呼的一掌，沒有半點徵兆，一招"HIY"「佛法無邊」"NOR"，猛地向$n的$l擊打過去",
        "lvl"   : 40,
        "skill_name" : "佛法無邊"
]),
([        "action" : "$N雙掌交錯，若有若無，一招"HIB"「誰入地獄」"NOR"，帶着勁風拍向$n的肩頭和前胸",
        "lvl"   : 50,
        "skill_name" : "誰入地獄"
]),
([        "action" : "$N一招"HIM"「禪心永明」"NOR"，右手一掌擊出，緊接着右掌上一搭，擊向$n的$l",
        "lvl"   : 60,
        "skill_name" : "禪心永明"
]),
([        "action" : "$N雙手在空中齊劃，跟着雙掌齊推，一招"HIR"「我佛慈悲」"NOR"，一股排山倒海的掌力，直撲$n面門",
        "lvl"   : 70,
        "skill_name" : "我佛慈悲"
]),
([        "action" : "$N突然身行急轉，一招"GRN"「苦海回頭」"NOR"，掌影飛舞，霎時之間將$n四面八方都裹住了",
        "lvl"   : 80,
        "skill_name" : "苦海回頭"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="qianye-hand"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練韋陀掌必須空手。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 20)
                return notify_fail("你的站樁功火候不夠，無法練韋陀掌。\n");
        if ((int)me->query_skill("luohan-cuff", 1) < 20)
                return notify_fail("你的羅漢拳火候不夠，無法練韋陀掌。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練韋陀掌。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練韋陀掌。\n");
        me->receive_damage("qi", 25);
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
        int d_e1 = -10;
        int d_e2 = 10;
        int p_e1 = 30;
        int p_e2 = 60;
        int f_e1 = 100;
        int f_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("weituo-strike", 1);
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
        write(HIC"\n韋陀掌："NOR"\n");
        write(@HELP

    韋陀掌是南少林入門掌法。與如來千葉手互備。

        學習要求：
                站樁功20級
                羅漢拳20級
                內力修為50
HELP
        );
        return 1;
}

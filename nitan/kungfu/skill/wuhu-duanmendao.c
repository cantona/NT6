// wuhu-duanmendao.c 五虎斷門刀
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w斜指，一招"HIC"「直來直去」"NOR"，反身一頓，一刀向$n的$l撩去",
        "lvl"    : 0,
        "skill_name" : "直來直去",
]),
([        "action" : "$N一招"HIM"「童子掛畫」"NOR"，左右腿虛點，$w一提一收，平刃揮向$n的頸部",
        "lvl"    : 10,
        "skill_name" : "童子掛畫",
]),
([        "action" : "$N展身虛步，提腰躍落，一招"HIW"「推窗望月」"NOR"，刀鋒一卷，攔腰斬向$n",
        "lvl"    : 20,
        "skill_name" : "推窗望月",
]),
([        "action" : "$N一招"HIB"「力劈華山」"NOR"，$w大開大闔，自上而下劃出一個閃電，直劈向$n",
        "lvl"    : 30,
        "skill_name" : "力劈華山",
]),
([        "action" : "$N手中$w一沉，一招"MAG"「臨溪觀魚」"NOR"，雙手持刃攔腰反切，砍向$n的胸口",
        "lvl"    : 40,
        "skill_name" : "臨溪觀魚",
]),
([        "action" : "$N揮舞$w，使出一招"HIR"「張弓望的」"NOR"，上劈下撩，左擋右開，齊齊罩向$n",
        "lvl"    : 50,
        "skill_name" : "張弓望的",
]),
([        "action" : "$N一招"HIW"「風送輕舟」"NOR"，左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "lvl"    : 60,
        "skill_name" : "風送輕舟",
]),
([        "action" : "$N盤身駐地，一招"CYN"「川流不息」"NOR"，揮出一片流光般的刀影，向$n的全身湧去",
        "lvl"    : 70,
        "skill_name" : "川流不息",
]),
([        "action" : "$N右手後撤，手腕一翻，一招"YEL"「壯士斷腕」"NOR"，頓時一道白光直斬向$n的手臂",
        "lvl"    : 80,
        "skill_name" : "壯士斷腕",
]),
([        "action" : "$N高高躍起，一招"HIR"「人頭落地」"NOR"，手中$w直劈向$n的頸部",
        "lvl"    : 90,
        "skill_name" : "人頭落地",
]),
([        "action" : "$N貼地滑行，一招"BLU"「斷子絕孫」"NOR"，手中$w直撩去$n的襠部",
        "lvl"    : 100,
        "skill_name" : "斷子絕孫",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<350 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的基本內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("wuhu-duanmendao", 1))
                return notify_fail("你的基本刀法火候有限，無法領會更高深的五虎斷門刀法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練五虎斷門刀法。\n");
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
        int d_e1 = 55;
        int d_e2 = 35;
        int p_e1 = 5;
        int p_e2 = -15;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 140;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("wuhu-duanmendao", 1);
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
                "damage_type" : "割傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1; }
/*
mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action)-1;
        level = (int) me->query_skill("wuhu-duanmendao",1);

        if (level < 60 ) zhaoshu--;
        if (level < 50 ) zhaoshu--;
        if (level < 40 ) zhaoshu--;
        if (level < 30 ) zhaoshu--;
        if (level < 20 ) zhaoshu--;
        if (level < 10 ) zhaoshu--;
        return action[random(zhaoshu)];
}
*/
int double_attack() { return 1; }

string perform_action_file(string action)
{
        return __DIR__"wuhu-duanmendao/" + action;
}
int help(object me)
{
        write(HIC"\n五虎斷門刀："NOR"\n");
        write(@HELP

    五虎斷門刀是茅十八縱橫江湖，苟且偷生的功夫。

        學習要求：
                基本刀法20級
                內力100
HELP
        );
        return 1;
}

// jinwu-goufa.c 金蜈鈎法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N手中$w一抖，一式「靈蛇吐信」，閃電般的疾刺向$n的$l",
        "force"  : 50,
        "attack" : 15,
        "dodge"  : 10,
        "parry"  : 25,
        "damage" : 10,
        "lvl"    : 0,
        "damage_type":  "刺傷"
]),
([      "action" : "$N身形突閃，招式陡變，手中$w從一個絕想不到的方位斜刺向$n的$l",
        "force"  : 93,
        "attack" : 25,
        "dodge"  : 25,
        "parry"  : 30,
        "damage" : 5,
        "lvl"    : 10,
        "damage_type":  "刺傷"
]),
([      "action" : "$N一式「柔絲輕系」，劍意綿綿不絕，化做一張無形的大網將$n困在當中",
        "force"  : 135,
        "attack" : 33,
        "dodge"  : 22,
        "parry"  : 32,
        "damage" : 20,
        "lvl"    : 20,
        "damage_type":  "刺傷"
]),
([      "action" : "$N一聲陰笑，飛身縱起，一式「張牙舞爪」，手中$w狂舞，幻出千萬條手臂，合身撲向$n",
        "force"  : 189,
        "attack" : 39,
        "dodge"  : 40,
        "parry"  : 35,
        "damage" : 35,
        "lvl"    : 30,
        "damage_type":  "刺傷"
]),
([      "action" : "$N身形一旋看似欲走，手中$w卻倏的從腋下穿過，疾刺向$n的$l，好一式「天蠍藏針」",
        "force"  : 221,
        "attack" : 43,
        "dodge"  : 60,
        "parry"  : 40,
        "damage" : 48,
        "lvl"    : 40,
        "damage_type":  "刺傷"
]),
([      "action" : "$N腳步踉蹌，身形忽的向前跌倒，一式「井底望月」，掌中$w自下而上直刺$n的小腹",
        "force"  : 263,
        "attack" : 51,
        "dodge"  : 50,
        "parry"  : 45,
        "damage" : 63,
        "lvl"    : 70,
        "damage_type":  "刺傷"
]),
([      "action" : "$N身形一晃，一式「金蛇纏腕」，手中$w如附骨之蛆般無聲無息地刺向$n的手腕",
        "force"  : 285,
        "attack" : 62,
        "dodge"  : 40,
        "parry"  : 47,
        "damage" : 87,
        "lvl"    : 100,
        "damage_type":  "刺傷"
]),
([      "action" : "$N一聲厲嘯，身形沖天而起，一式「神蟾九變」，掌中$w如鬼魅般連刺$n全身九道大穴",
        "force"  : 291,
        "attack" : 71,
        "dodge"  : 30,
        "parry"  : 52,
        "damage" : 91,
        "lvl"    : 110,
        "damage_type":  "刺傷"
]),
([      "action" : "$N緩緩低首，手中$w中宮直進，一式「蜈化龍形」，迅捷無比地往$n的$l刺去",
        "force"  : 313,
        "attack" : 85,
        "dodge"  : 20,
        "parry"  : 54,
        "damage" : 95,
        "lvl"    : 130,
        "damage_type":  "刺傷"
]),
([      "action" : "$N深吸一口起，招演「萬毒至尊」，$w尖端透出一條強勁的黑氣，閃電般的襲向$n",
        "force"  : 328,
        "attack" : 88,
        "dodge"  : 30,
        "parry"  : 62,
        "damage" : 117,
        "lvl"    : 160,
        "damage_type":  "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，無法學習金蜈鈎法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinwu-goufa", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的金蜈鈎法。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 100;
        int f_e2 = 200;
        int m_e1 = 200;
        int m_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinwu-goufa", 1);
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
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }


int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力目前沒有辦法練習金蜈鈎法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練習金蜈鈎法。\n");

        addn("qi", -50, me);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jinwu-goufa/" + action;
}

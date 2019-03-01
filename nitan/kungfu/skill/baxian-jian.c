#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N面露微笑，一招「撥雲見日」，手中$w一抖，劍光暴長，洒向$n的$l",
        "force"  : 50,
        "attack" : 15,
        "dodge"  : 10,
        "parry"  : 25,
        "damage" : 10,
        "lvl"    : 0,
        "skill_name" : "撥雲見日",
        "damage_type":  "刺傷"
]),
([      "action" : "$N一招「仙人指路」，身形突閃，劍招陡變，手中$w從後部斜刺向$n的$l",
        "force"  : 70,
        "attack" : 21,
        "dodge"  : 25,
        "parry"  : 30,
        "damage" : 15,
        "lvl"    : 20,
        "skill_name" : "仙人指路",
        "damage_type":  "刺傷"
]),
([      "action" : "$N暴退數尺，一招「曹國舅拍板」，低首撫劍，隨後手中$w驟然穿上，刺向$n的$l",
        "force"  : 75,
        "attack" : 23,
        "dodge"  : 22,
        "parry"  : 32,
        "damage" : 20,
        "lvl"    : 40,
        "skill_name" : "曹國舅拍板",
        "damage_type":  "刺傷"
]),
([      "action" : "$N身形一晃，疾掠而上，使一招「丹鳳朝陽」，手中$w龍吟一聲，對準$n連遞數劍",
        "force"  : 90,
        "attack" : 29,
        "dodge"  : 10,
        "parry"  : 25,
        "damage" : 21,
        "lvl"    : 60,
        "skill_name" : "丹鳳朝陽",
        "damage_type":  "刺傷"
]),
([      "action" : "$N身形一展，施展出「湘子吹簫」，如影相隨，手中$w疾往$n的$l刺去",
        "force"  : 103,
        "attack" : 31,
        "dodge"  : 13,
        "parry"  : 22,
        "damage" : 23,
        "lvl"    : 80,
        "skill_name" : "湘子吹簫",
        "damage_type":  "刺傷"
]),
([      "action" : "$N一招「採和獻花」，側過身子，手中$w疾往斜上挑起，直指$n的$l",
        "force"  : 125,
        "attack" : 35,
        "dodge"  : 15,
        "parry"  : 25,
        "damage" : 28,
        "lvl"    : 100,
        "skill_name" : "採和獻花",
        "damage_type":  "刺傷"
]),
([      "action" : "$N微微一個轉身，一招「張果老倒騎驢」，手中$w卻已自肋下穿出，罩向$n的$l",
        "force"  : 133,
        "attack" : 42,
        "dodge"  : 11,
        "parry"  : 27,
        "damage" : 33,
        "lvl"    : 120,
        "skill_name" : "張果老倒騎驢",
        "damage_type":  "刺傷"
]),
([      "action" : "$N神色微變，一招「漢鍾離陰陽寶扇」，劍招頓時變得凌厲無比，手中$w閃電般射向$n",
        "force"  : 151,
        "attack" : 47,
        "dodge"  : 13,
        "parry"  : 32,
        "damage" : 36,
        "lvl"    : 140,
        "skill_name" : "漢鍾離陰陽寶扇",
        "damage_type":  "刺傷"
]),
([      "action" : "$N緩緩低首，接著一招「鐵拐李葫蘆系腰」，手中$w中宮直進，迅捷無比地往$n刺去",
        "force"  : 165,
        "attack" : 53,
        "dodge"  : 20,
        "parry"  : 34,
        "damage" : 43,
        "lvl"    : 160,
        "skill_name" : "鐵拐李葫蘆系腰",
        "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 10)
                return notify_fail("你的基本劍法火候不夠，無法學習八仙劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("baxian-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的八仙劍法。\n");

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
        int d_e1 = 45;
        int d_e2 = 20;
        int p_e1 = -10;
        int p_e2 = -25;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 110;
        int m_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("baxian-jian", 1);
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
                "damage_type" : random(2) ? "刺傷":"割傷",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力目前沒有辦法練習八仙劍法。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠，無法練習八仙劍法。\n");

        addn("qi", -43, me);
        addn("neili", -44, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baxian-jian/" + action;
}
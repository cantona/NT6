// wuyun-jian.c 五韻七絃劍
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N左小指輕彈，一招"HIM"「宮韻」"NOR"悄然划向$n的後心",
        "lvl" : 0,
        "skill_name" : "宮韻"
]),
([        "action" : "$N右手無名指若有若無的一劃，將琴絃並做一處，"HIR"[商韻]"NOR"已將$n籠罩",
        "lvl" : 10,
        "skill_name" : "商韻"
]),
([        "action" : "$N五指疾揮，一式"HIB"[角韻]"NOR"無形的刺向$n的左肋",
        "lvl" : 20,
        "skill_name" : "角韻"
]),
([        "action" : "$N將手中劍橫掃，同時左右手如琵琶似的疾彈，正是一招"HIG"[支韻]"NOR"",
        "lvl" : 30,
        "skill_name" : "支韻"
]),
([        "action" : "$N使出"HIW"「羽韻」"NOR"，將劍提至脣邊，如同清音出簫，劍掌齊出，划向$n的$l",
        "lvl" : 40,
        "skill_name" : "羽韻"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("kuihua-xinfa", 1) < 20)
                return notify_fail("你的葵花心法火候不到。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("jing", me)<35 || query("neili", me)<15 )
                return notify_fail("你的精或內力不夠練五韻七絃劍。\n");
        me->receive_damage("jing", 20);
        addn("neili", -15, me);
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
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 70;
        int m_e2 = 170;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuyun-jian", 1);
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
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"wuyun-jian/" + action;
}

int help(object me)
{
        write(HIC"\n五韻七絃劍："NOR"\n");
        write(@HELP

    日月神教黑木崖武功，梅莊大莊主黃鐘公的獨門劍法，將琴樂
融入劍法之中，以樂音擾敵心神，從而控制對方內息的變化。

        學習要求：
                葵花心法20級
                內力100
HELP
        );
        return 1;
}

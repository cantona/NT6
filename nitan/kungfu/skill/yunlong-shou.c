// yunlongshou.c -雲龍手
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"GRN"「草木皆兵」"NOR"，十指伸縮，虛虛實實地襲向$n的全身要穴",
        "lvl" : 0,
        "skill_name" : "草木皆兵"
]),
([        "action" : "在呼呼風聲中，$N使一招"BLU"「捕風捉影」"NOR"，雙手如鉤如戢，插向$n的$l",
        "lvl"   : 20,
        "skill_name" : "捕風捉影"
]),
([        "action" : "$N雙拳揮舞，一式"CYN"「浮雲去來」"NOR"，兩手環扣，攏成圈狀，猛擊$n的下頜",
        "lvl" : 30,
        "skill_name" : "浮雲去來"
]),
([        "action" : "$N雙手平伸，十指微微上下抖動，一招"YEL"「十指乾坤」"NOR"打向$n的$l",
        "lvl"   : 40,
        "skill_name" : "十指乾坤"
]),
([        "action" : "$N左手護胸，腋下含空，右手五指如鉤，一招"MAG"「抱殘守缺」"NOR"插向$n的頂門",
        "lvl"   : 50,
        "skill_name" : "抱殘守缺"
]),
([        "action" : "$N右腿斜插$n二腿之間，一招"RED"「掏虛搶珠」"NOR"，上手取目，下手反勾$n的襠部",
        "lvl"   : 60,
        "skill_name" : "掏虛搶珠"
]),
([        "action" : "$N一手虛指$n的劍訣，一招"HIC"「空手入刃」"NOR"，劈空抓向$n手中的兵刃",
        "lvl"   : 70,
        "skill_name" : "空手入刃"
]),
([        "action" : "$N左手指向$n胸前的五道大穴，右手斜指太陽穴，一招"HIY"「降龍伏虎」"NOR"使$n進退兩難",
        "lvl"   : 80,
        "skill_name" : "降龍伏虎"
]),
([        "action" : "$N一手頂天成爪，一手指地，一招"HIR"「撥雲見日」"NOR",勁氣籠罩$n的全身",
        "lvl"   : 90,
        "skill_name" : "撥雲見日"
]),
([        "action" : "$N一式"HIM"「如煙往事」"NOR"，拳招若隱若現，若有若無，緩緩地拍向$n的丹田",
        "lvl" : 100,
        "skill_name" : "如煙往事"
]),
([        "action" : "$N隨意揮洒，使一式"HIR"「我心依舊」"NOR"，掌心微紅,徐徐拍向$n的$l",
        "lvl" : 80,
        "skills_name" : "我心依舊"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="yunlong-zhua"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練雲龍手必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的雲龍神功火候不夠，無法學雲龍手。\n");

        if( query("max_neili", me)<700 )
                return notify_fail("你的內力太弱，無法練雲龍手。\n");

        if ((int)me->query_skill("hand",1) < 100)
                return notify_fail("你的基本手法火候不夠，無法學雲龍手。\n");

        if ((int)me->query_skill("hand",1) < (int)me->query_skill("yunlong-shou",1))
                return notify_fail("你的基本手法水平有限，無法繼續學雲龍手。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練雲龍手。\n");
        me->receive_damage("qi", 35);
        addn("neili", -25, me);
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
        int d_e1 = -45;
        int d_e2 = -15;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 140;
        int f_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yunlong-shou", 1);
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
int power_point(object me) {
        if ((int)me->query_skill("yunlong-xinfa",1) < 100)
        return 0.7;
        else if ((int)me->query_skill("yunlong-xinfa",1) > 200)
        return 1.4;
        else return ( ((int)me->query_skill("yunlong-xinfa",1)-100)/100*0.7+0.7 );
}

string perform_action_file(string action)
{
        return __DIR__"yunlong-shou/" + action;
}
int help(object me)
{
        write(HIC"\n雲龍手："NOR"\n");
        write(@HELP

    天地會雲龍門武功。
    可與雲龍爪互備。

        學習要求：
                基本手法30級
                基本內功50級
                雲龍神功50級
                內力250
                相應的雲龍心法
HELP
        );
        return 1;
}

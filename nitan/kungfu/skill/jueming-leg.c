// jueming-leg.c 絕命腿
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$n用右腳鈎踢$N左腳下盤，$N提腳避開$n鋒芒，一招「黑虎蹬山」，\n迅速猛力地連續踹擊$n的$l。",
        "lvl"   : 0,
        "skill_name" : "黑虎蹬山" 
]),
([        "action" : "$n右拳擊$N頭部，$N上體後閃，同時起右腳猛蹬$n腹部，「白猿登枝」，\n突然變側踹腿猛力踹擊$n$l。",
        "lvl"   : 10,
        "skill_name" : "白猿登枝" 
]),
([        "action" : "$N左拳撩撥$n拳頭，右腳內側踩擊$n的脛骨，一招「虎尾攪林」\n側踹腿攻擊$n$l",
        "lvl"   : 20,
        "skill_name" : "虎尾攪林" 
]),
([        "action" : "$N用右腳鈎踢$n左腿下盤，同時右鈎踢突然橫掃$n腰部，一招「風捲殘葉」",
        "lvl"   : 30,
        "skill_name" : "風捲殘葉" 
]),
([        "action" : "$n用右拳猛擊$N面部，$N速用右裏合腿掛攔$n腕部，一招「疾浪翻花」，\n變為側踹腿踹$n的$l",
        "lvl"   : 40,
        "skill_name" : "疾浪翻花" 
]),
([        "action" : "$N突發右腿彈踢$n襠部，「浪子踢球」，右腿速變點腳猛力踢擊$n之$l",
        "lvl"   : 60,
        "skill_name" : "浪子踢球" 
]),
([        "action" : "$N用右腳鈎踢$n足根，使出「順風扯旗」，順勢變為橫腿，側倒疾掃$n$l",
        "lvl"   : 80,
        "skill_name" : "順風扯旗" 
]),
([        "action" : "$N起右腳彈踢$n檔部，一招「野馬奔蹄」，彈踢之腿疾變為側踹腿，猛力攻擊$n$l",
        "lvl"   : 100,
        "skill_name" : "野馬奔蹄" 
]),
});

int valid_enable(string usage) { return  usage=="leg" || usage=="parry"; }
int valid_combine(string combo) { return combo=="huagu-mianzhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練絕命腿必須空手。\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 20)
                return notify_fail("你的毒龍大法火侯不夠，無法學絕命腿。\n");
        if ((int)me->query_skill("leg", 1) < 20)
                return notify_fail("你的基本腿法火侯不夠，無法學絕命腿。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練絕命腿。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的氣血太低了。\n");
        if( query("neili", me)<10 )
                return notify_fail("你的內力不夠練絕命腿。\n");
        me->receive_damage("qi", 30);
        addn("neili", -5, me);
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
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 220;
        int f_e2 = 320;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jueming-leg", 1);
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
string perform_action_file(string action)
{
        return __DIR__"jueming-leg/" + action;
}

int help(object me)
{
        write(HIC"\n絕命腿"NOR"\n");
        write(@HELP

    絕命腿招是神龍島腿法，可與化骨綿掌互備。

        學習要求：
                毒龍大法20級
                基本腿法20級
                內力修為100
HELP
        );
        return 1;
}

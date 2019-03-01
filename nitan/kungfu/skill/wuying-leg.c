// wuying-leg.c 無影腿
// Last Modified by sir 10.21.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙手虛晃，左腳猛地飛起，一式"HIB"「無影無蹤」"NOR"，腳尖晃動，踢向$n的屁股",        
        "lvl" : 0,
        "skill_name" : "無影無蹤"
]),
([        "action" : "$N左腳頓地，別轉身來抽身欲走，只一剎那間一回身，右腳一式"HIW"「無影亂舞」"NOR"，猛踹$n的$l",
        "lvl" : 10,
        "skill_name" : "無影亂舞"
]),
([        "action" : "$N左手一掙，反手扭搭住$n的右手，右腳同時踹出，既猛且準，一式"GRN"「叢叢疊疊」"NOR"，踢中的$n的胸口",
        "lvl" : 20,
        "skill_name" : "叢叢疊疊"
]),
([        "action" : "$N突然躍起，雙足連環圈轉，一式"YEL"「秋風掃葉」"NOR"，足帶風塵，攻向$n的全身",
        "lvl" : 30,
        "skill_name" : "秋風掃葉"
]),
([        "action" : "$N兩手護胸，雙腳交叉踢起，一式"HIC"「腿掃殘雲」"NOR"，腳腳不離$n的面門左右",
        "lvl" : 40,
        "skill_name" : "腿掃殘雲"
]),
([        "action" : "$N突然側身，卻步後退，一個前空翻，右腳自上而下一式"HIM "「慧星墜地」"NOR"，照$n的面門直劈下來",
        "lvl" : 50,
        "skill_name" : "慧星墜地"
]),
([        "action" : "$N使一式"HIW"「東風吹雪」"NOR"，全身突然飛速旋轉，雙足忽前忽後，迅猛無極踹向$n的胸口",
        "lvl" : 60,
        "skill_name" : "東風吹雪"
]),
([        "action" : "$N抽身躍起，開聲吐氣，大喝一聲：嗨！一式"HIY"「佛山無影」"NOR"，雙腳如旋風般踢向$n的$l",
        "lvl" : 80,
        "skill_name" : "佛山無影"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }
int valid_combine(string combo) { return combo=="cuixin-strike"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("無影腿必須空手。\n");
        if ((int)me->query_skill("qingming-xuangong", 1) < 15)
                return notify_fail("你的青冥玄功火候不夠，無法學無影腿。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練無影腿。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練無影腿。\n");
        me->receive_damage("qi", 45);
        addn("neili", -40, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
        {
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
        }
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 15;
        int d_e2 = 35;
        int p_e1 = -40;
        int p_e2 = 20;
        int f_e1 = 250;
        int f_e2 = 350;        
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuying-leg", 1);
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

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"wuying-leg/" + action;
}

int help(object me) {
        write(HIC"\n無影腿："NOR"\n");
        write(@HELP

    無影腿是青城派的功夫。
    可與摧心掌互備。

        學習要求：
                青冥玄功15級
                內力100
HELP
        );
        return 1;
}

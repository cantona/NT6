// chuanyun-leg.c 穿雲腿法
// Last Modified by winder on Sep. 27 2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N身子疾轉，右腳貼地伸出，一式"BLU"「劃地為牢」"NOR"，橫掃$n的下盤",
        "lvl" : 0,
        "skill_name" : "劃地為牢"
]),
([        "action" : "$N左腿踢出，不待左腿落下，右腳緊跟著凌空踢出，一式"GRN"「追風逐電」"NOR"，雙腳先後踢向$n的$l",
        "lvl" : 15,
        "skill_name" : "追風逐電"
]),
([        "action" : "$N一式"MAG"「左右穿花」"NOR"，左腳橫踹，隨即向右前方落步，右腳迅速發力踢向$n的$l",
        "lvl" : 30,
        "skill_name" : "左右穿花"
]),
([        "action" : "$N突然一個後翻，一式"HIW"「倒踢北鬥」"NOR"，雙腿晃動，向$n的$l踢去",
        "lvl" : 45,
        "skill_name" : "倒踢北鬥"
]),
([        "action" : "$N使一式"HIC"「登雲步月」"NOR"，拔地而起，雙腿連續踢出，擊向$n的胸口",
        "lvl" : 60,
        "skill_name" : "登雲步月"
]),
([        "action" : "$N身子盤旋飛起，一式"HIY"「橫掃九州」"NOR"，右腿橫掃$n的$l",
        "lvl" : 75,
        "skill_name" : "橫掃九州"
]),
([        "action" : "$N左手一繞，向擊向$n的頭部，一式"HIB"「無影無蹤」"NOR"，右腿突然踢向$n的$l",
        "lvl" : 90,
        "skill_name" : "無影無蹤"
]),
([        "action" : "$N使一式"HIR"「雷霆天下」"NOR"，身體凌空而起，雙腿連環，只見漫天腿影籠罩著$n",
        "lvl" : 100,
        "skill_name" : "雷霆天下"
]),
});

int valid_enable(string usage) { return usage=="leg" || usage=="parry"; }
int valid_combine(string combo) { return combo=="zhentian-cuff"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練穿雲腿必須空手。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 20)
                return notify_fail("你的玄天無極功火候不夠，無法學穿雲腿。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練穿雲腿。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<15 )
                return notify_fail("你的內力不夠練穿雲腿。\n");
        me->receive_damage("qi", 25);
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
        int d_e1 = -40;
        int d_e2 = -10;
        int p_e1 = -5;
        int p_e2 = 25;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("chuanyun-leg", 1);
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
int success() { return 10; }
int power_point(object me) { 
        if( query("gender", me) == "女性" )
          return 1.2;
        else 
          return 0.8;
}

string perform_action_file(string action)
{
        return __DIR__"chuanyun-leg/" + action;
}

int help(object me)
{
        write(HIC"\n穿雲腿："NOR"\n");
        write(@HELP

    穿雲腿是昆侖派側重女弟子的武功。

        學習要求：
                玄天無極功20級
                內力50
HELP
        );
        return 1;
}

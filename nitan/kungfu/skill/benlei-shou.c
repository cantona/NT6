// Last Modified by winder on Sep. 12 2001
// benlei-shou.c 奔雷手

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N一式"CYN"「行雲流水」"NOR"，雙掌一翻，一股勁力緩緩推向$n的$l",
        "lvl"   : 0,
        "skill_name" : "行雲流水"
]),
([      "action" : "$N一式"BLU"「披雲戴月」"NOR"，兩掌一並，疾向$n的$l戳去",
        "lvl"   : 10,
        "skill_name" : "披雲戴月"
]),
([      "action" : "$N使一式"MAG"「翻雲赴雨」"NOR"，左掌微拂，右掌乍伸乍合，猛地插往$n的$l",
        "lvl"   : 20,
        "skill_name" : "翻雲覆雨"
]),
([      "action" : "$N掌心隱隱發紅，一式"YEL"「排山倒海」"NOR"，掌力如海水般向$n擊去",
        "lvl"   : 30,
        "skill_name" : "排山倒海"
]),
([      "action" : "$N身形往上一縱，使出一式"HIB"「烏雲敝日」"NOR"，雙掌一攤，筆直地向$n的$l拍去",
        "lvl"   : 40,
        "skill_name" : "烏雲敝日"
]),
([      "action" : "$N身形一變，使一式"HIB"「重雲深鎖」"NOR"，雙掌帶著蕭剎的勁氣，猛地擊往$n的$l",
        "lvl"   : 50,
        "skill_name" : "重雲深鎖"
]),
([      "action" : "$N使一式"HIW"「撕天排雲」"NOR"，左掌凝重，右掌輕盈，同時向$n的$l擊去",
        "lvl"   : 60,
        "skill_name" : "撕天排雲"
]),
([      "action" : "$N突地一招"HIM"「雲海波濤」"NOR"，雙掌挾著一陣風雷之勢，猛地劈往$n的$l",
        "lvl"   : 70,
        "skill_name" : "雲海波濤"
]),
([      "action" : "$N一式"HIY"「變雲無定」"NOR"，雙掌縵妙地一陣揮舞，不覺已擊到$n的$l上",
        "lvl"   : 80,
        "skill_name" : "變雲無定"
]),
([      "action" : "$N一式"HIR"「殃雲天降」"NOR"，身形向上竄起丈余，雙掌一高一低，看似簡單，卻令$n無法躲閃",
        "lvl"   : 90,
        "skill_name" : "殃雲天降"
]),
([      "action" : "$N一式"HIW"「雲萊仙境」"NOR"，身形凝立不動，兩掌間綻出萬道霞光，將$n緊緊罩住",
        "lvl"   : 100,
        "skill_name" : "雲萊仙境"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry" ; }
int valid_combine(string combo) { return combo=="baihua-cuoquan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練奔雷手必須空手。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練奔雷手。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練奔雷手。\n");
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
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = 10;
        int p_e2 = 40;
        int f_e1 = 180;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("benlei-shou", 1);
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
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"benlei-shou/" + action;
}

int help(object me)
{
        write(HIM"\n奔雷手："NOR"\n");
        write(@HELP

    紅花會四當家文泰來的看門武功。

        學習要求：
                紅花神功20級
                內力修為100
HELP
        );
        return 1;
}
// Last Modified by Winder on May. 29 2001
// jimie-claw.c 寂滅爪 和波羅密手互備 截至佛經中人生八苦。

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N全身拔地而起，一式"HIG"「生」"NOR"字訣，雙爪相扣，迅猛地抓向$n，卻又不帶任何霸氣",
        "lvl"    : 0,
        "skills_name" : "生",
]),
([        "action" : "$N一式"HIY"「老」"NOR"字訣，雙爪中宮直進，卻不變招，待其用老之際，$n已避無可避",
        "lvl"    : 10,
        "skills_name" : "老",
]),
([        "action" : "$N腳步蹣跚，有如"MAG"「病」"NOR"態，左手曲抓隨意一揮，竟然能帶起數到勁風直襲$n$l",
        "lvl"    : 20,
        "skills_name" : "病",
]),
([        "action" : "$N雙爪交錯，一式"HIB"「死」"NOR"字訣，身隨抓動，追著$n如影附骨，誓要擊殺$p去爪下",
        "lvl"    : 30,
        "skills_name" : "死",
]),
([        "action" : "$N一式"GRN"「求不得」"NOR"，右爪突出，左爪跟進，接著右抓又出，雙爪相疊，抓向$n的胸口",
        "lvl"    : 40,
        "skills_name" : "求不得",
]),
([        "action" : "$N原地不動，一式"RED"「愛別離」"NOR"，只待$n襲來，雙手猛然變爪而出，直插$n的兩處大穴",
        "lvl"    : 60,
        "skills_name" : "愛別離",
]),
([        "action" : "$N翻身一揮，雙爪無數道勁氣破空而出，一式"HIM"「怨憎會」"NOR"，迅疾無比地飛刺向$n",
        "lvl"    : 80,
        "skills_name" : "怨憎會",
]),
([        "action" : "$N騰空高飛數丈，打出一式"HIR"「五陰熾盛」"NOR"，一時間空中出現無數$N的身影，層層抓影罩向$n",
        "lvl"    : 100,
        "skills_name" : "五陰熾盛",
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo){ return combo=="boluomi-hand"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練寂滅爪必須空手。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 40)
                return notify_fail("你的站樁功火候不夠，無法學寂滅爪。\n");
        if( query("max_neili", me)<400 )
                return notify_fail("你的內力太弱，無法練習寂滅爪。\n");
        if (me->query_skill("sanhua-strike", 1) < 40)
                return notify_fail("你的散花掌火候不夠，無法學寂滅爪。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練寂滅爪。\n");
        me->receive_damage("qi", 40);
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
        int d_e1 = 60;
        int d_e2 = 30;
        int p_e1 = -5;
        int p_e2 = -20;
        int f_e1 = 100;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("jimie-claw", 1);
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
                "damage_type" : random(2) ? "內傷" : "抓傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
         return __DIR__"jimie-claw/" + action;
}

int help(object me)
{
        write(HIC"\n寂滅爪："NOR"\n");
        write(@HELP

    寂滅爪是南少林入門爪法，和波羅密手互備。出自佛經中人生八苦。

        學習要求：
                站樁功40級
                散花掌40級
                內力修為400。
HELP
        );
        return 1;
}

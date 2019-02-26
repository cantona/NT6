// Last Modified by Winder on May. 29 2001
// boluomi-hand.c 波羅蜜手 和寂滅爪互備 截自佛經中之“六度”。

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action":"$N雙手合十做鞠，第一式"BLU"「佈施式」"NOR"打出，內勁已逼得衣帶翻飛，將$n層層籠罩",
        "lvl"   : 0,
        "skill_name" : "佈施式"
]),
([      "action":"$N右手伸出，上翻下壓，左揮右劈，在$n眼前連連變幻，這招叫做"RED"「持戒式」"NOR"，最是變化無窮",
        "lvl"   : 10,
        "skill_name" : "持戒式"
]),
([      "action":"$N低頭垂肩，使"YEL"「忍辱式」"NOR"這招，對眼前$n不聞不問，暗地裏卻聚力雙手，伺機拍出",
        "lvl"   : 20,
        "skill_name" : "忍辱式"
]),
([      "action":"$N得理不饒人，一招"GRN"「精進式」"NOR"，雙臂晃動，打出片片掌影，一步步向$n進逼過去",
        "lvl"   : 40,
        "skill_name" : "精進式"
]),
([      "action":"$N一式"HIY"「禪定式」"NOR"，單臂凌空懸垂，心中平靜如水，一點點向着$n頂門壓將下來",
        "lvl"   : 80,
        "skill_name" : "禪定式"
]),
([      "action":"$N雙臂揮動，幻出一蓮花般手印，以"MAG"「般若式」"NOR"向$n推來，不緊不慢，卻又凝重異常",
        "lvl"   : 100,
        "skill_name" : "般若式"
]),
});
int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo){ return combo=="jimie-claw"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練波羅蜜手必須空手。\n");
        if( query("max_neili", me)<400 )
                return notify_fail("你的內力太弱，無法練波羅蜜手。\n");
        if ((me->query_skill("qianye-hand", 1) < 40) ||
                me->query_skill("sanhua-strike", 1) < 40)
                return notify_fail("你的千葉手和散花掌火候不夠，無法學波羅蜜手。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練波羅蜜手。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
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
        int d_e2 = -25;
        int p_e1 = 0;
        int p_e2 = 35;
        int f_e1 = 210;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("boluomi-hand", 1);
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
        return __DIR__"boluomi-hand/" + action;
}

int help(object me)
{
        write(HIC"\n波羅蜜手："NOR"\n");
        write(@HELP

    波羅蜜手是南少林手法，和寂滅爪互備。
    出自佛經中之“六度”。

        學習要求：
                站樁功40級
                散花掌40級
                如來千葉手40級
                內力修為400
HELP
        );
        return 1;
}

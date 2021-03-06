// poyun-hand.c 破雲手
// Last Modified by sir 10.23.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙臂一攏，左爪直攻$n下盤，右爪卻挾風雷之勢推向$n腰間，一虛一實，正是一招"BLU"「翻雲覆雨」"NOR"",
        "lvl"    : 0,
        "skill_name"  : "翻雲覆雨"
]),
([        "action" : "$N身形陡起，如雄鷹擊日般“倏”地從$n頭頂越過，使一招"CYN"「排山倒海」"NOR"雙手疾向$n腦後拍下",
        "lvl"    : 10,
        "skill_name"  : "排山倒海"
]),
([        "action" : "$N就地一滾，突然到了$n身前，使一招"MAG"「風捲殘雲」"NOR"，雙手直拍$n小腹",
        "lvl"    : 20,
        "skill_name"  : "風捲殘雲"
]),
([        "action" : "$N左手護胸，右手凝勁後發，一招"HIC"「雲過天晴」"NOR"，緩緩託向$n的$l",
        "lvl"    : 40,
        "skill_name"  : "雲過天晴"
]),
([        "action" : "$N微微一笑，疾速前撲，使一招"HIW"「夢幻塵緣」"NOR"，直拍$n胸前三大要穴",
        "lvl"    : 60,
        "skill_name"  : "夢幻塵緣"
]),
([        "action" : "$N身形詭異，忽左忽右，陡然轉到$n身後，一招"HIR"「電光火石」"NOR"，雙手直向$n咽喉插下",
        "lvl"    : 80,
        "skill_name"  : "電光火石"
]),
([        "action" : "$N一聲長嘯，身形突然拔起，使出"HIG"「如水中月」"NOR"，由半空盤旋下擊，$n頓覺漫天掌影，罩向全身要穴",
        "lvl"    : 100,
        "skill_name"  : "如水中月"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="songyang-strike"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練破雲手必須空手。\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 10)
                return notify_fail("你的寒冰真氣火候不夠，無法學破雲手。\n");
        if( query("max_neili", me)<10 )
                return notify_fail("你的內力太弱，無法學破雲手。\n");
        if( query("str", me)<25 )
                return notify_fail("你的臂力太差，無法學破雲手。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠練破雲手。\n");
        me->receive_damage("qi", 30);
        addn("neili", -20, me);
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
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 120;
        int f_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("poyun-hand", 1);
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
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"poyun-hand/" + action;
}

int help(object me)
{
        write(HIC"\n破雲手："NOR"\n");
        write(@HELP

    破雲手為嵩山派手法。可與大嵩陽掌互備。

        學習要求：
                寒冰真氣10級
                先天膂力25
                內力10
HELP
        );
        return 1;
}

// This program is a part of NT MudLIB
// sougu.c 搜骨鷹爪功

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙臂一攏，左爪直攻$n下盤，右爪卻挾風雷之勢推向$n腰間，一虛一實，正是一招"HIM"「推爪式」"NOR"",
        "lvl"    : 0,
        "skill_name" : "推爪式"
]),
([        "action" : "$N身形陡起，如雄鷹擊日般“倏”地從$n頭頂越過，使一招"HIR"「蓋爪式」"NOR"雙爪疾向$n腦後擊下",
        "lvl"    : 5,
        "skill_name" : "蓋爪式"
]),
([        "action" : "$N就地一滾，突然到了$n身前，使一招"HIB"「掏爪式」"NOR"，右爪直奔$n小腹",
        "lvl"    : 10,
        "skill_name" : "掏爪式"
]),
([        "action" : "\n$N左爪護胸，右爪凝勁後發，一招"HIC"「托爪式」"NOR"，緩緩托向$n的$l",
        "lvl"    : 20,
        "skill_name" : "托爪式"
]),
([        "action" : "\n$N身形詭異，疾速前撲，使一招"HIG"「撩爪式」"NOR"，直撩$n襠部",
        "lvl"    : 35,
        "skill_name" : "撩爪式"
]),
([        "action" : "\n$N身形飄忽，陡然轉到$n身後，一招"HIW"「鎖爪式」"NOR"，雙爪直向$n嚥喉插下",
        "lvl"    : 60,
        "skill_name" : "鎖爪式"
]),
([        "action" : "\n$N一聲厲嘯，身形拔起，使出"HIC"「千爪式」"NOR"，由半空盤旋下擊，$n頓覺漫天爪影，罩向全身死穴",
        "lvl"    : 85,
        "skill_name" : "千爪式"
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練搜骨鷹爪功必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學搜骨鷹爪功。\n");

        if ((int)query("max_neili", me) < 600)
                return notify_fail("你的內力太弱，無法學搜骨鷹爪功。\n");

        if ((int)me->query_str() < 33)
                return notify_fail("你現在的膂力太差，還無法學搜骨鷹爪功。\n");

        return 1;
}

int practice_skill(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("你的必須空手才能練習。\n");
        if ((int)query("qi", me) < 40)
                return notify_fail("你的體力太低了。\n");
        if ((int)query("neili", me) < 40)
                return notify_fail("你的內力不夠練鷹爪功。\n");
        me->receive_damage("qi", 30);
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
        int d_e1 = 40;
        int d_e2 = 20;
        int p_e1 = -10;
        int p_e2 = -40;
        int f_e1 = 250;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("sougu", 1);
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
                "damage_type" : random(2) ? "抓傷" : "內傷",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"sougu-yingzhua/" + action;
}

int help(object me)
{
        write(HIC"\n搜骨鷹爪功："NOR"\n");
        write(@HELP

    明教白眉鷹王殷天正之絕招，又手似鷹爪，手到擒來。

        學習要求：
                先天膂力24
                基本內功30級
                內力100
HELP
        );
        return 1;
}
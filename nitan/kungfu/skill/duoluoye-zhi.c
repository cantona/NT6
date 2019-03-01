// This program is a part of NT MudLIB
// duoluoye-finger.c 多羅葉指 和大金剛神掌互備 截自佛經中之“欲界諸天”。

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIY"「四天王天」"NOR"，連出四指，帶起空中無限氣勁，一道道地插向$n$l",
        "lvl"   : 0,
        "skill_name" : "四天王天"
]),
([        "action" : "$N面帶笑容使出"HIC"「仞利天」"NOR"，身形微側，手指從袖底穿出，挾一股極利的勁力刺向$n",
        "lvl"   : 20,
        "skill_name" : "仞利天"
]),
([        "action" : "$N一式"HIB"「夜摩天」"NOR"，左掌立刃大開大闔，右手飄忽靈動，忽然一指點出，刺向$n$l！",
        "lvl"   : 40,
        "skill_name" : "夜摩天"
]),
([        "action" : "$N使出一招"CYN"「兜率天」"NOR"，左掌連劈，勁力罩住$n的身子，右手一揮，一指點向$n$l",
        "lvl"   : 60,
        "skill_name" : "兜率天"
]),
([        "action" : "$N雙手抱圓，內力運行，"YEL"「化樂天」"NOR"擊出，一縷指風飛襲$n，看似無力，實是無堅不摧",
        "lvl"   : 80,
        "skill_name" : "化樂天"
]),
([        "action" : "$N向$n連點數指，勁風更激起無數尖嘯之聲，這招"MAG"「他化自在天」"NOR"虛虛實實，防不勝防",
        "lvl"   : 100,
        "skill_name" : "他化自在天"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練多羅葉指必須空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法學習多羅葉指。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練多羅葉指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("duoluoye-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的多羅葉指。\n");

        return 1;
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習。\n");

        if( query("qi", me)<130 )
                return notify_fail("你的體力太低了，無法練多羅葉指。\n");

        if( query("neili", me)<110 )
                return notify_fail("你的內力不夠，無法練多羅葉指。\n");

        me->receive_damage("qi", 110);
        addn("neili", -100, me);
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
        int d_e2 = 60;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 150;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("duoluoye-finger", 1);
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

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"duoluoye-finger/" + action;
}

int help(object me)
{
        write(HIC"\n多羅葉指："NOR"\n");
        write(@HELP

    多羅葉指是南少林的指法，和大金剛神掌互備，出自佛經中之“欲界諸天”。

        學習要求：
                站樁功50級
                波羅蜜手50級
                摩訶指50級
                內力修為500
HELP
        );
        return 1;
}

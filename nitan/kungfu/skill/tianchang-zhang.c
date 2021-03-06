//tianchang-zhang 天長掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使一招"GRN"「青山隱隱」"NOR"，雙手劃了個半圈，按向$n的$l",
        "skill_name" : "青山隱隱",
        "lvl" : 5
]),
([        "action" : "$N使一招"MAG"「雲霞出海」"NOR"，左手輕輕一揮，劈向$n的$l",
        "skill_name" : "雲霞出海",
        "lvl" : 15
]),
([        "action" : "$N右手掌心向外，由右向左，使一招"CYN"「星河鷺起」"NOR"，向$n的$l打去",
        "skill_name" : "星河鷺起",
        "lvl" : 10
]),
([        "action" : "$N使一招"HIM"「彩舟雲淡」"NOR"，分擊$n的胸口和$l",
        "skill_name" : "彩舟雲淡",
        "lvl" : 20
]),
([        "action" : "$N使一招"HIB"「月照幽林」"NOR"，左右掌同時擊出，在空中突然左右掌方向互變",
        "skill_name" : "月照幽林",
        "lvl" : 30
]),
([        "action" : "$N左手不住晃動，右掌一招"HIW"「白日參辰」"NOR"，向$n的$l打去",
        "skill_name" : "白日參辰",
        "lvl" : 50
]),
([        "action" : "$N左手變掌為啄，右掌立掌如刀，一招"HIY"「鶴舞白沙」"NOR"，劈向$n的$l",
        "skill_name" : "鶴舞白沙",
        "lvl" : 70
]),
([        "action" : "$N左腳退後半步，右掌使一招"HIC"「水天一色」"NOR"，橫揮向$n",
        "skill_name" : "水天一色",
        "lvl" : 80
]),
([        "action" : "$N一招"CYN"「月華流照」"NOR"，左掌先發而後至，右掌後發而先至",
        "skill_name" : "月華流照",
        "lvl" : 90
]),
([        "action" : "$N雙掌縮入袖中，雙袖飛起掃向$n的$l，卻是一招"HIR"「嫦娥奔月」"NOR"，儀態瀟灑",
        "skill_name" : "嫦娥奔月",
        "lvl" : 100
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" ; }
int valid_combine(string combo) { return combo == "hujia-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練天長掌法必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法練天長掌法。\n");

        if( query("max_neili", me)<750 )
                return notify_fail("你的內力太弱，無法練天長掌法。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候不夠，無法練習天長掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tianchang-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深天長掌法。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練天長掌。\n");
        me->receive_damage("qi", 35);
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
        int d_e1 = -35;
        int d_e2 = -5;
        int p_e1 = 5;
        int p_e2 = 35;
        int f_e1 = 170;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tianchang-zhang", 1);
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
        return __DIR__"tianchang-zhang/" + action;
}

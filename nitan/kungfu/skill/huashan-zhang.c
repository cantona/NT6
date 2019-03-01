#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N一式「白雲出岫」，雙掌間升起一團淡淡的白霧，緩緩推向$n的$l",
        "force" : 50,
        "dodge" : 5,
        "parry" : 10,
        "damage": 5,
        "lvl" : 0,
        "skill_name" : "白雲出岫",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N並指如劍，一式「白虹貫日」，疾向$n的$l戳去",
        "force" : 60,
        "dodge" : -5,
        "parry" : 15,
        "damage": 5,
        "lvl" : 10,
        "skill_name" : "白虹貫日",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使一式「雲斷秦嶺」，左掌微拂，右掌乍伸乍合，猛地插往$n的$l",
        "force" : 65,
        "dodge" : 5,
        "parry" : 10,
        "damage": 10,
        "lvl" : 20,
        "skill_name" : "雲斷秦嶺",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙掌隱隱泛出青氣，一式「青鬆翠翠」，幻成漫天碧綠的鬆針，雨點般向$n擊去",
        "force" : 70,
        "dodge" : 10,
        "parry" : 20,
        "damage": 15,
        "lvl" : 30,
        "skill_name" : "青鬆翠翠",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形往上一縱，使出一式「天紳倒懸」，雙掌並攏，筆直地向$n的$l插去",
        "force" : 75,
        "dodge" : 15,
        "parry" : 10,
        "damage": 15,
        "lvl" : 40,
        "skill_name" : "天紳倒懸",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形一變，使一式「無邊落木」，雙掌帶著蕭剎的勁氣，猛地擊往$n的$l",
        "force" : 80,
        "dodge" : 15,
        "parry" : 15,
        "damage": 20,
        "lvl" : 50,
        "skill_name" : "無邊落木",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使一式「高山流水」，左掌凝重，右掌輕盈，同時向$n的$l擊去",
        "force" : 85,
        "dodge" : 20,
        "parry" : 15,
        "damage": 20,
        "lvl" : 60,
        "skill_name" : "高山流水",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N突地一招「金玉滿堂」，雙掌挾著一陣風雷之勢，猛地劈往$n的$l",
        "force" : 90,
        "dodge" : 20,
        "parry" : 20,
        "damage": 25,
        "lvl" : 70,
        "skill_name" : "金玉滿堂",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一式「風伴流雲」，雙掌縵妙地一陣揮舞，不覺已擊到$n的$l上",
        "force" : 110,
        "dodge" : 15,
        "parry" : 20,
        "damage": 25,
        "lvl" : 80,
        "skill_name" : "風伴流雲",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一式「煙雨飄渺」，身形凝立不動，雙掌一高一低，看似簡單，卻令$n無法躲閃",
        "force" : 120,
        "dodge" : 25,
        "parry" : 10,
        "damage": 30,
        "lvl" : 90,
        "skill_name" : "煙雨飄渺",
        "damage_type" : "瘀傷"
])
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "huashan-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練華山掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學華山掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練華山掌法。\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("huashan-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的華山掌法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -25;
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 150;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("hunyuan-zhang", 1);
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

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練華山掌法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huashan-zhang/" + action;
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n華山掌："NOR"\n");
        write(@HELP

    華山掌為華山武功。華山掌緣自劍法，固招數名稱多與劍招相
符。
    可與華山拳互備。

        學習要求：
                基本內功20級
                內力100
HELP
        );
        return 1;
}

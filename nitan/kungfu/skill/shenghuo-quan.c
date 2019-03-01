// shenghuo-quan.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N左拳虛晃，右拳若有若無悄然飛出，身形如同微風吹拂下的火燄，徑直襲向$n",
        "force" : 100,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 0,
        "damage" : 20,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙拳齊出，拳風呼嘯，熱浪陣陣，拳勢直指$n的$l",
        "force" : 120,
        "dodge" : -20,
        "parry" : 20,
        "lvl" : 10,
        "damage" : 30,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N下身沉穩，上身卻微伏向前，出拳飄忽，如閃爍的火燄般吞吐不定，無情的擊向$n",
        "force" : 140,
        "dodge" : 30,
        "parry" : -20,
        "lvl" : 20,
        "damage" : 40,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N不進反退，輕輕一拳，出招雖然緩慢，但是炙熱的勁氣卷向$n的$l",
        "force" : 160,
        "dodge" : -50,
        "parry" : -10,
        "lvl" : 30,
        "damage" : 40,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N拳勢大盛，如同風中的篝火，氣燄升騰飄旋，$n只感覺熱浪撲面，拳招從四面八方襲來",
        "force" : 180,
        "dodge" : -30,
        "parry" : 20,
        "lvl" : 40,
        "damage" : 50,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N面色凝重，一拳又一拳突然沉穩無比，雖是劈空而發，拳勁卻如同火球直擊$n的$l",
        "force" : 200,
        "dodge" : 50,
        "parry" : -30,
        "lvl" : 50,
        "damage" : 50,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形急轉，忽左忽右，忽前忽後，拳勁如同升騰的火燄直向$n招呼過去",
        "force" : 220,
        "dodge" : 10,
        "parry" : 10,
        "lvl" : 60,
        "damage" : 60,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N胸口空門大開，狀似破綻，雙拳卻左右圍合，夾帶著滾滾熱浪直擊$n",
        "force" : 250,
        "dodge" : 40,
        "parry" : -10,
        "lvl" : 70,
        "damage" : 60,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N臉露詭異微笑，滿面紅光大盛，單拳擊出，拳勢凌厲，帶著滔天熱浪直向$n的$l撲去",
        "force" : 280,
        "dodge" : -30,
        "parry" : -20,
        "lvl" : 80,
        "damage" : 70,
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="guangming-zhang"; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練聖火拳必須空手。\n");

        if ((int)me->query_skill("cuff", 1) < 10)
                return notify_fail("你的基本拳法火候不夠，無法練聖火拳。\n");


        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("shenghuo-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的聖火拳。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("shenghuo-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)query("qi", me) < 60)
                return notify_fail("你的體力太低了。\n");

        if ((int)query("neili", me) < 70)
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 20);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shenghuo-quan/" + action;
}
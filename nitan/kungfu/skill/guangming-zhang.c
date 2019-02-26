// This program is a part of NT MudLIB
// guangming-zhang.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N雙掌一錯，一招“魔火天焚”幻出漫天掌影攏向$n的$l",
        "force" : 100,
        "dodge" : 5,
        "parry" : 1,
        "lvl" : 0,
        "damage" : 20,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使出一招「聖火小天羅式」，右掌穿出擊向$n的$l",
        "force" : 120,
        "dodge" : -2,
        "parry" : 2,
        "lvl" : 10,
        "damage" : 30,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使出一招「聖火大天羅式」，左掌化虛為實擊向$n的$l",
        "force" : 140,
        "dodge" : 3,
        "parry" : -2,
        "lvl" : 20,
        "damage" : 40,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N使出光明神掌「聖火九轉式」，如鬼魅般欺至$n身前，一掌拍向$n的$l",
        "force" : 160,
        "dodge" : -5,
        "parry" : -1,
        "lvl" : 30,
        "damage" : 40,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙掌一錯，使出「聖火三連飛」，對準$n的$l連續拍出三掌",
        "force" : 180,
        "dodge" : -3,
        "parry" : 2,
        "lvl" : 40,
        "damage" : 50,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左掌畫了個圈圈，右掌推出，一招「焰卷五方鼓」擊向$n$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -3,
        "lvl" : 50,
        "damage" : 50,
        "damage_type" : "瘀傷"
]),
([      "action" :"$N使出「風雷七星斷」，身形散作七處同時向$n的$l出掌攻擊",
        "force" : 220,
        "dodge" : 1,
        "parry" : 1,
        "lvl" : 60,
        "damage" : 60,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N吐氣揚聲，一招「氣撼九重天」雙掌併力推出",
        "force" : 250,
        "dodge" : 4,
        "parry" : -1,
        "lvl" : 70,
        "damage" : 60,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左掌畫了個圈圈，右掌推出，一招「光明鎮四方」擊向$n$l",
        "force" : 280,
        "dodge" : 3,
        "parry" : 2,
        "lvl" : 80,
        "damage" : 70,
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo=="shenghuo-quan"; }

int valid_learn(object me)
{
        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail("練光明神掌必須空手。\n");

        if ((int)me->query_skill("strike", 1) < 10)
                return notify_fail("你的基本掌法火候不夠，無法練光明神掌。\n");


        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("guangming-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的光明神掌。\n");

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
        level = (int)me->query_skill("guangming-zhang", 1);
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
        return __DIR__"guangming-zhang/" + action;
}
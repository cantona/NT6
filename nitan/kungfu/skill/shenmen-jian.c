#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N身形斜飛，手中$w輕輕點向$n的腕部",
        "force"  : 60,
        "dodge"  :-20,
        "parry"  :-10,
        "damage" : 5,
        "damage_type" : "刺傷"
]),
([      "action" : "$N長躍而起，$w猛然下刺，直打$n腕部的神門穴",
        "force"  : 74,
        "dodge"  :-25,
        "parry"  :-13,
        "damage" : 9,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w自上而下反刺，模擬冰輪橫空、清光舖地的光景",
        "force"  : 86,
        "attack" : 27,
        "dodge"  :-15,
        "parry"  :-17,
        "damage" : 17,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w顫動來回揮削，只幌得$n眼花撩亂，渾不知從何攻來",
        "force"  : 89,
        "attack" : 31,
        "dodge"  :-25,
        "parry"  :-25,
        "damage" : 21,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w由內自外一刺，左手虛擊，身形一晃，$w已搭在$n腕部",
        "force"  : 107,
        "attack" : 38,
        "dodge"  :-30,
        "parry"  :-35,
        "damage" : 29,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左掌橫擺胸前，右手中$w輕輕揮拂，直取$n的神門要穴",
        "force"  : 130,
        "attack" : 29,
        "dodge"  :-35,
        "parry"  :-37,
        "damage" : 28,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w中宮直入，攜著強大的勁道攻向$n的$l",
        "force"  : 160,
        "attack" : 42,
        "dodge"  :-45,
        "parry"  :-40,
        "damage" : 39,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候不到，無法學習神門十三劍。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力太差，無法學習神門十三劍。\n");

        if (me->query_skill("sword", 1) < me->query_skill("shenmen-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的神門十三劍。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("shenmen-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        weapon=query_temp("weapon", victim);

        if( !query_temp("weapon", victim )
           || ! living(victim)
           || query("max_neili", me)<query("max_neili", victim )
           || damage_bonus < 100
           || query("neili", me)<500
           || me->query_skill("shenmen-jian", 1) < 80
           || random(2) == 1)
                return 0;

        if( !victim->is_busy() )
                victim->start_busy(2);
        victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
        weapon->move(environment(victim));

        return HIW "突然間$n" HIW "被$N" HIW "一劍刺中神門要穴，手中" +
               weapon->name() + HIW "再也抓拿不住，不禁脫手飛出。\n" NOR;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<65 )
                return notify_fail("你的體力不夠練神門十三劍。\n");

        if( query("neili", me)<65 )
                return notify_fail("你的內力不足以練神門十三劍。\n");

        me->receive_damage("qi", 52);
        addn("neili", -58, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shenmen-jian/" + action;
}

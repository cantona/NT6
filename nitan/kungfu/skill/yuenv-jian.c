// yuenv-jian.c 越女劍術
// Modify by Rcwiz for hero.cd

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N手中$w輕輕點向$n的$l，迅疾無比",
        "force"  : 100,
        "attack" : 130,
        "dodge"  : 120,
        "parry"  : 12,
        "damage" : 70,
        "lvl"    : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N長躍而起，手中的$w挽了一個劍花，猛然刺向$n",
        "force"  : 120,
        "attack" : 140,
        "dodge"  : 125,
        "parry"  : 15,
        "damage" : 84,
        "lvl"    : 20,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出回身側步，手中的$w斜刺$n的$l",
        "force"  : 140,
        "attack" : 140,
        "dodge"  : 130,
        "parry"  : 10,
        "damage" : 100,
        "lvl"    : 50,
        "damage_type" : "內傷"
]),
([      "action" : "$N卻身提步，手中的$w似擋飛擋，似進非進，忽的直刺$n",
        "force"  : 160,
        "attack" : 160,
        "dodge"  : 138,
        "parry"  : 10,
        "damage" : 110,
        "lvl"    : 75,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w顫動的極快，只幌得$n眼花撩亂，渾不知從何攻來",
        "force"  : 180,
        "attack" : 180,
        "dodge"  : 145,
        "parry"  : 12,
        "damage" : 125,
        "lvl"    : 100,
        "damage_type" : "內傷"
]),
([      "action" : "$N劍柄提起，劍尖下指，有如提壺斟酒，直揮$n的$l",
        "force"  : 200,
        "attack" : 185,
        "dodge"  : 150,
        "parry"  : 18,
        "damage" : 130,
        "lvl"    : 130,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w由內自外一刺，沒有任何花巧，然而來是快得不可思議",
        "force"  : 220,
        "attack" : 210,
        "dodge"  : 155,
        "parry"  : 15,
        "damage" : 140,
        "lvl"    : 160,
        "damage_type" : "刺傷"
]),
([      "action" : "$N輕嘆一聲，手中的$w化作一到長弧點向$n",
        "force"  : 240,
        "attack" : 230,
        "dodge"  : 170,
        "parry"  : 22,
        "damage" : 150,
        "lvl"    : 200,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一抖手中的$w，挽出數個劍花，籠罩了$n",
        "force"  : 260,
        "attack" : 250,
        "dodge"  : 185,
        "parry"  : 25,
        "damage" : 155,
        "lvl"    : 225,
        "damage_type" : "刺傷"
]),
([  "action" : "$N一聲輕笑，手中$w幻化作滿天星點，不知刺向$n的何處",
        "force"  : 320,
        "attack" : 280,
        "dodge"  : 220,
        "parry"  : 30,
        "damage" : 180,
        "lvl"    : 250,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{

        if( query("gender", me) != "女性" )
                return notify_fail("你練來練去覺得這個劍法還是適合女性練習！\n");

        if( query("dex", me)<13 )
                return notify_fail("你先天身法不足，無法修煉越女劍術。\n");

        if ((int)me->query_skill("dodge", 1) < 200)
                return notify_fail("你的輕功火候不到，無法運用越女劍術。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的劍術功底不行，難以領會越女劍術。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太差，無法學習越女劍術。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuenv-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的越女劍術。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yuenv-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練越女劍術。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不足以練越女劍術。\n");

        me->receive_damage("qi", 64);
        addn("neili", -65, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;
        int ap, dp;

        weapon=query_temp("weapon", me);

        attack_time = (int)(me->query_skill("yuenv-jian", 1) / 40);

        if (attack_time > 7)
                attack_time = 7;

        ap = me->query_skill("sword"); 
        dp = victim->query_skill("dodge");

        if (me->is_busy()
           || ! living(victim)
            || query("neili", me)<200
           || ap * 3 / 5 + random(ap) < dp
            || query_temp("is_attacking", me )
           || me->query_skill_mapped("sword") != "yuenv-jian"
           || me->query_skill("yuenv-jian", 1) < 120)
                return 0;
        
        message_vision(HIW "\n霎那間，只見$N" HIW "手中" + weapon->name() + HIW "輕盈靈動"
                       "，優美華麗，不帶一絲塵俗之氣，卻將$n" HIW "攻得無暇反擊！\n"
                       NOR, me, victim);

        set_temp("is_attacking", 1, me);
        me->start_busy(1 + random(attack_time / 2));
        addn("neili", -attack_time*20, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        delete_temp("is_attacking", me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuenv-jian/" + action;
}

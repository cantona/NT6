#include <ansi.h>
inherit SHAOLIN_SKILL;

mapping *action = ({
([        "action" : "$N一聲大喝，左掌疊于右掌之上，劈向$n",
        "force" : 210,
        "attack": 22,
        "dodge" : 30,
        "parry" : 31,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "內傷"
]),
([        "action" : "$N面色凝重，雙掌輕抖，飄忽不定地拍向$n",
        "force" : 270,
        "attack": 38,
        "dodge" : 25,
        "parry" : 33,
        "damage": 30,
        "lvl"   : 20,
        "damage_type" : "內傷"
]),
([        "action" : "$N氣沉丹田，雙掌幻化一片掌影，將$n籠罩于內。",
        "force" : 320,
        "attack": 62,
        "dodge" : 43,
        "parry" : 44,
        "damage": 35,
        "lvl"   : 40,
        "damage_type" : "內傷"
]),
([        "action" : "$N跨前一步，右掌中攻直進，向$n的$l連擊三掌",
        "force" : 370,
        "attack": 75,
        "dodge" : 55,
        "parry" : 68,
        "damage": 50,
        "lvl"   : 60,
        "damage_type" : "內傷"
]),
([        "action" : "$N沉身頓氣，貫出雙掌，頓時只見一片掌影攻向$n",
        "force" : 420,
        "attack": 82,
        "dodge" : 52,
        "parry" : 80,
        "damage": 30,
        "lvl"   : 80,
        "damage_type" : "內傷"
]),
([        "action" : "$N雙掌平揮，猛擊向$n的$l，毫無半點花巧可言",
        "force" : 460,
        "attack": 103,
        "dodge" : 65,
        "parry" : 101,
        "damage": 50,
        "lvl"   : 100,
        "damage_type" : "內傷"
]),
([        "action" : "$N體內真氣迸發，雙掌繽紛拍出，頓時一片掌影籠罩$n",
        "force" : 510,
        "attack": 128,
        "dodge" : 63,
        "parry" : 125,
        "damage": 80,
        "lvl"   : 120,
        "damage_type" : "內傷"
]),
([        "action" : "$N左掌虛晃，右掌攜著千鈞之力猛然向$n的頭部擊落",
        "force" : 530,
        "attack": 125,
        "dodge" : 77,
        "damage": 90,
        "parry" : 152,
        "lvl"   : 140,
        "damage_type" : "內傷"
]),
([        "action" : "$N身子驀的橫移，右手橫掃$n的$l，左手攻向$n的胸口",
        "force" : 580,
        "attack": 131,
        "dodge" : 80,
        "parry" : 115,
        "damage": 100,
        "lvl"   : 160,
        "damage_type" : "內傷"
]),
([        "action" : "$N陡然一聲暴喝，真氣迸發，雙掌同時擊向$n的$l",
        "force" : 620,
        "attack": 132,
        "dodge" : 81,
        "parry" : 123,
        "damage": 130,
        "lvl"   : 180,
        "damage_type" : "內傷"
])
});

int valid_enable(string usage)
{
        return usage == "parry" || usage == "strike";
}

int double_attack()
{
        return 1;
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練千手如來掌必須空手。\n");

        if( query("str", me)<26 )
                return notify_fail("你先天膂力不足，無法學習淳厚的古拙掌法。\n");

        if ((int)me->query_skill("buddhism", 1) < 300)
                return notify_fail("你的禪宗心法不夠，無法練千手如來掌。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，無法練千手如來掌。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為太淺，無法練千手如來掌。\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("你的基本掌法火候不夠，無法練千手如來掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("rulai-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的千手如來掌。\n");

        return 1;
}

mixed hit_ob(object me, object victim, int i, int damage_bonus)
{
        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || victim->is_busy()
           || damage_bonus < 150
            || query("neili", me)<600
            || query_temp("action_flag", me) == 0
           || me->query_skill("buddhism", 1) < 300
           || me->query_skill("rulai-zhang", 1) < 180)
                return 0;

        // 避免在使用Pfm時訊息重復
        if( !query_temp("rulai-zhang/hit_msg", me) )
                message_sort(HIY "\n$N" HIY "忽然喝道：「" HIR + RANK_D->query_respect(victim) +
                             HIR "，接" + RANK_D->query_self(me) + HIR "一掌。" HIY "」說罷輕飄"
                             "飄拍出一掌，招式甚為尋常。但掌到中途，忽然微微搖晃，登時一掌變兩"
                             "掌，兩掌又變四掌，四勢連環，盡數籠罩$n" HIY "周身。\n",
                             me, victim);

        me->start_busy(1 + random(3));
        addn("neili", -200, me);

        for (i = 0; i < 4; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, 0, 20);
        }

        if (damage_bonus / 6 > victim->query_con())
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 120) / 2, me);
                return random(2) ? HIR "$n" HIR "被$N" HIR "凌厲的掌風劃中氣門，只"
                                   "感內息窒滯，“哇”的噴出一口鮮血！\n" NOR:

                                   HIR "$N" HIR "一掌拍出，只聽$n" HIR "胸前“喀嚓"
                                   "喀嚓”幾聲脆響，竟似斷了數根肋骨！\n" NOR;
        }

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("rulai-zhang", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<200 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<220 )
                return notify_fail("你的內力不夠練千手如來掌。\n");

        me->receive_damage("qi", 180);
        addn("neili", -200, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"rulai-zhang/" + action;
}
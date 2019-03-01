// This program is a part of NITAN MudLIB
// youming-guizhao.c 幽冥鬼爪

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N左爪前伸，帶著絲絲藍陰鬼氣，一式「元神出竅」，猛得向$n的頂門插下",
        "$N雙掌連拍，築起一道氣牆推向$n，忽然一爪「鬼魅穿心」沖破氣牆直插$n的$l",
        "$N使出「血鬼鎖」雙爪遊向$n扣住$l，氣勁激發往左右兩下一拉，便要將$n割成碎片",
        "$N雙爪攏住$n，使一式「煉獄鬼嚎」，陰毒內功隨爪尖透入$n體內，直襲各大關節",
        "$N力透指尖，向$n虛虛實實連抓十五爪，「妖風襲體」帶動無數陰氣纏住$n",
        "$N一式「索命妖手」，左爪上下翻動形成無數爪影，右臂一伸，鬼魅般抓向$n的$l",
        "$N探手上前，順著$n的手臂攀緣直上，變手為爪，一招「孤魂馭魔」抓向$n的$l",
        "$N凌空飛落，一爪突前，「魔爪天下」積聚全身功力于指尖，快絕無比地插向$n",
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
       if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
               return notify_fail("練爪功必須空手。\n");
       if ((int)me->query_skill("claw", 1) < 50)
               return notify_fail("你的基本爪功火候不夠，無法學習。\n");
       if( query("max_neili", me)<1000 )
               return notify_fail("你的內力太弱，無法練幽冥鬼爪。\n");
       return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 320 + random(60),
                "attack": 70 + random(10),
                "dodge" : -70 + random(10),
                "parry" : -70 + random(10),
                "damage_type" : "抓傷",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query_skill("youming-guizhao", 1) < 199 )
                return notify_fail("你的幽冥鬼爪修為不夠，只能用學(learn)的來增加熟練度。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練幽冥鬼爪必須空手。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練幽冥鬼爪。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"youming-guizhao/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( query_temp("lingjiu/youming", me )
         && !query_temp("youming_hit", me) )
        {
                set_temp("youming_hit", 1, me);
                set_temp("apply/name", ({query("name", me)+"的鬼影"}), me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                delete_temp("apply/name", me);
                delete_temp("youming_hit", me);
        }
}

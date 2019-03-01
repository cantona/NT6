// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;


string *action_msg = ({
        "$N輕撫手中的$w，突然間只見刀光一閃，再閃，又一閃！三道刺骨的寒氣已然襲上了$n的$l",
        "只見$N倒提$w，身形急沖，就在與$n錯身之際，突然反手一刀從$n後腦斜劈而下",
        "$N斜身飛起，帶出一片匹練也似的刀光卷向$n的$l",
        "$N突然一腳踢出，手中的$w劃出一道輕妙的圓弧，淡淡的刀光封住了$n的頭臉，切斷了$n的呼吸",
        "只見$N臉色一寒，一招「千裡冰封」使出，從眉捷到腳跟，\n$n周身的血液都似被這無盡的刀勢凍住，而生命也仿佛要離體而去",
        "$N刀勢漸慢，而$w上帶出的寒氣卻越來越濃。就在這時，\n$n的心頭一緊，一道比針尖還要銳利的寒氣已刺上了$n$l",
        "$N也不管三七二十一，高舉$w呼！地就是一刀向$n迎面斬下！\n雖然只有一刀，可怕的刀勢卻似萬古不化的寒冰封死了$n的一切退路",
});


int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠，沒有辦法練冰魄寒刀，多練些內力再來吧。\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "blade"
         || query("material", ob) != "ice" )
                return notify_fail("你必須先找一把冰做的刀才能練冰魄寒刀。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 260 + random(30),
                "dodge" : -60 + random(10),
                "parry" : -60 + random(10),
                "damage_type" : random(2) ? "挫傷" : "割傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<110
             || query("neili", me)<110 )
                return notify_fail("你的內力或氣不夠，沒有辦法練習冰魄寒刀。\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        write("你按著所學練了一遍冰魄寒刀。\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon=query_temp("weapon", me);
        string msg;

        if (( damage_bonus > 250 ) && (! userp(me)))
                return 0;

        if (((int)me->query_skill("blade", 1)/2) > random((int)victim->query_skill("force", 1)))
        {
                victim->receive_wound("qi", (300-damage_bonus));
                msg = HIW "$N默運真氣，將冰魄寒刀中寒氣逼出，$n一個不察，已被凍傷！\n\n"NOR;
                message_combatd(msg, me, victim);

        }
        switch(random(3)) {
        case 0:
                victim->receive_damage("qi",damage_bonus/3*2);
                msg = "只見一絲寒氣無聲無息地鑽到$n體內！\n";
                break;

        case 1:
                victim->receive_damage("qi",damage_bonus/2);
                msg = "$N暗使巧力，在$n的傷口上留下一道淺淺的白印！\n";
                break;

        case 2:
                victim->receive_damage("qi",damage_bonus);
                msg = "$n突然覺得體內奇寒難忍...\n";
                break;
        }

        return msg;
}
string perform_action_file(string action)
{
        return __DIR__"bingpo-blade/" + action;

}



// 五鬥米神功 shenzhaojing.c
// Editd By Vin On 1/7/2001

#include <ansi.h>
inherit FORCE;

int valid_force(string force) { return 1; }
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("wudoumi-shengong", 1);
        return lvl * lvl * 15 * 10 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N提運五鬥米神功，呼的撲向$n，待至跟前，陡然一拳擊向$n面門",
        "dodge"  : 31,
        "force"  : 323,
        "attack" : 89,
        "parry"  : 34,
        "damage" : 58,
        "lvl"    : 0,
        "damage_type": "內傷" 
]), 
([      "action" : "$N絲毫不動聲色，右掌平伸，左掌運起五鬥米神功的勁力，呼的一聲拍向$n",
        "dodge"  : 43,
        "force"  : 362,
        "attack" : 103,
        "parry"  : 47,
        "damage" : 63,
        "lvl"    : 160,
        "damage_type": "內傷"
]), 
([      "action" : "$N身形微微一展，一雙手掌便似滲出血一般，雙掌齊施，猛拍$n前胸",
        "dodge"  : 48,
        "force"  : 413,
        "attack" : 122,
        "parry"  : 51,
        "damage" : 75,
        "lvl"    : 180,
        "damage_type": "內傷"
]),
([      "action" : "$N一聲呼嘯，雙掌回收，凌空劃出一個圓圈，頓時一股熱浪直湧$n而出",
        "dodge"  : 41,
        "force"  : 451,
        "attack" : 113,
        "parry"  : 47,
        "damage" : 83,
        "lvl"    : 200,
        "damage_type": "內傷"
]), 
});

int valid_enable(string usage)
{ 
        object me = this_player();

        if( query("can_perform/wudoumi-shengong/gui", me) )
                return usage == "force" || usage=="unarmed" || usage =="parry";
        else
                return usage == "force";
       
}

int valid_learn(object me)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "國士無雙" )
                return notify_fail("你暗想這五鬥米神功損人不利己，修來何用？\n");

        if( query("con", me)<24 )
                return notify_fail("你按照法門運轉了下內息，忽然只覺丹田一陣攪疼。\n");

/*
        因考慮五鬥米神功的反噬情況，無玄門正宗的內功不能修煉高，所以暫
        時設為可以與辟邪劍法所共存的內功，如有不妥再作改正。

        if( query("gender", me) == "無性" && query("wudoumi-shengong",1, me)>29 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的五鬥米神功。\n");
*/

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的基本內功火候不足，不能學五鬥米神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 50)
                return notify_fail("你的基本拳腳火候不足，不能學五鬥米神功。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不足，不能學五鬥米神功。\n");

        if (me->query_skill("force", 1) < me->query_skill("wudoumi-shengong", 1))
                return notify_fail("你的基本內功水平不夠，難以鍛煉更深厚的五鬥米神功。\n");

        if( query("can_perform/wudoumi-shengong/gui", me )
           && me->query_skill("unarmed", 1) < me->query_skill("wudoumi-shengong", 1))
                return notify_fail("你的基本拳腳水平不夠，難以鍛煉更深厚的五鬥米神功。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("wudoumi-shengong", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

int practice_skill(object me)
{
        return notify_fail("五鬥米神功只能用學(learn)的來增加熟練度。\n");
}

void check_count(object me)
{
        if( query("max_neili", me) >= 3000 && 
            query("exception/wudoumi-count", me)>1000 )
        {
                me->apply_condition("wudoumi-fanshi",
                        me->query_condition("wudoumi-fanshi") +
                        query("exception/wudoumi-count", me)/10);
                delete("exception/wudoumi-count", me);
        }
}

void skill_improved(object me)
{
        int level = (int)me->query_skill("wudoumi-shengong", 1);

        addn("exception/wudoumi-count", level+1, me);
        check_count(me);
}

int difficult_level()
{
        return 600;
}

string perform_action_file(string action)
{
        return __DIR__"wudoumi-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"wudoumi-shengong/exert/" + action;
}

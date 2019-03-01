// 血刀大法 xuedao-dafa.c
// Editd By Vin On 1/9/2001

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
        return force == "longxiang" ||
               force == "xiaowuxiang" ||
               force == "mizong-neigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xuedao-dafa", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N高舉手中$w，使出一招「磨牙吮血」，一刀斜劈$n的$l",
        "force"  : 210,
        "attack" : 20,
        "dodge"  : 30,
        "parry"  : 25,
        "lvl"    : 0,
        "damage" : 100,
        "skill_name"  : "磨牙吮血",
        "damage_type" : "割傷",
]),
([      "action" : "$N就地一滾，使一招「刺血滿地」，手中$w卷向$n的大腿",
        "force"  : 240,
        "attack" : 25,
        "dodge"  : 45,
        "parry"  : 35,
        "lvl"    : 140,
        "damage" : 120,
        "skill_name"  : "刺血滿地",
        "damage_type" : "割傷",
]),
([      "action" : "$N足尖一點，使出「血海茫茫」，刀鋒自上而下直插$n的$l",
        "force"  : 280,
        "attack" : 40,
        "dodge"  : 52,
        "parry"  : 40,
        "lvl"    : 160,
        "damage" : 130,
        "skill_name"  : "血海茫茫",
        "damage_type" : "割傷",
]),
([      "action" : "$N使出一招「嘔心瀝血」，將$w舞得如白霧一般壓向$n",
        "force"  : 320,
        "attack" : 45,
        "dodge"  : 58,
        "parry"  : 42,
        "lvl"    : 180,
        "damage" : 140,
        "skill_name"  : "嘔心瀝血",
        "damage_type" : "割傷",
]),
([      "action" : "$N低吼一聲，使出「血口噴人」，舉$w直劈$n的$l",
        "force"  : 340,
        "attack" : 50,
        "dodge"  : 65,
        "parry"  : 45,
        "lvl"    : 200,
        "damage" : 150,
        "skill_name"  : "血口噴人",
        "damage_type" : "割傷",
]),
([      "action" : "$N使出「血跡斑斑」，飛身斜刺，忽然反手一刀橫斬$n的腰部",
        "force"  : 360,
        "attack" : 55,
        "dodge"  : 70,
        "parry"  : 60,
        "lvl"    : 220,
        "damage" : 160,
        "skill_name"  : "血跡斑斑",
        "damage_type" : "割傷",
]),
([      "action" : "$N使一式「以血還血」，揮刀直指$n的胸口",
        "force"  : 390,
        "attack" : 60,
        "dodge"  : 80,
        "parry"  : 55,
        "lvl"    : 240,
        "damage" : 170,
        "skill_name"  : "以血還血",
        "damage_type" : "割傷",
]),
([      "action" : "$N刀鋒虛點，使出一招「血流滿面」，轉身舉$w橫劈$n的面門",
        "force"  : 420,
        "attack" : 70,
        "dodge"  : 90,
        "parry"  : 60,
        "lvl"    : 260,
        "damage" : 185,
        "skill_name"  : "血流漫面",
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage)
{ 
        int lvl;
        lvl = (int)this_player()->query_skill("xuedao-dafa", 1);

        if (lvl >= 120)
                return usage == "force" || usage == "blade" || usage == "parry";
        else
                return usage == "force";
       
}

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" || 
           query("character", me) == "狡黠多變" )
                return notify_fail("你心中暗道：這血刀大法邪氣太重，甚過詭異，莫"
                                   "不是專門設來害人的？\n");

        if( query("str", me)<28 )
                return notify_fail("你先天膂力孱弱，無法修煉血刀大法。\n");

        if( query("dex", me)<26 )
                return notify_fail("你先天身法太差，無法修煉血刀大法。\n");

        if( query("gender", me) == "無性" && query("xuedao-dafa", me)>29 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的血刀大法。\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的基本內功火候不足，不能學血刀大法。\n");

        if( query("max_neili", me)<1600 )
                return notify_fail("你的內力修為不足，不能學血刀大法。\n");

        if (me->query_skill("force", 1) < me->query_skill("xuedao-dafa", 1))
                return notify_fail("你的基本內功水平不夠，難以鍛煉更深厚的血刀大法。\n");

        if (me->query_skill("xuedao-dafa", 1) > 120 &&
           me->query_skill("blade", 1) < me->query_skill("xuedao-dafa", 1))
                return notify_fail("你的基本刀法水平不夠，難以鍛煉更深厚的血刀大法。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuedao-dafa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

int practice_skill(object me)
{
        return notify_fail("血刀大法只能用學(learn)的來增加熟練度。\n");
}

int difficult_level()
{
        return 400;
}

string perform_action_file(string action)
{
        return __DIR__"xuedao-dafa/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"xuedao-dafa/exert/" + action;
}

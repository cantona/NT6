#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N劍勢忽緩而不疏，劍意有余而不盡，化恆山劍法為一劍，向$n慢慢推去",
        "force" : 20,
        "attack": 65,
        "dodge" : 65,
        "parry" : 60,
        "damage": 25,
        "lvl" : 21,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍意突煥氣象森嚴，便似千軍萬馬奔馳而來，劍勢擊向$n",
        "force" : 20,
        "attack": 70,
        "dodge" : 60,
        "parry" : 65,
        "damage": 30,
        "lvl" : 28,
        "damage_type" : "刺傷"
]),
([      "action" : "$N滿場遊走，東刺一劍，西刺一劍，令$n莫明其妙，分不出$N劍法的虛實",
        "force" : 180,
        "attack": 100,
        "dodge" : 70,
        "parry" : 105,
        "damage": 130,
        "lvl" : 105,
        "damage_type" : "刺傷"
]),
([      "action" : "$N抱劍旋身，轉到$n身後，雜亂無章地向$n刺出一劍，不知使的是什麼劍法",
        "force" : 210,
        "attack": 110,
        "dodge" : 75,
        "parry" : 95,
        "damage": 140,
        "lvl" : 112,
        "damage_type" : "刺傷"
]),
([      "action" : "$N突然一劍點向$n的$l，雖一劍卻暗藏無數後著，$n手足無措，不知如何是好",
        "force" : 230,
        "attack": 115,
        "dodge" : 90,
        "parry" : 95,
        "damage": 150,
        "lvl" : 119,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍挾刀勢，大開大闔地亂砍一通，但招招皆擊在$n攻勢的破綻，迫得$n不得不守",
        "force" : 250,
        "attack": 120,
        "dodge" : 95,
        "parry" : 95,
        "damage": 160,
        "lvl" : 126,
        "damage_type" : "刺傷"
]),
([      "action" : "$N反手橫劍刺向$n的$l，這似有招似無招的一劍，威力竟然奇大，$n難以看清劍招來勢",
        "force" : 270,
        "attack": 125,
        "dodge" : 85,
        "parry" : 95,
        "damage": 170,
        "lvl" : 133,
        "damage_type" : "刺傷"
]),
([      "action" : "$N舉劍狂揮，迅速無比地點向$n的$l，卻令人看不出其所用是什麼招式",
        "force" : 300,
        "attack": 130,
        "dodge" : 115,
        "parry" : 80,
        "damage": 180,
        "lvl" : 140,
        "damage_type" : "刺傷"
]),
([      "action" : "$N隨手一劍指向$n，落點正是$n的破綻所在，端的是神妙無倫，不可思議",
        "force" : 330,
        "attack": 140,
        "dodge" : 95,
        "parry" : 100,
        "damage": 190,
        "lvl" : 147,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練御劍術。\n");

        if( query("int", me)<35 )
                return notify_fail("你的天資不足，無法理解御劍術的劍意。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yujian-shu", 1))
                return notify_fail("你的基本劍法造詣有限，無法理解更高深的御劍術。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("御劍術無法通過簡單的練習來提高。\n");
}

string perform_action_file(string action)
{
        return __DIR__"yujian-shu/" + action;
}

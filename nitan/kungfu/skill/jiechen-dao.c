// jiechen-dao.c 戒塵刀
// by gladiator
#include <ansi.h>
inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$N內息轉動，運勁于單刀，全身骨節一陣暴響，起手一式「示誕生」向$n劈出，將$n全身籠罩在赤熱的刀風下",
        "skill_name" : "示誕生",
        "force" : 300,
        "lvl" : 0,
        "dodge" : 15,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N面帶輕笑，一招「始心鏡」，火燄刀內勁由內及外慢慢湧出，$P雙掌如寶像合十于胸前，向著$n深深一鞠",
        "skill_name" : "始心鏡",
        "force" : 350,
        "lvl" : 20,
        "dodge" : 10, 
        "damage_type" : "震傷",
]),
([      "action" : "$N刀掌相合又打開，這招「現寶蓮」以火燄刀無上功力聚出一朵紅蓮，盛開的花瓣飛舞旋轉，漫布在$n四周",
        "skill_name" : "現寶蓮",
        "force" : 400,
        "lvl" : 50,
        "dodge" : 5,
        "weapon" : "紅蓮刀氣",
        "damage_type" : "割傷",
]),
([      "action" : "$N面帶金剛相，刀氣搓圓，使無數炙熱的刀氣相聚，這招「破法執」猶如一只巨大的飛鷹，凌空向$n飛抓而下",
        "skill_name" : "破法執",
        "force" : 340,
        "lvl" : 70,
        "dodge" : 1,
        "damage_type" : "內傷",
]),
([      "action" : "$N暴喝一聲，竟然使出伏魔無上的「開顯圓」，氣浪如颶風般圍著$P飛旋，炎流將$n一步步向著$P拉扯過來",
        "skill_name" : "開顯圓",
        "force" : 450,
        "lvl" : 120,
        "dodge" : -10,
        "damage_type" : "震傷",
]),
([      "action" : "$N口念伏魔真經，鋼刀連連劈出，將$n籠罩在炙燄之下，這如刀切斧鑿般的「顯真常」氣浪似乎要將$p從中劈開",
        "skill_name" : "顯真常",
        "force" : 380,
        "lvl" : 140,
        "dodge" : -5, 
        "weapon" : "無形刀氣",
        "damage_type" : "割傷",
]),
([      "action" : "$N現寶相，結迦蘭，右手「歸真法」單刀揮出，半空中刀氣凝結不散，但發出炙灼的氣浪卻排山倒海般地湧向$n",
        "skill_name" : "歸真法",
        "force" : 450,
        "lvl" : 160,
        "dodge" : -15, 
        "damage_type" : "瘀傷",
]),
([      "action" : "$N虛托刀柄，一式「吉祥逝」，內力運轉，跟著全身衣物無風自動，$P身體微傾，閃電一刀，斬向$n$",
        "skill_name" : "吉祥逝",
        "force" : 500,
        "lvl" : 180,
        "dodge" : 5, 
        "weapon" : "無形氣浪",
        "damage_type" : "割傷",
]),
});

 
        int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
        if( query("max_neili", me)<2500 )
                return notify_fail("以你的內力修為，還不足以練習戒塵刀。\n");
        if ((int)me->query_con() < 32) 
                return notify_fail("你的根骨太低，不能駕御戒塵刀。\n");
        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你基本內功不足。\n");
        if ((int)me->query_skill("force") < 260)
                return notify_fail("你的內功修為太淺，不能學戒塵刀。\n");

        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiechen-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

      if( !objectp(weapon=query_temp("weapon", me)) || 
          query("skill_type", weapon) != "blade" )
                return notify_fail("你先找把刀再說吧！\n");

        if( query("jingli", me)<70 || query("neili", me)<50 )
                return notify_fail("你的體力不夠，練不了戒塵刀。\n");
        addn("jingli", -60, me);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiechen-dao/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( query("blade", me) == me->query_skill("force",1 )
          && me->query_skill_mapped("blade") == "jiechen-dao")
             set_temp("xiuluo", 1, me);
}

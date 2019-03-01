#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N縱身輕輕躍起，一式「修羅道」，劍光如輪疾轉，霍霍斬向$n的$l",
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "lvl"   : 300,        
        "skill_name" : "修羅道",
        "damage_type": "割傷"
]),
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{

        // 與12T沖突
        if( me->query_skill("yinyang-shiertian",1) && !query("thborn/ok", me) )
                return notify_fail("你感覺體內的陰陽九轉真氣跌宕起伏，似乎容納這種技能。\n");
                
        if( query("str", me)<32 )
                return notify_fail("你先天臂力不足。\n");

        if( query("int", me)<32 )
                return notify_fail("你先天悟性不足。\n");

        if( query("dex", me)<32 )
                return notify_fail("你先天身法不足。\n");
                
        if( query("con", me)<32 )
                return notify_fail("你先天根骨不足。\n");                        
                
        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠，難以修煉修羅道。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候太淺，難以修煉修羅道。\n");

        if ((int)me->query_skill("sword", 1) < 300)
                return notify_fail("你的劍法根基不足，難以修煉修羅道。\n");
    
        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你的武學修養不足，難以修煉修羅道。\n");
                    
        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("你的禪宗心法修為不足，難以修煉修羅道。\n");
                                            
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xiuluodao", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的修羅道。\n");
                                                                
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xiuluodao", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if (me->query_skill("xiuluodao", 1) > 180)
                return notify_fail("修羅道博大精深，無法簡單的通過練習進步。\n");

        return 1;
}

int difficult_level()
{
        return 30000;
}

string main_skill() { return "lunhui-sword"; } 
//    /kungfu/skill/suixing-tui.c 如影隨形腿

#include <ansi.h>
inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$N縱身向前，忽然伸出左腿，一式「仗義執言」，直踢$n的頭部",
        "force" : 200,
        "dodge" : 0,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "仗義執言",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形一閃，雙足點地，一式「七星伴月」，在空中連踢七腳，直本$n的頭、胸、臂",
        "force" : 250,
        "dodge" : 10,
        "parry" : -10,
        "lvl" : 40,
        "skill_name" : "七星伴月",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身體前傾，左腳畫圓，右腿使出一式「佛界無邊」，掃向$n的腰部",
        "force" : 300,
        "dodge" : -10,
        "parry" : 5,
        "lvl" : 80,
        "skill_name" : "佛界無邊",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左足倏地彈出，連環六腿，分踢$n的頭部，胸部和襠部，正是一式「轉世輪回」",
        "force" : 350,
        "dodge" : 10,
        "parry" : 0,
        "lvl" : 120,
        "skill_name" : "轉世輪回",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左足獨立，右腿隨身形反轉橫掃，一招「西天極樂」，踢向$n的$l",
        "force" : 400,
        "dodge" : -10,
        "parry" : 0,
        "lvl" : 150,
        "skill_name" : "西天極樂",
        "damage_type" : "瘀傷"
]),                                                   
([      "action" : "$N躍起在半空，雙足帶起無數勁風，一式「佛祖慈悲」迅捷無倫地卷向$n",
          "force" : 450,
        "dodge" : 5,
        "parry" : -10,
        "lvl" : 180,
        "skill_name" : "佛祖慈悲",
        "damage_type" : "瘀傷"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry" || usage=="dodge"; }


int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學如影隨形腿時手裡不能拿武器。\n");
           if (me->query_skill("force", 1) < 150)
                return notify_fail("你的內功火候不夠，無法學如影隨形腿。\n");
        if ((int)me->query_int() > 30)
                return 1;
        
        if( query("max_neili", me)<600 )
                return notify_fail("你的內力太弱，無法練如影隨形腿。\n");
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
        string msg;
        level   = (int) me->query_skill("ruying-suixingtui",1);
        
        if( query_temp("sl_rysxt", me)){
                    switch(query_temp("sl_rysxt", me)){
                           case 5: msg = HIY"$N忽然躍起，左腳一勾一彈，霎時之間踢出一招「如」字訣的穿心腿，直襲$n前胸"NOR; break;
                           case 4: msg = HIY"緊接著$N左腿勾回，將腰身一扭，那右腿的一招「影」字訣便緊隨而至，飛向$n"NOR; break;
                           case 3: msg = HIY"只見$N右腳勁力未消，便凌空一轉，左腿順勢掃出一招「隨」字訣，如影而至"NOR; break;
                           case 2: msg = HIY"半空中$N腳未後撤，已經運起「形」字訣，內勁直透腳尖，在$n胸腹處連點了數十下"NOR; break;
                           case 1: msg = HIR"這時$N雙臂展動，帶起一股強烈的旋風，雙腿霎時齊並，「如影隨形」一擊重炮轟在$n胸堂之上"NOR; break;
                           default: msg = HIY"$N忽然躍起，左腳一勾一彈，霎時之間踢出一招「如」字訣的穿心腿，直襲$n前胸"NOR; break;
                }    
                    addn_temp("sl_rysxt", -1, me);
                    return([      
                           "action": msg,        
                           "force" : 400+random(100),
                    "dodge" : random(30)-15,
                           "damage_type":query_temp("sl_rysxt", me)?"內傷":"瘀傷",
                ]);
        }
            
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練如影隨形腿。\n");
        addn("qi", -60, me);
        addn("neili", -10, me);
        return 1;
}

string perform_action_file(string action)
{
         return __DIR__"ruying-suixingtui/" + action;
}

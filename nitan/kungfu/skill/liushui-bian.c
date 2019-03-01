//liushui-bian.c 流水鞭法
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"只見$N身形疾轉，手腕輕抖，一式「天地雙飛」，$w在身畔化作兩道飛虹。",
        "force" :180,
        "dodge" :10,
        "attack":30,
        "damage":50,
        "lvl"   :0,
        "skill_name" :"天地雙飛",
        "damage_type":"割傷"
]),
([      "action":"$N一式「荒煙平楚」，手中$w吞吐不定，仿佛一層輕煙薄霧飄上$n肩頭，若即若離。",
        "force" :190,
        "dodge" :50,
        "attack":45,
        "damage":80,
        "lvl"   :10,
        "skill_name" :"荒煙平楚",
        "damage_type":"割傷"
]),
([      "action":"$N力貫$w，一招「蘆花飄香」點點鞭影飄浮不定地點向$n的$l。",
        "force" :210,
        "dodge" :80,
        "attack":60,
        "damage":110,
        "lvl"   :80,
        "skill_name" :"蘆花飄香",
        "damage_type":"刺傷"
]),
([      "action":"$N徐徐舞動$w，卻是一招「似真似幻」，只見招斷意連，纏綿婉轉，一鞭未絕，便隱隱有萬鞭相隨。",
        "force" :230,
        "dodge" :110,
        "attack":85,
        "damage":130,
        "lvl"   :110,
        "skill_name" :"似真似幻",
        "damage_type":"割傷"
]),
([      "action":"$N一式「千山暮雪」，$w揮洒自如，霎時間絳雪紛紛，嬌如柳絮，弱似梨花，密密裹住$n全身。",
        "force" :250,
        "dodge" :140,
        "attack":120,
        "damage":150,
        "lvl"   :150,
        "skill_name" :"千山暮雪",
        "damage_type":"刺傷"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "whip" )
         return notify_fail("你必須先找一條鞭子才能練鞭法。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 150)
         return notify_fail("你的內功心法火候太淺，不能學流水鞭法。\n");

     if ((int)me->query_skill("whip", 1) < 150)
         return notify_fail("你的基本鞭法火候不夠。\n");

     if( query("max_neili", me)<500 )
         return notify_fail("你的內力太低，無法學流水鞭法。\n");

     if ((int)me->query_skill("whip", 1) < (int)me->query_skill("liushui-bian", 1))
         return notify_fail("你的基本鞭法水平有限，無法領會更高深的流水鞭法。\n");

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
     level = (int) me->query_skill("liushui-bian", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "whip" )
         return notify_fail("你必須先找一條鞭子才能練鞭法。\n");

     if( query("qi", me)<110 )
            return notify_fail("你的體力不夠練流水鞭法。\n");

     if( query("neili", me)<115 )
            return notify_fail("你的內力不夠練流水鞭法。\n");

     me->receive_damage("qi", 92);
     addn("neili", -98, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"liushui-bian/" + action;
}

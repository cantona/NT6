//tianmo-dao.c 天魔刀法
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N高高躍起，一式「刀劈乾坤」，向$n$l一劈！",
        "force" :60,
        "attack":18,
        "dodge" :30,
        "parry" :20,
        "damage":25,
        "lvl"   :0,
        "skill_name" :"刀劈乾坤",
        "damage_type":"劈傷"
]),
([      "action":"只見$N倒提$w，身形急沖，就在與$n錯身之際，突然使出「曇花一現」從$n後腦斜劈而下。",
        "force" :80,
        "attack":25,
        "dodge" :50,
        "parry" :35,
        "damage":30,
        "lvl"   :30,
        "skill_name" :"曇花一現",
        "damage_type":"劈傷"
]),
([      "action":"$N一式「星河欲曙天」，手中$w化做一道刀光, 似銀河倒瀉般揮向$n$l。",
        "force" :95,
        "attack":38,
        "dodge" :70,
        "parry" :50,
        "damage":50,
        "lvl"   :60,
        "skill_name" :"星河欲曙天",
        "damage_type":"砍傷"
]),
([      "action":"$N眼神恍惚，手中$w飄搖不定，一招「邊風飄搖」斜斜的砍向$n的$l。",
        "force" :110,
        "attack":45,
        "dodge" :90,
        "parry" :75,
        "damage":70,
        "lvl"   :90,
        "skill_name" :"邊風飄搖",
        "damage_type":"砍傷"
]),
([      "action":"$N狂喝一聲，使出一招「絕域蒼茫」，雙手緊握$w帶著逼人的殺氣，刺向$n的$l。",
        "force" :130,
        "attack":62,
        "dodge" :110,
        "parry" :95,
        "damage":85,
        "lvl"   :120,
        "skill_name" :"絕域蒼茫",
        "damage_type":"刺傷"
]),
([      "action":"$N斜身飛起，一招「乘風破浪」，帶出一片刀光卷向$n的$l。",
        "force" :160,
        "attack":80,
        "dodge" :110,
        "parry" :102,
        "damage":100,
        "lvl"   :150,
        "skill_name" :"乘風破浪",
        "damage_type":"劈傷"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "blade" )
         return notify_fail("你必須手裡拿著刀才能練刀法。\n");

     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的內功心法火候太淺，不能學天魔刀法。\n");

     if ((int)me->query_skill("blade", 1) < 100)
         return notify_fail("你的基本刀法火候不夠。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的內力太低，無法學天魔刀法。\n");

     if ((int)me->query_skill("blade", 1) < (int)me->query_skill("tianmo-dao", 1))
         return notify_fail("你的基本刀法水平有限，無法領會更高深的天魔刀法。\n");

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
     level = (int) me->query_skill("tianmo-dao", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "blade" )
         return notify_fail("你必須手裡拿著刀才能練天魔刀法。\n");

     if( query("qi", me)<100 )
            return notify_fail("你的體力不夠練天魔刀法。\n");

     if( query("neili", me)<90 )
            return notify_fail("你的內力不夠練天魔刀法。\n");

     me->receive_damage("qi", 70);
     addn("neili", -75, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-dao/" + action;
}

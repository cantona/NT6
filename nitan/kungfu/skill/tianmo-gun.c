//tianmo-gun.c 日月天魔棍
//By haiyan

inherit SKILL; 

mapping *action = ({
([      "action":"$N身形稍退，手中$w迎風一抖，一招「月黑風高」，朝着$n劈頭蓋臉地砸將下來。",
        "force" :120,
        "attack":15,
        "dodge" :40,
        "parry" :30,
        "damage":20,
        "lvl"   :0,
        "skill_name" :"月黑風高",
        "damage_type":"砸傷"
]),
([      "action":"$N面帶戚色，手中$w以一招「悽風長號」狂風驟雨般地向$n的$l連連掃去。",
        "force" :150,
        "attack":25,
        "dodge" :48,
        "parry" :35,
        "damage":30,
        "lvl"   :20,
        "skill_name" :"悽風長號",
        "damage_type":"挫傷"
]),
([      "action":"$N身形一轉，手中$w往後一拖，就在這將退未退之際，一招「峯迴路轉」，向$n當頭砸下。",
        "force" :180,
        "attack":40,
        "dodge" :60,
        "parry" :50,
        "damage":48,
        "lvl"   :50,
        "skill_name" :"峯迴路轉",
        "damage_type":"砸傷"
]),
([      "action":"$N身形一轉，一招「寒風起兮」$w幻出滿天棍影，虛虛實實地襲向$n的$l。",
        "force" :190,
        "attack":55,
        "dodge" :75,
        "parry" :63,
        "damage":65,
        "lvl"   :80,
        "skill_name" :"寒風起兮",
        "damage_type":"瘀傷"
]),
([      "action":"$N袖舞時幻起花雨滿天，$w落處化作斷霞千縷，一式「生死相隨」，着着搶攻，全然不顧$n進招。",
        "force" :230,
        "attack":70,
        "dodge" :90,
        "parry" :85,
        "damage":75,
        "lvl"   :120,
        "skill_name" :"生死相隨",
        "damage_type":"瘀傷"
]),
([      "action":"$n忽然不見$N，猛一抬頭只見$N一式「策馬長川」，急風驟雨一般徑直掃向$n$l。",
        "force" :280,
        "attack":90,
        "dodge" :105,
        "parry" :100,
        "damage":80,
        "lvl"   :150,
        "skill_name" :"策馬長川",
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; }

int valid_learn(object me)
{
     if ((int)me->query_skill("riyue-xinfa", 1) < 100)
         return notify_fail("你的內功心法火候太淺，不能學日月天魔棍。\n");

     if ((int)me->query_skill("club", 1) < 100)
         return notify_fail("你的基本棍法火候不夠。\n");

     if( query("max_neili", me)<350 )
         return notify_fail("你的內力太低，無法學日月天魔棍。\n");

     if ((int)me->query_skill("club", 1) < (int)me->query_skill("tianmo-gun", 1))
         return notify_fail("你的基本棍法水平有限，無法領會更高深的日月天魔棍。\n");

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
     level = (int) me->query_skill("tianmo-gun", 1);
     for(i = sizeof(action); i > 0; i--)
         if(level > action[i-1]["lvl"])
              return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
     object weapon;

     if( !objectp(weapon=query_temp("weapon", me)) || 
        query("skill_type", weapon) != "club" )
            return notify_fail("你使用的武器不對。\n");

     if( query("qi", me)<70 )
            return notify_fail("你的體力不夠練日月天魔棍。\n");

     if( query("neili", me)<80 )
            return notify_fail("你的內力不夠練日月天魔棍。\n");

     me->receive_damage("qi", 65);
     addn("neili", -68, me);
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-gun/" + action;
}

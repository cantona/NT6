// spring-blade.c

inherit SKILL;

mapping *action = ({
        ([      "action":               "$N使一招「春風拂人醉」，手中$w輕飄飄地向$n的$l斬去！",
                "damage":               100,
                "dodge":                70,
                "damage_type":  "割傷"
        ]),
        ([      "action":               "$N金刃劈風，$w隨著一招「遠山伴人痴」由下而上撩往$n的$l",
                "damage":               40,
                "damage_type":  "割傷"
        ]),
        ([      "action":               "$N身形一轉，一招「飛花逐人香」$w刀光不定，斬向$n的$l",
                "damage":               20,
                "damage_type":  "割傷"
        ]),
        ([      "action":               "$N舞動$w，一招「柳葉隨人笑」迅捷無倫地劈向$n的$l",
                "damage_type":  "割傷"
        ]),
        ([      "action":               "$N手中$w一晃，一招「倩影惹人憐」往$n的$l斜斜砍出一刀",
                "damage":               40,
                "damage_type":  "割傷"
        ]),
        ([      "action":               "$N提刀過肩，蓄勁發力，一招「蘆雪碎人影」直劈$n$l",
                "damage":               40,
                "damage_type":  "割傷"
        ]),
        ([      "action":               "$N移步側身，使一招「彩蝶灼人衣」刀光霍霍斬向$n的$l",
                "damage":               40,
                "damage_type":  "割傷"
        ]),
});

int valid_learn(object me)
{
        return 1;
}

int valid_enable(string usage)
{
        return (usage=="blade") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你必須先找一把刀，才能練刀法。\n");

        if( query("kee", me)<40 )
                return notify_fail("你的體力不夠練這門刀法，還是先休息休息吧。\n");
        me->receive_damage("kee", 40);
        return 1;
}
int effective_level() { return 20;}

string *parry_msg = ({
        "$n使出一招「快意圖恩仇」，用手中的$v急削$N的五指。\n",
        "$n左腳踏前一步，一招「春風吹斜柳」，手中的$v從側面飄向$N之必救。\n",
        "$n手中的$v一抖，挽出一片刀花，一招「晚春憐夕陽」，撒向$N的全身。\n",
        "$n微退一步，手中的$v劃出一條圓弧，一招「春眠不知嘵」，將$N的全身圍住。\n",
});

string *unarmed_parry_msg = ({
"$n使出一招「快意圖恩仇」，用手中的$v急削$N的五指。\n",
"$n左腳踏前一步，一招「春風吹斜柳」，手中的$v從側面飄向$N之必救。\n",
"$n手中的$v一抖，挽出一片刀花，一招「晚春憐夕陽」，撒向$N的全身。\n",
"$n微退一步，手中的$v劃出一條圓弧，一招「春眠不知嘵」，將$N的全身圍住。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int learn_bonus()
{
        return 10;
}
int practice_bonus()
{
        return -100;
}
int black_white_ness()
{
        return 20;
}


// piaoyi-bu.c

inherit SHAOLIN_SKILL;

string *dodge_msg = 
        ({
        "$n一個「銀鷺渡海」，躍起數尺，躲過了$N這一招。\n",
        "$n身形向後一縱，使出一招「玉兔落塵」，避過了$N的攻擊。\n",
        "$n使出「錦鯉穿沙」，恰好躲過了$N的攻勢。\n",
        "$n一招「靈狐幻遁」，姿態美妙地躲了開去。\n"
        "$n使出一招「巧燕穿雲」，猛然縱起丈餘，結果$N撲了個空。\n",
        "$n身形一搖，幻出幾個人影，一招「望穿秋水」躲過了$N的攻勢。\n",
        "$n左一搖，右一晃，一招「紫燕呢喃」已輕鬆閃過。\n",
        "$n一招「飛鳥投林」縱身躍起，倏忽已落至$N身後。\n",
        });

int valid_enable(string usage)
{
        return (usage == "dodge");
}


int valid_learn(object me)
{

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學飄逸步。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練飄逸步。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("piaoyi-bu", 1))
                return notify_fail("你基本輕功火候不夠，無法領會更高深的飄逸步。\n");
        
        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("你基本輕功火候不夠，無法領會高深的飄逸步。\n");

        return 1;
}


string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{       
        int ci;
        if( query("qi", me)<100 )
                return notify_fail("你的體力太差了，不能練飄逸步法。\n");
        if (me->query_skill("piaoyi-bu", 1) < 100)
                me->receive_damage("qi", 30);
        else if (me->query_skill("piaoyi-bu", 1) > 100)
        {    
             if( query("neili", me)<170 )
                     return notify_fail("你的內力不夠練飄逸步法。\n");

                me->receive_damage("qi", ci);
        }
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"piaoyi-bu/" + action;
}

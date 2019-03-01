// xueying-shenfa

inherit SKILL;

mapping *action = ({
([        "action" : "$n一式「天涯海角」，身輕如燕，從$N身邊橫躍而過。\n",
        "dodge"  : 10
]),
([        "action" : "$n一式「血海飄香」，如一陣清風，舒緩地閃過了$N的凌厲攻勢。\n",
        "dodge"  : 20
]),
([        "action" : "$n一式「血影無蹤」，輕盈地一躍，一轉眼間便繞到了$N的身後。\n",
        "dodge"  : 30
]),
([        "action" : "$n一式「心血來潮」，一轉身間，向後飄出近一丈遠\n",
        "dodge"  : 40
]),
([        "action" : "$n一式「血海茫茫」，拔地而起，在半空中一轉，已落到幾丈遠的地方。\n",
        "dodge"  : 50
]),
([        "action" : "$n一式「血刀之影」，淼茫中防似看到紅色的刀光。\n",
        "dodge"  : 60
]),
([        "action" : "$n一式「血洗情天」，雙腳點地，全身化為一道白影，急速繞着$N打了幾轉。\n",
        "dodge"  : 70
]),
([        "action" : "$n一式「血魔之影」，漫天紅影，圍着$N急速地盤旋了幾圈。\n",
        "dodge"  : 80
]),
([        "action" : "$n一式「血血血」，漫天紅影，圍着$N急速地盤旋了幾圈。\n",
        "dodge"  : 90
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("huashan-shenfa");

        if (level < 80 )
                zhaoshu--;

        if (level < 60 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        object me, ob;
        mapping action;

        me = this_player();
        action = query_action(me, ob);

        return action["action"];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太差了，不能練血影身法。\n");
        me->receive_damage("qi", 30);
        return 1;
}
inherit SKILL;

mapping *action = ({
([      "action": "$N單手上抬，一招查拳的﹝沖天炮﹞，對準$n的$l猛擊下去",
        "force" : 120,
        "attack": 30,
        "dodge" : 5,
        "parry" : 5,
        "damage": 40,
        "lvl"   : 0,
        "skill_name" : "查拳",
        "damage_type":  "砸傷"
]),
([      "action": "$N一招燕青拳的﹝白鶴亮翅﹞，身子已向左轉成弓箭步，兩臂向後成鉤手，呼\n"
                  "的一聲輕響，反擊$n$l",
        "force" : 180,
        "attack": 35,
        "dodge" : 10,
        "parry" : 50,
        "damage": 55,
        "lvl"   : 0,
        "skill_name" : "燕青拳",
        "damage_type":  "瘀傷"
]),
([      "action": "$N往後一縱，施展小擒拿手的手法，雙手對著$n$l處的關節直直抓去",
        "force" : 220,
        "attack": 40,
        "dodge" : 15,
        "parry" : 15,
        "damage": 70,
        "lvl"   : 0,
        "skill_name" : "小擒拿手",
        "damage_type":  "抓傷"
]),
([      "action": "$N左拳拉開，右拳轉臂回擾，一招少林的大金剛拳突然擊出，帶著許許風聲貫向$n",
        "force" : 280,
        "attack": 60,
        "dodge" : 22,
        "parry" : 20,
        "damage": 90,
        "lvl"   : 30,
        "skill_name" : "少林大金剛拳",
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N運足氣力，使出八極拳中的﹝八極翻手式﹞，雙掌對著$n的$l平平攻去",
        "force" : 340,
        "attack": 55,
        "dodge" : 40,
        "parry" : 40,
        "damage": 80,
        "lvl"   : 60,
        "skill_name" : "八極拳",
        "damage_type":  "瘀傷"
]),
([      "action": "$N大喝一聲，左手往$n身後一抄，右掌往$n反手擊去，正是八卦掌的招式",
        "force" : 360,
        "attack": 65,
        "dodge" : 30,
        "parry" : 30,
        "damage": 95,
        "lvl"   : 80,
        "skill_name" : "八卦掌",
        "damage_type":  "瘀傷"
]),
([      "action": "$N提氣遊走，左手護胸，右手一招遊身八卦掌的﹝遊空探爪﹞，迅速拍向$n$l",
        "force" : 420,
        "attack": 80,
        "dodge" : 45,
        "parry" : 45,
        "damage": 85,
        "lvl"   : 100,
        "skill_name" : "遊身八卦掌",
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N拉開架式，把武當派的綿掌使得密不透風，招招不離$n的$l",
        "force" : 380,
        "attack": 75,
        "dodge" : 90,
        "parry" : 90,
        "damage": 70,
        "lvl"   : 120,
        "skill_name" : "武當綿掌",
        "damage_type":  "瘀傷"
]),
([      "action": "$N突然飛身一躍而起，雙手握做爪狀，朝著$n的$l猛然抓去，凜然是鷹爪功的招式",
        "force" : 440,
        "attack": 105,
        "dodge" : 90,
        "parry" : 70,
        "damage": 105,
        "lvl"   : 140,
        "skill_name" : "鷹爪功",
        "damage_type":  "抓傷"
]),
([      "action": "只見$N身形一矮，雙手翻滾，一招太極拳﹝雲手﹞直拿$n$l",
        "force" : 450,
        "attack": 90,
        "dodge" : 90,
        "parry" : 100,
        "damage": 90,
        "lvl"   : 160,
        "skill_name" : "太極拳",
        "damage_type":  "瘀傷"
]),
([      "action": "$N一個轉身，趁$n不備，反手將$n牢牢抱住猛的朝地面摔去，竟然是蒙古的摔角招式",
        "force" : 460,
        "attack": 105,
        "dodge" : 5,
        "parry" : 60,
        "damage": 105,
        "lvl"   : 180,
        "skill_name" : "摔角",
        "damage_type":  "摔傷"
]),
});

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練百花錯拳必須空手。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為遠遠不足，難以練習百花錯拳。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的內功火候尚淺，無法學習百花錯拳。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的拳腳根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("cuff", 1) < 150)
                return notify_fail("你的拳法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("hand", 1) < 150)
                return notify_fail("你的手法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("claw", 1) < 150)
                return notify_fail("你的爪法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("strike") < 150)
                return notify_fail("你的掌法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("unarmed", 1)/3 < (int)me->query_skill("baihua-quan", 1)/2)
                return notify_fail("你的拳腳根基火候不足，無法領會更高深的百花錯拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("baihua-quan", 1))
                return notify_fail("你的拳法根基火候不足，無法領會更高深的百花錯拳。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("baihua-quan", 1))
                return notify_fail("你的手法根基火候不足，無法領會更高深的百花錯拳。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("baihua-quan", 1))
                return notify_fail("你的爪法根基火候不足，無法領會更高深的百花錯拳。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("baihua-quan", 1))
                return notify_fail("你的掌法根基火候不足，無法領會更高深的百花錯拳。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "cuff" || usage == "unarmed" || usage == "parry" || usage == "hand" || usage == "strike" || usage == "claw";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("baihua-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你現在手足酸軟，休息一下再練吧。\n");

        if( query("neili", me)<120 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 50);
        addn("neili", -100, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baihua-quan/" + action;
}

inherit SKILL;

mapping *action = ({
([          "action": "$N驀地騰空躍起，雙手緊握$w，對準$n的頭頂，自上而下地砍了下去，只\n"
                  "在半空中留下一團巨大的黑影",
            "force" : 100,
            "damage": 30,
            "dodge" : -5,
            "parry" : -10,
            "damage_type" : "砍傷",
            "lvl" : 0,
            "skill_name" : "開天闢地"
]),
([          "action": "$N突然發一聲喊，衝前兩步，手中$w由下而上反撩$n下三路，頓時只見道\n"
                  "淡黃色的氣影逼向$n，情知不妙，急忙招架",
            "force" : 130,
            "damage": 40,
            "dodge" : -10,
            "parry" : -10,
            "damage_type" : "割傷",
            "lvl" : 10,
            "skill_name" : "氣衝霄漢"
]),
([          "action": "$N忽然虎吼一聲，閃身斜向左前方衝出一步，身體微晃，手中$w在空中劃\n"
                  "出一道淡影，急速橫掃$n的右肩，氣勢迫人",
            "force" : 160,
            "damage": 50,
            "dodge" : -20,
            "parry" : -15,
            "damage_type" : "砍傷",
            "lvl" : 20,
            "skill_name" : "橫掃千軍"
]),
([          "action": "$N突然抽身向右滾倒，隨即跳起，就在一瞬間，已單臂握着$w砸向$n的左\n"
                  "肋，出手既快且狠",
            "force" : 180,
            "damage": 60,
            "dodge" : -35,
            "parry" : -10,
            "damage_type" : "砸傷",
            "lvl" : 30,
            "skill_name" : "以退為進"
]),
([          "action": "$N雙手橫舉$w，平掃$n前胸，招式未使老就已打住猝然變招，斧尖直直撞\n"
                  "向$n的小腹，",
            "force" : 210,
            "damage": 70,
            "dodge" : -40,
            "parry" : -20,
            "damage_type" : "內傷",
            "lvl" : 42,
            "skill_name" : "金斧撞鐘"
]),
([          "action": "$N不急不緩地轉身微蹲，$n見$N露出破綻，急忙搶攻，卻突然發現$N的\n"
                  "身體已轉過來，手中$w正迅猛地掃向自己的下盤",
            "force" : 240,
            "damage": 90,
            "dodge" : -30,
            "parry" : -20,
            "damage_type" : "割傷",
            "lvl" : 55,
            "skill_name" : "迴風轉雲"
]),
([          "action": "$N身形微動，就在同一時間自上中下左右砍出五斧，$n見五把$w從不同的\n"
                   "方位砍向自己，一時間竟不知該如何招架",
            "force" : 280,
            "damage": 110,
            "dodge" : -25,
            "parry" : -40,
            "damage_type" : "砍傷",
            "lvl" : 68,
            "skill_name" : "五斧奪命"
]),
([          "action": "$N前腳猛地往地上一頓，大地也微微一震，接着舉起斧頭在頭頂急轉數圈，$w\n"
                  "就隱含風雲之聲平直而沉穩地襲向$n",
            "force" : 310,
            "damage": 150,
            "parry" : -30,
            "dodge" : -50,
            "damage_type" : "砍傷",
            "lvl" : 80,
            "skill_name" : "一斧斷雲"
])
});

int valid_enable(string usage)
{
        return usage == "hammer" ||  usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的內功火候不夠，無法學盤根錯節斧。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的內力修為太弱，無法練盤根錯節斧。\n");

        if ((int)me->query_skill("hammer") < 30)
                return notify_fail("你的基本錘法等級太低，無法學盤根錯節斧。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("pangen-cuojiefu", 1))
                return notify_fail("你的基本錘法水平有限，無法領會更高深的盤根錯節斧。\n");

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
        level = (int)me->query_skill("pangen-cuojiefu", 1);
                for(i = sizeof(action); i > 0; i--)
                        if(level > action[i-1]["lvl"])
                                return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練盤根錯節斧。\n");

        me->receive_damage("qi", 80);
        me->receive_damage("neili", -52);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pangen-cuojiefu/" + action;
}
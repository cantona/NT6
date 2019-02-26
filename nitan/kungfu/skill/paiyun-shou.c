// panyun-shou.c 排雲手

inherit SKILL;

mapping *action = ({
([        "action" : "$N跨開馬步，右掌前出，十指伸縮，虛虛實實地襲向$n的全身要穴",
        "force" : 30,
        "dodge" : 1,
        "parry" : 4,
        "damage": 0,
        "lvl" : 0,
        "damage_type" : "抓傷"
]),
([        "action" : "$N退後一步，雙掌一起排出，如鈎如戢，插向$n的$l",
        "force" : 40,
        "dodge" : 15,
        "parry" : 5,
        "damage": 0,
        "lvl"   : 15,
        "damage_type" : "刺傷"
]),
([        "action" : "$N忽的一轉身，兩手環扣，攏成圈狀，猛擊$n的下頜",
        "force" : 60,
        "dodge" : 18,
        "parry" : 7,
        "damage": 10,
        "lvl" : 30,
        "damage_type" : "內傷"
]),
([        "action" : "$N雙手平伸，十指微微上下抖動，戳向$n的$l",
        "force" : 80,
        "dodge" : 25,
        "parry" : 11,
        "damage": 12,
        "lvl"   : 40,
        "damage_type" : "內傷"
]),
([        "action" : "$N左手護胸，腋下含空，右手五指如鈎，打向$n的要穴",
        "force" : 100,
        "dodge" : 30,
        "parry" : 14,
        "damage": 15,
        "lvl"   : 50,
        "damage_type" : "內傷"
]),
([        "action" : "$N右腿斜上，上手取目，下手反勾$n的襠部",
        "force" : 115,
        "dodge" : 35,
        "parry" : 17,
        "damage": 19,
        "lvl"   : 60,
        "damage_type" : "內傷"
]),
([        "action" : "$N一手虛指$n的劍訣，劈空抓向$n手中的兵刃",
        "force" : 130,
        "dodge" : 32,
        "parry" : 13,
        "damage": 21,
        "lvl"   : 70,
        "damage_type" : "抓傷"
]),
([        "action" : "$N左手指向$n胸前的五道大穴，右手斜指太陽穴，兩面夾擊$n",
        "force" : 150,
        "dodge" : 38,
        "parry" : 18,
        "damage": 24,
        "lvl"   : 80,
        "damage_type" : "內傷"
]),
([        "action" : "$N一手撐天，一手指地，勁氣籠罩$n的全身",
        "force" : 170,
        "dodge" : 42,
        "parry" : 12,
        "damage": 27,
        "lvl"   : 90,
        "damage_type" : "內傷"
]),
([        "action" : "$N拳掌招若隱若現，若有若無，緩緩地拍向$n的丹田",
        "force" : 190,
        "dodge" : 50,
        "parry" : 15,
        "damage": 30,
        "lvl" : 100,
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_combine(string combo)
{
        return combo == "taiji-quan" || combo == "wudang-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練排雲手必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學排雲手。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的內力太弱，無法練排雲手。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("paiyun-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練排雲手。\n");

        me->receive_damage("qi", 37);
        addn("neili", -25, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"paiyun-shou/" + action;
}
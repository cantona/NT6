inherit FORCE;

string *dodge_msg = ({
        "$n暗運內力，$N的進攻就如擊到氣牆上，沒有半點效果。\n",
        "$n大喝一聲，一股氣流直衝而出，硬生生震退了$N。\n",
        "$n身子一轉，一股旋風將$N的招數全部化解。\n",
        "$n哼然冷笑，微微移動，內力迴旋使$N的進攻差之毫釐。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("zhonghua-aojue", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}


mapping *actionf = ({
([      "action":"$N跨出一步，一指緩緩戳向$n的$l，籠罩了方圓數寸的範圍",
        "force" : 500,
        "attack": 150,
        "dodge" : 90,
        "parry" : 88,
        "damage": 170,
        "damage_type":  "刺傷"
]),
([      "action":"$N一聲震喝，隨即一掌劈出，中途卻忽然一指刺向$n的$l",
        "force" : 510,
        "attack": 165,
        "dodge" : 110,
        "parry" : 90,
        "damage": 160,
        "damage_type":  "刺傷"
]),
([      "action":"$N疾走數步，左掌掌劈向$n的肩頭，右手食卻點向$n的$l，",
        "force" : 515,
        "attack": 155,
        "dodge" : 85,
        "parry" : 85,
        "damage": 175,
        "damage_type":  "刺傷"
]),
([      "action":"$N深吸一口氣，步步進逼，雙掌連環劈向$n的$l",
        "force" : 520,
        "attack": 140,
        "dodge" : 80,
        "parry" : 90,
        "damage": 180,
        "damage_type":  "瘀傷"
]),
([      "action":"$N身體原地不動，雙掌平推，一股掌力凌空奔$n而去",
        "force" : 535,
        "attack": 135,
        "dodge" : 80,
        "parry" : 95,
        "damage": 170,
        "damage_type":  "內傷"
]),
([      "action":"$N足下暗和八卦，步法變幻莫測，左右掌連翻出擊，攻向$n",
        "force" : 500,
        "attack": 150,
        "dodge" : 85,
        "parry" : 115,
        "damage": 165,
        "damage_type":  "震傷"
]),
});

mapping *actionw = ({
([      "action":"$N跨出一步，手中$w緩緩刺向$n，籠罩了方圓數寸的範圍",
        "force" : 450,
        "attack": 170,
        "dodge" : 100,
        "parry" : 110,
        "damage": 240,
        "damage_type":  "刺傷"
]),
([      "action":"$N一聲震喝，手中的$w隨即橫掃$n，中途卻忽然刺向$n的$l",
        "force" : 460,
        "attack": 165,
        "dodge" : 80,
        "parry" : 110,
        "damage": 250,
        "damage_type":  "刺傷"
]),
([      "action":"$N疾走數步，左掌掌劈向$n的肩頭，右手的$w卻點向$n的$l，",
        "force" : 480,
        "attack": 175,
        "dodge" : 85,
        "parry" : 100,
        "damage": 260,
        "damage_type":  "刺傷"
]),
([      "action":"$N深吸一口氣，步步進逼，手中的$w連環刺向$n的$l",
        "force" : 475,
        "attack": 180,
        "dodge" : 75,
        "parry" : 120,
        "damage": 275,
        "damage_type":  "刺傷"
]),
([      "action":"$N身體原地不動，手中的$w一劃，一股內力凌空奔$n而去",
        "force" : 480,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 280,
        "damage_type":  "刺傷"
]),
([      "action":"$N足下暗合八卦，步法變幻莫測，手中的$w化作數道光芒，攻向$n",
        "force" : 490,
        "dodge" : 160,
        "parry" : 110,
        "damage": 320,
        "damage_type":  "刺傷"
]),
});

string *usage_skills = ({ "unarmed", "strike", "sword", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int valid_combo(string combo)
{
        return combo == "zhonghua-aojue" ;
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if( query("character", me) != "光明磊落" || query("character", me) != "國土無雙" )
                return notify_fail("中華傲決正大恢弘，氣度儼然，你"
                                   "怎麼也學不得神似。\n");

        if( query("combat_exp", me)<3000000 )
                return notify_fail("你覺得中華傲決深奧之極，"
                                   "憑自己的戰鬥經驗一時間難以領會。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("你覺得中華傲決過於深奧之極，以"
                                   "自己的武學修養全然無法明白。\n");

        if( query("int", me)<35 )
                return notify_fail("你覺得中華傲決過於艱深，難以理解。\n");

        if( query("con", me)<31 )
                return notify_fail("依照你的根骨無法修煉中華傲決。\n");

        if( query("gender", me) == "無性" && 
            (int)me->query_skill("zhonghua-aojue", 1) > 219)
                return notify_fail("你無根無性，陰陽不調，難以領會高深的中華傲決。\n");

        level = me->query_skill("zhonghua-aojue", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你覺得自己的武學修養有限，難以領會更高深的中華傲決。\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你對" + to_chinese(usage_skills[i]) +
                                           "的理解還不夠，無法繼續領會更高深的中華傲決。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("中華傲決博大精深，無法簡單的通過練習進步。\n");
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"zhonghua-aojue/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"zhonghua-aojue/exert/" + action;
}

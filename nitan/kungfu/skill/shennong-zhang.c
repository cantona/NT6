// shennong-zhang.c 神農杖法
// Edit By Vin Oo 22/2/2001

inherit SKILL;

mapping *action = ({
([      "action": "$N微一躬身，一招「混沌初開」，$w帶著刺耳的吱吱聲，擦地掃向$n的腳踝",
        "force" : 130,
        "attack": 10,
        "dodge" : -5,
        "parry" : 19,
        "damage": 20,
        "lvl"   : 0,
        "skill_name" : "混沌初開",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「後羿射日」，右手托住杖端，左掌居中一擊，令其憑慣性倒向$n的肩頭",
        "force" : 140,
        "attack": 15,
        "dodge" : -10,
        "parry" : 15,
        "damage": 25,
        "lvl"   : 20,
        "skill_name" : "後羿射日",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「夸父趕日」，飛身一躍而起，$w揮舞轉動不停，逼得$n左閃右避，狼狽不堪",
        "force" : 150,
        "attack": 20,
        "dodge" : -5,
        "parry" : 19,
        "damage": 30,
        "lvl"   : 40,
        "skill_name" : "夸父趕日",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「莫邪奠劍」，手中$w斜指蒼天，呆呆地盯了一會，突然猛地一杖刺向$n的$l",
        "force" : 160,
        "attack": 25,
        "dodge" : -5,
        "parry" : 22,
        "damage": 40,
        "lvl"   : 60,
        "skill_name" : "莫邪奠劍",
        "damage_type":"挫傷"
]),
([      "action": "$N高舉$w，猛然一聲暴喝，杖端遙指$n，一招「大禹治水」，攜著呼嘯聲貫向$n",
        "force" : 180,
        "attack": 30,
        "dodge" : -15,
        "parry" : 28,
        "damage": 50,
        "lvl"   : 80,
        "skill_name" : "大禹治水",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「伏羲披靡」，身形一展，持杖狂揮，$w全力一擊攔腰向$n劈去",
        "force" : 210,
        "attack": 35,
        "dodge" : 5,
        "parry" : 32,
        "damage": 57,
        "lvl"   : 100,
        "skill_name" : "伏羲披靡",
        "damage_type":"挫傷"
]),
([      "action": "$N面色莊嚴，一招「軒轅帝威」，端持$w，陡然間身形一晃，疾風般一杖凌空攻向$n而去",
        "force" : 240,
        "attack": 40,
        "dodge" : -5,
        "parry" : 37,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "軒轅帝威",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「化蛇易龍」，單手持杖，力注于腕，待$n攻來， $w猛地彈射而起，擊向$n",
        "force" : 260,
        "attack": 45,
        "dodge" : -5,
        "parry" : 45,
        "damage": 71,
        "lvl"   : 140,
        "skill_name" : "化蛇易龍",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「女媧補天」，猛然一個翻滾拔地而起，高舉$w凌空打向$n的頭部",
        "force" : 280,
        "attack": 50,
        "dodge" : -5,
        "parry" : 55,
        "damage": 70,
        "lvl"   : 160,
        "skill_name" : "女媧補天",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「蚩尤戮血」，身不動，腳不移，$w卻晃動不定，不偏不倚地倒插向$n的要穴",
        "force" : 310,
        "attack": 55,
        "dodge" : -5,
        "parry" : 58,
        "damage": 84,
        "lvl"   : 180,
        "skill_name" : "蚩尤戮血",
        "damage_type":"挫傷"
]),
([      "action": "$N高舉$w，一招「盤古開天」，身形如鬼魅般飄出，對準$n的天靈蓋一杖打下",
        "force" : 330,
        "attack": 61,
        "dodge" : -5,
        "parry" : 62,
        "damage": 90,
        "lvl"   : 200,
        "skill_name" : "盤古開天",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「神農百草」，單腿獨立，$w舞成千百根相似，根根砸向$n全身各處要害",
        "force" : 350,
        "attack": 65,
        "dodge" : -5,
        "parry" : 67,
        "damage": 95,
        "lvl"   : 220,
        "skill_name" : "神農百草",
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 130)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("staff") < 50)
                return notify_fail("你的基本杖法水平不足。\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("shennong-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的神農杖法。\n");

        return 1;
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
        level = (int) me->query_skill("shennong-zhang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練神農杖法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練神農杖法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shennong-zhang/" + action;
}
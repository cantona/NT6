// huilong-zhang.c 回龍杖法

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N微一躬身，一招「龍行無狀」，$w帶著刺耳的吱吱聲，擦地掃向$n的腳踝",
        "force" : 100,
        "attack": 10,
        "dodge" : -5,
        "parry" : 9,
        "damage": 15,
        "lvl"   : 0,
        "skill_name" : "龍行無狀",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「神龍潛行」，右手托住杖端，左掌居中一擊，令其憑慣性倒向$n的肩頭",
        "force" : 110,
        "attack": 15,
        "dodge" : -10,
        "parry" : 15,
        "damage": 15,
        "lvl"   : 30,
        "skill_name" : "神龍潛行",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「飛龍回壁」，舉起$w乒乒乓乓地滿地亂敲，讓$n左閃右避，狼狽不堪",
        "force" : 120,
        "attack": 20,
        "dodge" : -5,
        "parry" : 19,
        "damage": 20,
        "lvl"   : 60,
        "skill_name" : "飛龍回壁",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「淺龍入水」，舉起$w，呆呆地盯了一會，突然猛地一杖打向$n的$l",
        "force" : 140,
        "attack": 25,
        "dodge" : -5,
        "parry" : 22,
        "damage": 20,
        "lvl"   : 70,
        "skill_name" : "淺龍入水",
        "damage_type":"挫傷"
]),
([      "action": "$N將$w頂住自己的胸膛，一端指向$n，一招「騰龍上天」，大聲叫喊著沖向$n",
        "force" : 160,
        "attack": 30,
        "dodge" : -15,
        "parry" : 28,
        "damage": 30,
        "lvl"   : 80,
        "skill_name" : "騰龍上天",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「行雲流水」，全身僵直，蹦跳著持杖前行，冷不防舉杖攔腰向$n劈去",
        "force" : 180,
        "attack": 35,
        "dodge" : 5,
        "parry" : 32,
        "damage": 30,
        "lvl"   : 90,
        "skill_name" : "行雲流水",
        "damage_type":"挫傷"
]),
([      "action": "$N面帶戚色，一招「龍飛鳳舞」，趁$n說話間，一杖向$n張大的嘴巴捅了過去",
        "force" : 220,
        "attack": 40,
        "dodge" : -5,
        "parry" : 37,
        "damage": 40,
        "lvl"   : 110,
        "skill_name" : "龍飛鳳舞",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「蒼龍決」，假意將$w摔落地上，待$n行來，一腳勾起，擊向$n的$l",
        "force" : 250,
        "attack": 45,
        "dodge" : -5,
        "parry" : 45,
        "damage": 40,
        "lvl"   : 120,
        "skill_name" : "蒼龍決",
        "damage_type":"挫傷"
]),
([      "action": "$N伏地一招「地龍決」，一個翻滾，身下$w往橫裡打出，揮向$n的襠部",
        "force" : 280,
        "attack": 50,
        "dodge" : -5,
        "parry" : 55,
        "damage": 50,
        "lvl"   : 130,
        "skill_name" : "地龍決",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「神龍決」，身不動，腳不移，$w卻直飛半空，不偏不倚地砸向$n的$l",
        "force" : 310,
        "attack": 55,
        "dodge" : -5,
        "parry" : 58,
        "damage": 50,
        "lvl"   : 140,
        "skill_name" : "神龍決",
        "damage_type":"挫傷"
]),
([      "action": "$N高舉$w，一招「人龍決」，身形如鬼魅般飄出，對準$n的天靈蓋一杖打下",
        "force" : 330,
        "attack": 61,
        "dodge" : -5,
        "parry" : 62,
        "damage": 60,
        "lvl"   : 150,
        "skill_name" : "人龍決",
        "damage_type":"挫傷"
]),
([      "action": "$N一招「神龍嘯九天」，單腿獨立，$w舞成千百根相似，根根砸向$n全身各處要害",
        "force" : 350,
        "attack": 65,
        "dodge" : -5,
        "parry" : 67,
        "damage": 60,
        "lvl"   : 160,
        "skill_name" : "神龍嘯九天",
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("staff", 1) < 80)
                return notify_fail("你的基本杖法火候太淺。\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("huilong-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的回龍杖法。\n");

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
        level = (int) me->query_skill("huilong-zhang",1);
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
                return notify_fail("你的體力不夠練回龍杖法。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的內力不夠練回龍杖法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huilong-zhang/" + action;
}

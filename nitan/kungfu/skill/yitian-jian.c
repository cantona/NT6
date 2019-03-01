// 倚天劍法

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action": "$N劍尖劍芒暴長，一招「倚天寒芒」，手中$w大開大闔，劍芒直刺$n的$l",
        "force" : 250,
        "attack": 150,
        "dodge" : 50,
        "parry" : 50,
        "damage": 51,
        "lvl"   : 0,
        "skill_name" : "倚天寒芒",
        "damage_type" : "刺傷"
]),
([      "action": "$N劍芒吞吐，單手$w一招「翻江倒海」，劍勢曼妙，劍光直逼向$n的$l",
        "force" : 270,
        "attack": 180,
        "dodge" : 60,
        "parry" : 60,
        "damage": 78,
        "lvl"  : 30,
        "skill_name" : "翻江倒海",
        "damage_type" : "刺傷"
]),
([      "action": "$N一式「神劍佛威」，屈腕雲劍，劍光如彩碟紛飛，幻出點點星光飄向$n",
        "force" : 280,
        "attack": 220,
        "dodge" : 80,
        "parry" : 80,
        "damage": 147,
        "lvl"   : 50,
        "skill_name" : "神劍佛威",
        "damage_type" : "刺傷"
]),
([      "action": "$N揮劍分擊，劍勢自胸前躍出，$w一式「群邪辟易」，毫無留戀之勢，刺向$n",
        "force" : 290,
        "attack": 231,
        "dodge" : 81,
        "parry" : 83,
        "damage": 155,
        "lvl"   : 80,
        "skill_name" : "群邪辟易",
        "damage_type" : "刺傷"
]),
([      "action": "$N左手劍指劃轉，腰部一扭，右手$w一記「盪妖除魔」自下而上刺向$n的$l",
        "force" : 300,
        "attack": 275,
        "dodge" : 95,
        "parry" : 95,
        "damage": 193,
        "lvl"   : 150,
        "skill_name" : "盪妖除魔",
        "damage_type" : "刺傷"
]),
(["action": HIR "$N臉色凝重凝重，緩緩舉起$w"NOR""HIR"，突然躍起身劍合一，使出一招“倚天不出”，\n手中$w"NOR""HIR"由下至上劃出一條美麗的弧線刺向$n的$l" NOR,
         "damage": 250,
         "attack": 300,
         "dodge": 100,
         "parry": 100,
         "lvl": 150,
         "damage_type": "刺傷",
         "skill_name": "倚天不出",
]),
(["action": HIY "$N反身躍起，雙手握劍舉至頭頂使出倚天劍法奧義“誰與爭鋒”，這看似簡簡單單的一劍，\n而厚重的劍氣直奔$n的$l而去"NOR,
         "damage": 300,
         "attack": 350,
         "dodge": 120,
         "parry": 120,
         "lvl": 220,
         "damage_type": "刺傷",
         "skill_name": "誰與爭鋒",
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("character", me) == "心狠手辣" ||
            query("character", me) == "陰險姦詐" ||
            query("character", me) == "狡黠多變" )
                return notify_fail("以你的性格不適合修煉此劍術。\n");

        if( query("int", me)<33 )
                return notify_fail("以你的資質永遠也學不會倚天劍法。\n");

        if( query("con", me)<28 )
                return notify_fail("以你根骨不適合修煉倚天劍法。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("你的基本劍法火候太淺。\n");

        if (me->query_skill("sword", 1) < me->query_skill("yitian-jian"))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的倚天劍法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yitian-jian", 1);
         for (i = sizeof(action); i > 0; i--)
                 if (level > action[i - 1]["lvl"])
                         return action[NewRandom(i, 5, level / 5)];
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練倚天劍法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練倚天劍法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -60, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
         mixed result;
         object weapon;

         if( objectp(weapon) && query("id", weapon) == "yitian jian" )
         {
                victim->receive_damage("qi", damage_bonus+me->query_skill("yitian-jian"), me);
                victim->receive_damage("jing", (damage_bonus+me->query_skill("yitian-jian")) / 2, me);
                return WHT "$N有了倚天劍，頓時劍光大勝，劍氣之聲連連呼嘯而過，$n"
                       WHT "$n只覺氣血翻騰，“哇”的吐出一口鮮血。\n" NOR;
         }

         if (damage_bonus < 100)
         {
                 result =  ([ "damage" : damage_bonus / 2]);
                 result += (["msg" : "$n"NOR""HIR"只覺一陣清風拂過，只見"NOR"$n"HIR"的嘴角竟露出一絲血色！\n" NOR]);
                 return result;
         }

         if (damage_bonus > 100)
         {
                 result =  ([ "damage" : damage_bonus ]);
                 result += (["msg" : "$n"NOR""MAG"只覺一陣清風拂過，只見"NOR"$n"MAG"血冒三丈，已被$N的劍氣所傷！\n" NOR]);
                 return result;
         }
}


string perform_action_file(string action)
{
        return __DIR__"yitian-jian/" + action;
}
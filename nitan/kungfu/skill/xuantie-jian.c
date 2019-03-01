// This program is a part of NT MudLIB

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *msg = ({
BLU "$N當胸平平刺出一劍，實在是毫無任何變化，而卻有轟轟之聲，$n"BLU"只覺\n一股大力由$w"BLU"直逼周身",
BLU "$N凌空躍起，身隨劍起，借助下行之勢向下猛劈一劍，將$n"BLU"周身籠于劍氣之下",
BLU "$N輕嘆一聲，隨手橫劈一劍，緩緩指向$n"BLU"，看似無絲毫變化，卻盡得劍\n法精髓，當真平淡中蘊涵所有變化，無招勝有招",
BLU "$N迅疾挑出一劍，但見劍勢如虹，快似閃電，無可當鋒！此劍之快，匪夷所\n思，$n"BLU"無法分辨出劍路去來",
BLU "$N仰首長嘯，令風雲變幻，狂風遽起，旋及一劍平指，劍氣彌漫于$n"BLU"周\n身各處，$n"BLU"只覺身處驚濤駭浪之中，驚怖中更覺$N劍力有如海潮一般，一波\n一浪陣陣湧來，綿延不絕，癒發癒強",
BLU "$N祭起$w"BLU"，左手捏成劍訣置于胸前，咄喝一聲，正是劍法至尊的“御劍\n式”，空中滿是劍影，宛若千道銀鏈，只在$n"BLU"身邊遊動",
BLU "$N$w"BLU"連出十余劍，一時迅疾如流星劃空，一時凝重遲緩，招招無跡可尋，\n平淡至極又匪思至極，順刺，逆擊，橫削，倒劈，無不是劍法的入門，當真返樸\n歸真，卻已不再存任何破綻",
});

mapping *action = ({
([      "action": "$N手中的$w盪出，就如大江東去，威力勢不可擋",
        "force" : 250,
        "attack": 170,
        "dodge" :-30,
        "parry" :-70,
        "damage": 230,
        "lvl"   : 0,
        "damage_type": "割傷"
]),
([      "action": "$N踏上一步，手中$w舞出一道劍光劈向$n的$l",
        "force" : 310,
        "attack": 280,
        "dodge" :-33,
        "parry" :-79,
        "damage": 224,
        "lvl"   : 40,
        "damage_type": "割傷"
]),
([      "action": "$N手中$w一抖，一劍刺出，攻向$n的$l，沒有半點花巧",
        "force" : 330,
        "attack": 290,
        "dodge" :-41,
        "parry" :-85,
        "damage": 235,
        "lvl"   : 80,
        "damage_type": "割傷"
]),
([      "action": "$N手中$w微微顫動，忽然刺出，一道劍光射向$n的$l",
        "force" : 360,
        "attack": 295,
        "dodge" :-45,
        "parry" :-92,
        "damage": 239,
        "lvl"   : 120,
        "damage_type": "刺傷"
]),
([      "action": "$N橫過$w，驀然橫掃$n，氣勢如虹，盪氣回腸",
        "force" : 340,
        "attack": 297,
        "dodge" :-47,
        "parry" :-99,
        "damage": 248,
        "lvl"   : 160,
        "damage_type": "割傷"
]),
([      "action": "$N手中的$w連削帶刺，夾帶著一陣旋風掠過$n全身",
        "force" : 380,
        "attack": 300,
        "dodge" :-50,
        "parry" :-100,
        "damage": 300,
        "lvl"   : 200,
        "damage_type": "刺傷"
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{

        if( query("str", me)<26 )
                return notify_fail("你的先天膂力孱弱，無法學習玄鐵劍法。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想殺盡敵人，沒能理解玄鐵劍法的的真正含義。\n");

        if( query("character", me) == "陰險姦詐" )
                return notify_fail("你一心想怎麼學好劍法去害人，結果沒能理解玄鐵劍法。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不到，無法學習玄鐵劍法。\n");

        if (me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("你武學修養不足，無法領悟玄鐵劍法！\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力太差，無法學習玄鐵劍法。\n");

        if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的玄鐵劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的玄鐵劍法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuantie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        object env;

        env = environment(me);
        if( !query("can_practice_xiantie-jian", env) &&
            me->query_skill("xuantie-jian", 1) < 180)
                return notify_fail("你拿起劍揮舞了半天，只覺得此處不適合練習玄鐵劍法。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練玄鐵劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練玄鐵劍法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

        if( query("can_practice_xiantie-jian", env) )
        message_vision(HIW "\n$N" HIW"屏氣凝息，揮舞著手中的"+ weapon->name() + HIW "，奮力與洪流相抗。\n\n", me);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon=query_temp("weapon", me);

        lvl = me->query_skill("xuantie-jian", 1);

        if (damage_bonus < 120
           || lvl < 160
           || ! objectp(weapon)
           || query("neili", me)<500
           || me->query_skill_mapped("sword") != "xuantie-jian" )
                      return damage_bonus / 4;

        //if (lvl / 2 + random(lvl) > victim->query_skill("parry", 1))
        {
                addn("neili", -120, me);
                victim->receive_wound("qi", damage_bonus * 4 / 5, me);

                return HIW "$N" HIW "手中" + weapon->name() + HIW "猶如神助，從天而下，威不"
                       "可擋地劈向$n" HIW "，氣勢恢弘之極。\n" NOR;
         }
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jian/" + action;
}
int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("xuantie-jian", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 90;
        if (lvl < 325) return 100;
        if (lvl < 350) return 110;
        return 120;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("id", weapon) != "ironsword" )
                return 0.8;
        else return 1.2;
}
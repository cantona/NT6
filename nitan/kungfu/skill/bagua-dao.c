// bagua-dao.c 八卦刀

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N腳踏八卦方位，盤身駐地，一招「削耳撩腮」，手中$w由上至下向$n砍去",
        "force"  : 125,
        "attack" : 15,
        "dodge"  : 56,
        "parry"  : 52,
        "lvl"    : 0,
        "damage" : 19,
        "skill_name" : "削耳撩腮",
        "damage_type" : "割傷",
]),
([      "action" : "$N使出「上步劈山」，身形向後乍然一閃，左手急速纏住$n左手，手中$w已罩向$n的$l",
        "force"  : 153,
        "attack" : 32,
        "dodge"  : 70,
        "parry"  : 75,
        "lvl"    : 20,
        "damage" : 27,
        "skill_name" : "上步劈山",
        "damage_type" : "割傷",
]),
([      "action" : "$N腳踏八卦方位，反轉刀尖，一招「反身劈山」，手中$w竟然用刀背劈向$n的胸前",
        "force"  : 198,
        "attack" : 45,
        "dodge"  : 67,
        "parry"  : 87,
        "lvl"    : 40,
        "damage" : 34,
        "skill_name" : "反身劈山",
        "damage_type" : "割傷",
]),
([      "action" : "$N腳下踏着先天八卦的圖式，身隨意轉，手隨心動，一式「鐵牛耕地」，$w緩緩的斜着向$n推去",
        "force"  : 220,
        "attack" : 48,
        "dodge"  : 75,
        "parry"  : 91,
        "lvl"    : 60,
        "damage" : 49,
        "skill_name" : "鐵牛耕地",
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「朝陽刀」，左右腿虛點，$w一提一收，劃出一個大平十字，揮向$n的頸部",
        "force"  : 231,
        "attack" : 55,
        "dodge"  : 73,
        "parry"  : 96,
        "lvl"    : 80,
        "damage" : 58,
        "skill_name" : "朝陽刀",
        "damage_type" : "割傷",
]),
([      "action" : "$N一提氣，勁貫刀鋒，$w“嗡嗡”做響，一招「上歪門」，自上而下直插$n的頭頂",
        "force"  : 257,
        "attack" : 59,
        "dodge"  : 73,
        "parry"  : 95,
        "lvl"    : 100,
        "damage" : 66,
        "skill_name" : "上歪門",
        "damage_type" : "割傷",
]),
([      "action" : "$N使出「下歪門」，左手後撤，刀斜上招架，順勢下剁，刀光不停指向$n的$l",
        "force"  : 253,
        "attack" : 60,
        "dodge"  : 85,
        "parry"  : 105,
        "lvl"    : 120,
        "damage" : 63,
        "skill_name" : "下歪門",
        "damage_type" : "割傷",
]),
([      "action" : "$N使出「回身劈山」，身法陡變，輕靈飄忽，乘$n眼花耳鳴之際，突然右手刀光反捲向$n的$l",
        "force"  : 283,
        "attack" : 63,
        "dodge"  : 87,
        "parry"  : 118,
        "lvl"    : 140,
        "damage" : 69,
        "skill_name" : "回身劈山",
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「上勢抱刀」，$w大開大闔，自上而下劃出一個大弧，筆直劈向$n",
        "force"  : 268,
        "attack" : 66,
        "dodge"  : 88,
        "parry"  : 124,
        "lvl"    : 160,
        "damage" : 73,
        "skill_name" : "上勢抱刀",
        "damage_type" : "割傷",
]),
([      "action" : "$N藏刀內收，一招「下勢撩刀」，刀鋒自下而上劃了個半弧，向$n的$l揮去！\n"
                   "$n只覺眼前一片流光般的刀影，向自己全身湧去，退後欲避，又覺一陣寒氣直逼過來",
        "force"  : 272,
        "attack" : 67,
        "dodge"  : 94,
        "parry"  : 133,
        "lvl"    : 180,
        "damage" : 82,
        "skill_name" : "下勢撩刀",
        "damage_type" : "割傷",
]),
([      "action" : "$N驀的使一招「八卦八陣」，頓時劍光中無數朵刀花從四面八方湧向$n全身",
        "force"  : 280,
        "attack" : 72,
        "dodge"  : 96,
        "parry"  : 132,
        "lvl"    : 200,
        "damage" : 85,
        "skill_name" : "八卦八陣",
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為尚淺，無法練習八卦刀法。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 100 )
                return notify_fail("你的基本刀法水平有限，無法練習八卦刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("bagua-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的八卦刀法。\n");

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
        int i, level, tiandao;

        level = (int)me->query_skill("bagua-dao", 1);
        tiandao=query_temp("pfm_tiandao", me);

        switch (tiandao)
        {
        case 1:
                return ([ "action": WHT "$N" WHT "施出「" HIY "天刀八勢" NOR +
                                    WHT "」起手勢" HIY "『乾』" NOR + WHT "字"
                                    "訣，手中的$w" WHT "宛如一道閃電對準$n" WHT
                                    "直劈而下",
                           "force"  : 180,
                           "damage" : 85,
                           "attack" : 65,
                           "dodge"  : 96,
                           "parry"  : 132,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 2:
                return ([ "action": WHT "$N" WHT "身形一轉，一招" HIY "『坤』"
                                    NOR + WHT "字訣隨手施出，手中$w" WHT "頓時"
                                    "幻作一道道刀芒籠罩$n" WHT "全身",
                           "force"  : 220,
                           "damage" : 87,
                           "attack" : 63,
                           "dodge"  : 96,
                           "parry"  : 112,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 3:
                return ([ "action": WHT "$N" WHT "深深吸入一口氣，施一招" HIY
                                    "『巽』" NOR + WHT "字訣施出，手中$w" WHT
                                    "順勢翻手一刀，向$n" WHT "劈斬出",
                           "force"  : 230,
                           "damage" : 83,
                           "attack" : 61,
                           "dodge"  : 93,
                           "parry"  : 107,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 4:
                return ([ "action": WHT "$N" WHT "身法陡然加快，手中$w" WHT "隨"
                                    "着" HIY "『震』" NOR + WHT "字訣方位斬出，"
                                    "數道刀芒直劈向$n" WHT "要害所在",
                           "force"  : 220,
                           "damage" : 87,
                           "attack" : 63,
                           "dodge"  : 96,
                           "parry"  : 112,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 5:
                return ([ "action": WHT "接着$N" WHT "一聲長歎，依照八卦方位施"
                                    "出" HIY "『坎』" NOR + WHT "字訣，$w" WHT
                                    "刀身頓時迸出道金光射向$n" WHT,
                           "force"  : 223,
                           "damage" : 81,
                           "attack" : 67,
                           "dodge"  : 99,
                           "parry"  : 103,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 6:
                return ([ "action": WHT "$N" WHT "飛身一躍而起，凌空施一式" HIY
                                    "『兑』" NOR + WHT "字訣，頓時刀光爍爍猶如"
                                    "千萬柄$w" WHT "齊罩向$n" WHT,
                           "force"  : 210,
                           "damage" : 85,
                           "attack" : 65,
                           "dodge"  : 96,
                           "parry"  : 132,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 7:
                return ([ "action": WHT "$N" WHT "緊接着施展出" HIY "『離』" NOR +
                                    WHT "字訣，$w" WHT "猶如九天神雷，攜着呼嘯"
                                    "破空之聲直貫向$n" WHT "而去",
                           "force"  : 253,
                           "damage" : 63,
                           "attack" : 52,
                           "dodge"  : 97,
                           "parry"  : 88,
                           "damage_type" : "割傷",
                        ]);
                break;
        case 8:
                return ([ "action": WHT "最後$N" WHT "一聲冷笑，施出「" HIY "天"
                                    "刀八勢" WHT "」最終" HIY "『艮』" NOR + WHT
                                    "字訣，只見$w" WHT "一閃，已至$n" WHT "眼前",
                           "force"  : 197,
                           "damage" : 89,
                           "attack" : 58,
                           "dodge"  : 103,
                           "parry"  : 142,
                           "damage_type" : "割傷",
                        ]);
                break;
        default:
                for(i = sizeof(action); i > 0; i--)
                        if(level > action[i-1]["lvl"])
                                return action[NewRandom(i, 20, level / 5)];
                break;
        }
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠，練不了八卦刀法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠，練不了八卦刀法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -70, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"bagua-dao/" + action;
}
#include <ansi.h>

inherit SKILL;

mapping *action=({
([      "action" : "$N一招" HIY "『天陣居乾為天門』" NOR "身體緩緩遊動，圍繞$n輕拍數掌，忽然"
                   "迅速向上斜劈，掌力化成弧形，罩向$n的$l",
        "force" : 130,
        "attack": 21,
        "dodge" : 70,
        "parry" : 65,
        "damage": 14,
        "lvl"   : 0,
        "skill_name" : "天陣居乾為天門",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招" WHT "『地陣居坤為地門』" NOR "腳邁連環步，雙掌不停的滑動，忽然爆"
                   "喝一聲，身體高高躍起，撲向$n的$l就是一記重掌",
        "force" : 170,
        "attack": 25,
        "dodge" : 83,
        "parry" : 76,
        "damage": 17,
        "lvl"   : 30,
        "skill_name" : "地陣居坤為地門",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招" YEL "『風陣居巽為風門』" NOR "身如行雲流水，飄忽不定，雙手雲袖飄"
                   "動，忽然袖中雙掌咋現，分別從左右兩邊齊齊攻向$n",
        "force" : 190,
        "attack": 28,
        "dodge" : 95,
        "parry" : 88,
        "damage": 20,
        "lvl"   : 60,
        "skill_name" : "風陣居巽為風門",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招" HIW "『雲陣居震為雲門』" NOR "倏忽欺至$n身前，含胸收腹，頭緩緩低"
                   "下，似乎顯得沒精打采，一記雲掌軟綿綿的拍向$n",
        "force" : 230,
        "attack": 35,
        "dodge" : 107,
        "parry" : 98,
        "damage": 23,
        "lvl"   : 90,
        "skill_name" : "雲陣居震為雲門",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招" HIR "『飛龍居坎飛龍門』" NOR "突然縱起丈餘，頭下腳上，倒過身子，"
                   "猶如一隻在空中盤旋的飛龍，一掌拍向$n",
        "force" : 270,
        "attack": 40,
        "dodge" : 129,
        "parry" : 113,
        "damage": 27,
        "lvl"   : 120,
        "skill_name" : "飛龍居坎飛龍門",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一招" MAG "『武翼居兑武翼門』" NOR "身如陀螺急轉，展開輕功圍着$n快速遊"
                   "走，忽然飛身而起，一掌拍向$n的$l",
        "force" : 320,
        "attack": 48,
        "dodge" : 154,
        "parry" : 118,
        "damage": 38,
        "lvl"   : 150,
        "skill_name" : "武翼居兑武翼門",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N錯步上前，一招" CYN "『鳥翔居離鳥翔門』" NOR "招招搶先，以快打慢，猶如"
                   "一隻展翅翱翔的大鵬，輕輕一躍已經到了$n的身後，運掌如風推\n向$n的大椎穴",
        "force" : 360,
        "attack": 61,
        "dodge" : 153,
        "parry" : 131,
        "damage": 45,
        "lvl"   : 180,
        "skill_name" : "鳥翔居離鳥翔門",
        "damage_type" : "內傷"
]),
([      "action" : "$N身形一扭，將背門對準$n，使出一招" HIM "『蜿盤居艮蜿盤門』" NOR "無論$n"
                   "如何出招，$N的背後好像生了眼睛，總能及時閃避，忽\n然$N背脊猛向$n胸口靠去，"
                   "雙掌突然從腋下鑽出，直擊$n的$l",
        "force" : 380,
        "attack": 73,
        "dodge" : 155,
        "parry" : 135,
        "damage": 57,
        "lvl"   : 220,
        "skill_name" : "蜿盤居艮蜿盤門",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

string main_skill() { return "baihua-cuoquan"; }

int valid_learn(object me)
{
        if (me->query_skill("baihua-cuoquan", 1) > 0)
                return notify_fail("你已經練成了百花錯拳，不必再單獨學習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練八陣八卦掌必須空手。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力不夠，無法練習八陣八卦掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bazhen-zhang", 1))
                return notify_fail("你的基本掌法火候有限，無法領會更高深的八陣八卦掌。\n");

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
        level = (int)me->query_skill("bazhen-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 85);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"bazhen-zhang/" + action;
}
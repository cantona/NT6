#include <ansi.h>

inherit SKILL;

mapping *action = ({
([   "action" : "$N面露微笑，一招「蘇秦背劍」，手中$w一抖，劍光暴長，洒向$n的$l",
     "force"  : 50,
     "attack" : 15,
     "dodge"  :-10,
     "parry"  :-25,
     "damage" : 10,
     "lvl"    : 0,
     "skill_name" : "蘇秦背劍",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「下步劈山」，身形突閃，劍招陡變，手中$w從後部斜刺向$n的$l",
     "force"  : 70,
     "attack" : 25,
     "dodge"  :-25,
     "parry"  :-30,
     "damage" : 15,
     "lvl"    : 10,
     "skill_name" : "下步劈山",
     "damage_type":  "刺傷"
]),
([   "action" : "$N暴退數尺，一招「抱劍歸山」，低首撫劍，隨後手中$w驟然穿上，刺向$n的$l",
     "force"  : 75,
     "attack" : 33,
     "dodge"  :-22,
     "parry"  :-32,
     "damage" : 20,
     "lvl"    : 20,
     "skill_name" : "抱劍歸山",
     "damage_type":  "刺傷"
]),
([   "action" : "$N身形一晃，疾掠而上，使一招「丹鳳朝陽」，手中$w龍吟一聲，對準$n連遞數劍",
     "force"  : 90,
     "attack" : 39,
     "dodge"  :-40,
     "parry"  :-35,
     "damage" : 25,
     "lvl"    : 30,
     "skill_name" : "丹鳳朝陽",
     "damage_type":  "刺傷"
]),
([   "action" : "$N身形一展，施展出「隨形腿弄花葬劍」，如影相隨，手中$w疾往$n的$l刺去",
     "force"  : 100,
     "attack" : 43,
     "dodge"  :-60,
     "parry"  :-40,
     "damage" : 29,
     "lvl"    : 40,
     "skill_name" : "隨形腿弄花葬劍",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「陰陽扇折枝開合」，側過身子，手中$w疾往斜上挑起，直指$n的$l",
     "force"  : 130,
     "attack" : 51,
     "dodge"  :-50,
     "parry"  :-45,
     "damage" : 36,
     "lvl"    : 50,
     "skill_name" : "陰陽扇折枝開合",
     "damage_type":  "刺傷"
]),
([   "action" : "$N微微一個轉身，一招「空劍撫琴揮鞭」，手中$w卻已自肋下穿出，罩向$n的$l",
     "force"  : 150,
     "attack" : 62,
     "dodge"  :-40,
     "parry"  :-47,
     "damage" : 43,
     "lvl"    : 60,
     "skill_name" : "空劍撫琴揮鞭",
     "damage_type":  "刺傷"
]),
([   "action" : "$N神色微變，一招「翻雲手劍指瀾關」，劍招頓時變得凌厲無比，手中$w閃電般射向$n",
     "force"  : 180,
     "attack" : 71,
     "dodge"  :-30,
     "parry"  :-52,
     "damage" : 51,
     "lvl"    : 80,
     "skill_name" : "翻雲手劍指瀾關",
     "damage_type":  "刺傷"
]),
([   "action" : "$N緩緩低首，接著一招「洗劍懷中抱月」，手中$w中宮直進，迅捷無比地往$n刺去",
     "force"  : 200,
     "attack" : 85,
     "dodge"  :-20,
     "parry"  :-54,
     "damage" : 58,
     "lvl"    : 100,
     "skill_name" : "洗劍懷中抱月",
     "damage_type":  "刺傷"
]),
([   "action" : "$N縱步上走，單腿猛的踢向$n腰間，$n正要抽身回防，只見剎那間劍光一閃，$N\n"
                "一招「迎門腿反劈華山」，$w已經反劈而下",
     "force"  : 220,
     "attack" : 88,
     "dodge"  :-30,
     "parry"  :-62,
     "damage" : 67,
     "lvl"    : 120,
     "skill_name" : "迎門腿反劈華山",
     "damage_type":  "刺傷"
]),
([   "action" : "$N矮身側步，一招「返腕翼德闖帳」，手中$w反手疾挑而出，“唰”的一聲往$n刺去",
     "force"  : 240,
     "attack" : 91,
     "dodge"  :-65,
     "parry"  :-65,
     "damage" : 75,
     "lvl"    : 140,
     "skill_name" : "返腕翼德闖帳",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「黃龍轉身吐須」，驀地疾退一步，又沖前三步，手中$w化為一道凌厲的弧光\n"
                "往$n的$l刺去",
     "force"  : 265,
     "attack" : 93,
     "dodge"  :-40,
     "parry"  :-68,
     "damage" : 82,
     "lvl"    : 160,
     "skill_name" : "黃龍轉身吐須",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「上步雲邊摘月」，縱身躍起，不見蹤影，接著卻又從半空中穿下，雙手緊緊握著\n"
                "$w，聲勢逼人地刺向$n的$l",
     "force"  : 290,
     "attack" : 97,
     "dodge"  :-60,
     "parry"  :-72,
     "damage" : 88,
     "lvl"    : 180,
     "skill_name" : "上步雲邊摘月",
     "damage_type":  "刺傷"
]),
([   "action" : "$N一招「提撩劍白鶴舒翅」，手中$w“嗤”的一聲斜刺向天空，隨即向下“唰唰”兩\n"
                "下，劃出一個叉字，往$n的$l刺去",
     "force"  : 310,
     "attack" : 109,
     "dodge"  :-45,
     "parry"  :-75,
     "damage" : 96,
     "lvl"    : 200,
     "skill_name" : "提撩劍白鶴舒翅",
     "damage_type":  "刺傷"
]),
([   "action" : "$N左腿微抬，一招「沖天掌蘇秦背劍」，左手虛擊，右手$w猛的自下方挑起，激起數\n"
                "股勁風反挑$n的$l",
     "force"  : 330,
     "attack" : 115,
     "dodge"  :-50,
     "parry"  :-82,
     "damage" : 105,
     "lvl"    : 220,
     "skill_name" : "沖天掌蘇秦背劍",
     "damage_type":  "刺傷"
]),
});

string main_skill() { return "daojian-guizhen"; }

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
        /*
        if ((int)me->query_skill("daojian-guizhen", 1))
                return notify_fail("你已經將苗家劍法和胡家刀法二者合一了。\n");
        */
        if( query("max_neili", me)<1300 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本劍法火候不夠，無法學習苗家劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("miaojia-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的苗家劍法。\n");

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
        level   = (int) me->query_skill("miaojia-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if ((int)me->query_skill("daojian-guizhen", 1))
                return notify_fail("你已經將苗家劍法和胡家刀法二者合一了。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力目前沒有辦法練習苗家劍法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，無法練習苗家劍法。\n");

        addn("qi", -53, me);
        addn("neili", -84, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"miaojia-jian/" + action;
}
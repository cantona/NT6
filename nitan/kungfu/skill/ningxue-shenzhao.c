#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$N全身拔地而起，半空中一個筋鬥，一式「兇鷹襲兔」，迅猛地抓向$n的$l",
    "force" : 250,
    "attack": 45,
    "dodge" : 10,
    "parry" : 18,
    "damage": 30,
    "lvl"   : 0,
    "skill_name" : "兇鷹襲兔" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N單腿直立，雙臂平伸，一式「雄鷹展翅」，雙爪一前一後攏向$n的$l",
    "force" : 270,
    "attack": 50,
    "dodge" : 20,
    "parry" : 26,
    "damage": 45,
    "lvl"   : 40,
    "skill_name" : "雄鷹展翅" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N一式「拔翅鷹飛」，全身向斜裡平飛，右腿一繃，雙爪搭向$n的肩頭",
    "force" : 300,
    "attack": 60,
    "dodge" : 20,
    "parry" : 32,
    "damage": 45,
    "lvl"   : 70,
    "skill_name"  : "拔翅鷹飛" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N雙爪交錯上舉，使一式「迎風振翼」，一拔身，分別襲向$n左右腋空門",
    "force" : 340,
    "attack": 85,
    "dodge" : 30,
    "parry" : 55,
    "damage": 55,
    "lvl"   : 100,
    "skill_name" : "迎風振翼" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N全身滾動上前，一式「飛龍獻爪」，右爪突出，鬼魅般抓向$n的胸口",
    "force" : 350,
    "attack": 110,
    "dodge" : 40,
    "parry" : 68,
    "damage": 76,
    "lvl"   : 120,
    "skill_name" : "飛龍獻爪" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N伏地滑行，一式「頂天立地」，上手襲向膻中大穴，下手反抓$n的襠部",
    "force" : 370,
    "attack": 121,
    "dodge" : 51,
    "parry" : 78,
    "damage": 96,
    "lvl"   : 140,
    "skill_name" : "頂天立地" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N左右手掌爪互逆，一式「搏擊長空」，無數道勁氣破空而出，迅疾無比地擊向$n",
    "force" : 398,
    "attack": 133,
    "dodge" : 67,
    "parry" : 85,
    "damage": 107,
    "lvl"   : 160,
    "skill_name" : "搏擊長空" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N騰空高飛三丈，一式「鷹揚萬裡」，天空中頓時顯出一個巨靈爪影，緩緩罩向$n",
    "force" : 410,
    "attack": 143,
    "dodge" : 55,
    "parry" : 81,
    "damage": 121,
    "lvl"   : 180,
    "skill_name" : "鷹揚萬裡" ,
    "damage_type" : "抓傷"
]),
([  "action": "$N忽的撥地而起，使一式「蒼龍出水」，身形化作一道閃電射向$n",
    "force" : 431,
    "attack": 162,
    "dodge" : 63,
    "parry" : 86,
    "damage": 133,
    "lvl"   : 200,
    "skill_name" : "蒼龍出水" ,
    "damage_type" : "內傷"
]),
([  "action":  "$N微微一笑，使一式「萬佛朝宗」，雙手幻出萬道金光,直射向$n的$l",
    "force" : 455,
    "attack": 173,
    "dodge" : 66,
    "parry" : 95,
    "damage": 137,
    "lvl"   : 220,
    "skill_name" : "萬佛朝宗" ,
    "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
            return notify_fail("練凝血神爪必須空手。\n");

        if( query("max_neili", me)<800 )
            return notify_fail("你的內力太弱，無法練凝血神爪。\n");

        if ((int)me->query_str() < 40)
            return notify_fail("你現在膂力孱弱，還無法練凝血神爪。\n");

        if ((int)me->query_dex() < 40)
            return notify_fail("你現在身法欠佳，還無法練凝血神爪。\n");

        if ((int)me->query_skill("force") < 200)
            return notify_fail("你的內功太差，無法練凝血神爪。\n");

        if ((int)me->query_skill("claw", 1) < 180)
            return notify_fail("你的基本爪法太差，無法領會凝血神爪。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("ningxue-shenzhao", 1))
            return notify_fail("你的基本爪法火候不夠，無法領會更高深的凝血神爪。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("ningxue-shenzhao",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 5, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<120 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<350 )
                return notify_fail("你的內力不夠練凝血神爪。\n");

        me->receive_damage("qi", 100);
        addn("neili", -300, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("ningxue-shenzhao", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("zhua_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "remain": -1,
                                 "duration" : lvl / 100 + random(lvl / 10) ])))
        {
                return HIW "$n" HIW "的身子突然一陣顫抖,牙關咬得咯咯作響，看來是中了$N" HIW "抓上的凝血神抓毒。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"ningxue-shenzhao/" + action;
}
int query_effect_parry(object attacker, object me) 
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("ningxue-shenzhao", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
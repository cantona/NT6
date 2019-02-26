#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N使一招「伏魔式」，雙手猛地襲向$n$l",
        "force" : 250,
        "attack": 55,
        "dodge" : 70,
        "parry" : 60,
        "damage": 20,
        "lvl"   : 0,
        "damage_type": "瘀傷"
]),
([      "action": "$N左拳直出，鋼勁有力，一招「天玄式」砸$n的$l",
        "force" : 270,
        "attack": 60,
        "dodge" : 80,
        "parry" : 80,
        "damage": 35,
        "lvl"   : 30,
        "damage_type": "瘀傷"
]),
([      "action": "$N左右雙拳齊出，風聲呼呼，一招「游龍式」擊向$n$l",
        "force" : 310,
        "attack": 75,
        "dodge" : 100,
        "parry" : 100,
        "damage": 50,
        "lvl"   : 60,
        "damage_type": "瘀傷"
]),
([      "action": "$N一拳揮出，招式簡單之極，但是這招卻使得不卑不亢，氣勢雄渾，一招「魔驚式」拍向$n的$l",
        "force" : 330,
        "attack": 75,
        "dodge" : 110,
        "parry" : 100,
        "damage": 55,
        "lvl"   : 90,
        "damage_type": "瘀傷"
]),
([      "action": "$N使一招「大伏魔式」，$n心中一驚，已被$N雙拳籠罩",
        "force" : 350,
        "attack": 80,
        "dodge" : 130,
        "parry" : 120,
        "damage": 66,
        "lvl"   : 120,
        "damage_type": "瘀傷"
]),
([      "action": "$N拳法頓快，使出「無誨式」，轉眼間，數拳已襲向$n",
        "force" : 380,
        "attack": 85,
        "dodge" : 140,
        "parry" : 130,
        "damage": 80,
        "lvl"   : 150,
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大伏魔拳必須空手。\n");

        if( query("str", me)<32 )
                return notify_fail("你先天臂力太弱，無法練大伏魔拳。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力太弱，無法練大伏魔拳。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法練大伏魔拳。\n");

        if ((int)me->query_skill("unarmed", 1) < 120)
                return notify_fail("你的基本拳腳火候不夠，無法練大伏魔拳。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("dafumo-quan", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的大伏魔拳。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("dafumo-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("dafumo-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 50);
        addn("neili", -60, me);
        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        if ((int)me->query_skill("dafumo-quan", 1) < 100
           || ! living(me)
            || query_temp("weapon", me )
            || query_temp("weapon", ob) )
                return;

        ap = ob->query_skill("force") + ob->query_skill("count", 1);
        dp = me->query_skill("unarmed", 1) / 2 +
             me->query_skill("dafumo-quan", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "左臂隨意格擋，$N" + HIG
                                            "這招力道竟然落空。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIG "$n" HIG "怒喝一聲，出拳格擋，拳風呼呼，$N" HIG
                                            "頓覺得雙臂痠麻。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "不退反進，一拳直出，鋼勁無比，$N"
                                            HIG "連忙收招回縮，不敢硬碰。\n" NOR]);
                        break;
                }
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"dafumo-quan/" + action;
}
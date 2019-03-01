// tiyunzong.c 梯雲縱

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "只見$n一招"HIW"「白鶴沖天」"NOR"，身體向上筆直地縱起丈余，躲過了$N這一招。\n",
        "$n一個"BLU"「鷂子翻身」"NOR"，向後縱出數丈之遠，避開了$N的凌厲攻勢。\n",
        "$n使出"HIY"「大鵬展翅」"NOR"，向一旁飄然縱出，輕輕著地。\n",
        "但是$n一招"HIC"「白鶴沖天」"NOR"身形飄忽，輕輕一縱，早已避開。\n",
        "$n身隨意轉，一招"HIB"「鷂子翻身」"NOR"倏地往一旁挪開了三尺，避過了這一招。\n",
        "可是$n一招"YEL"「大鵬展翅」"NOR"側身一讓，$N這一招撲了個空。\n",
        "卻見$n足不點地一招"HIC"「白鶴沖天」"NOR"，往旁竄開數尺，躲了開去。\n",
        "$n身形微晃，一招"MAG"「鷂子翻身」"NOR"有驚無險地避開了$N這一招。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("你基本輕功修為有限，難以修煉梯雲縱。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你內力修為太淺，難以修煉梯雲縱。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<50 || query("neili", me)<10 )
                return notify_fail("你的體力太差了，無法練習梯雲縱。\n");
        me->receive_damage("qi", 50);
        addn("neili", -10, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.1; }

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("tiyunzong", 1);

        if (lvl < 50)  return 0;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 50;
        if (lvl < 250) return 70;
        return 80;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("tiyunzong", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("tiyunzong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一招「白鶴沖天」，身體向上筆直地縱起丈余，"
                                            "$N頓然失去目標，勁招失手！\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "一個「鷂子翻身」，向後縱出數丈之遠，"
                                            "$N一招失手，攻守之勢已露破綻！\n" NOR]);
                        if (! ob->is_busy())
                        ob->start_busy(random(2));
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "使出「大鵬展翅」，向一旁飄然縱出，"
                                            "已然毫發無損地輕輕著地。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一招「白鶴沖天」，身體向上筆直地縱起丈余，"
                                 "可是$N" HIY "早以看破$n的企圖。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "一個「鷂子翻身」，向後縱出數丈之遠，"
                                 "$N立刻跟上隨手揮招直入，進襲$n！\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "使出「大鵬展翅」，向一旁飄然縱出，"
                                 "突然發現$N速度更快，也先等候在此！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}


string perform_action_file(string action)
{
      return __DIR__"tiyunzong/" + action;
}

int help(object me)
{
        write(HIC"\n梯雲縱："NOR"\n");
        write(@HELP

    梯雲縱為武當最高輕功心法。

        學習要求：
          太極神功10級
HELP
        );
        return 1;
}

// zhuangzi-wu.c 莊子舞

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "可是$n側身微微一讓，$N這一招撲了個空。\n",
        "卻見$n足不點地，往旁竄開數尺，躲了開去。\n",
        "$n身形微晃，有驚無險地避開了$N這一招。\n",
        "$n跨出幾步，落點怪異莫測，讓$N這一招沒有發揮任何作用。\n",
        "$n自顧自的走出幾步，渾然不理$N出招攻向何處。\n",
        "$N這一招眼看就要擊中，可是$n往旁邊一讓，去點之妙，實在是匪夷所思。\n",
        "$n往前一邁，忽然後退，恰恰避開$N這一招，有驚無險。\n",
});

int valid_enable(string usage) 
{ 
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("zhuangzi-wu", 1);
        if (lvl > 300) lvl = 300;

        if( query("dex", me)<26 )
                return notify_fail("你先天身法太差，無法學習莊子舞。\n");

        if( query("max_neili", me)<2400+lvl*15 )
                return notify_fail("你按照莊子舞所示的步法隨意走了兩下，頓時"
                                   "只感頭暈目眩，看來是內力不濟。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("zhuangzi-wu", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 3/5 +
             me->query_skill("zhuangzi-wu", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : MAG "只見$n" MAG "足尖在地面輕輕一點，整個身"
                                            "子頓時凌空飄起，輕而易舉躲開了$N" MAG "的招"
                                            "式。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : MAG "可是$n" MAG "蠻腰微微一顫，步法宛如行雲"
                                            "流水，輕飄飄的落在一旁，頓時使$N" MAG "的攻"
                                            "勢落空。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : MAG "但見$n" MAG "微微一笑，身形輕展，整個人"
                                            "竟踏空飄起，待$N" MAG "一招擊空後，又翩翩而"
                                            "落，晃至$N" MAG "跟前。\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "可$n" MAG "竟絲毫不理會$N" MAG "的招數，"
                                            "徑自迎面奔上，幻出無數倩影翩翩起舞，$N" MAG
                                            "勘不透虛實，唯有收招。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "只見$n" HIY "足尖輕點地面，凌空飄然而"
                                 "起，可$N" HIY "遁影擒蹤，一聲冷笑，隨即飛"
                                 "身撲上。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "蠻腰微微一顫，步法宛如行雲流"
                                 "水，輕飄而落，可$N" HIY "毫不理會，反手又"
                                 "攻出一招。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "微微一笑，身形輕展，整個人竟"
                                 "踏空飄起，可又見$N" HIY "也隨即飄起，在半"
                                 "空攻出數招。\n" NOR;
                        break;
                default:
                        result = HIY "但見$n" HIY "身形一展，幻出無數倩影翩"
                                 "翩起舞，可$N" HIY "不假思索攻出一招，正是"
                                 "實影所在。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("zhuangzi-wu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 300) return 90;
        if (lvl < 350) return 100;
        if (lvl < 400) return 120;
        return 140;
}

int practice_skill(object me)
{
        if (me->query_skill("zhuangzi-wu", 1) < 180
            && query("family/family_name", me) != "紅花會" )
                return notify_fail("你對莊子舞瞭解不夠，還不足以自行鍛鍊。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太差了，難以練習莊子舞。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠了，無法練習莊子舞。\n");

        me->receive_damage("qi", 50);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhuangzi-wu/" + action;
}
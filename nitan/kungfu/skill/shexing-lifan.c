inherit SKILL;
#include <ansi.h>

string *dodge_msg = ({
        "只見$n清嘯一聲，身體向上筆直地縱起丈餘，躲過了$N這一招。\n",
        "$n身形飄忽，靈巧無比，輕輕向後一縱，早已避開。\n",
        "只見$n身行隨意轉，如同水蛇一般，倏地往一旁挪開了三尺，避過了這一招。\n",
        "可是$n着地一個猛翻，側身一讓，$N這一招撲了個空。\n",
        "卻見$n蠻腰擺動，足不點地，往旁竄開數尺，躲了開去。\n",
        "$n飛身躍起，在半空中一個翻滾，身形一晃，有驚無險地避開了$N這一招。\n"

});

int valid_enable(string usage) 
{ 
        return (usage == "dodge") || (usage == "move"); 
}

mapping *action = ({
([      "action":"$N身行忽而隨意轉動，如同水蛇一般，忽而飛身躍起，在半空中一個翻滾，招式怪異之極"
]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<150 )
                return notify_fail("你的體力太差了，不能練習蛇行狸翻。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力太差了，不能練習蛇行狸翻。\n");

        me->receive_damage("qi", 100);
        addn("neili", -150, me);
        return 1;
}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shexing-lifan", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 2 / 5 +
             me->query_skill("shexing-lifan", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "身形飄忽，靈巧無比，$N" HIW
                                            "頓覺眼前幻象萬千，這招竟然落空。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "猛然飛身躍起，在半空中一個翻滾，"
                                            "竟避開了$N" HIW "這招。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$N" HIW "一招攻出，$n" HIW "身形猛轉，猶"
                                            "如靈蛇一般，輕鬆地避開了$N" HIW "這招，令$N" HIW 
                                            "難以琢磨。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "但見$n" HIY "身形飄忽不定，靈巧無比，"
                                 "頓時出現無數幻影，令人眼花繚亂。可是$N"
                                 HIY "招式卻是毫無停滯，隨意施展。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "猛然飛身躍起，在半空中一個翻滾。然而$N"
                                 HIY "早已看破其中虛實，招式忽轉，襲向$n" HIY "。\n" NOR;
                        break;

                default:
                        result = HIY "但見$n" HIY "身形猛轉，猶如靈蛇一般，令人難以琢磨。$N"
                                 HIY "微微一笑，招式猛然加快。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

string perform_action_file(string action)
{
        return __DIR__"shexing-lifan/" + action;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("shexing-lifan", 1); 

        if( lvl >= 150 && 
            !query("can_perform/shexing-lifan/guiyuan", me) )  
        { 
                tell_object(me, HIC "你通曉了蛇行狸翻「" HIR "九陰歸元" HIC "」的奧祕。\n" NOR);     
                set("can_perform/shexing-lifan/guiyuan", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
} 


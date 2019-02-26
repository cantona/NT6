inherit FORCE;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N身形一轉，拳頭攜着疾速旋轉的氣流揮出，疾如閃電，勢如雷霆，擊向$n",
        "dodge"  : 50,
        "force"  : 300,
        "attack" : 100,
        "parry"  : 21,
        "damage" : 160,
        "lvl"    : 0,
        "damage_type": "震傷" 
]), 
([      "action" : "$N身形一轉，拳頭攜着疾速旋轉的氣流揮出，疾如閃電，勢如雷霆，擊向$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 200,
        "lvl"    : 100,
        "damage_type": "震傷"
]), 
([      "action" : "$N身體一側，一掌凌空劈出，一股凜冽的氣流頓時澎湃湧至$n的$l處",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 250,
        "lvl"    : 150,
        "damage_type": "震傷"
]),
([      "action" : "$N雙腿微曲，右掌平伸，左掌運起蛤蟆功勁力，呼的一聲推向$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 152,
        "parry"  : 37,
        "damage" : 200,
        "lvl"    : 200,
        "damage_type": "震傷"
]), 
([      "action" : "$N閉眼逼住呼吸，猛躍而起，眼睛也不及睜開，便向$n推了出去",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 202,
        "parry"  : 53,
        "damage" : 300,
        "lvl"    : 220,
        "damage_type": "震傷"
]),
([      "action" : "$N攻勢忽緩而不疏，$w變化無常，捉摸不定向$n慢慢捲去",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 243,
        "parry"  : 67,
        "damage" : 350,
        "lvl"    : 250,
        "damage_type": "震傷"
]), 
});

int valid_enable(string usage)
{ 
        int lvl = (int)this_player()->query_skill("jiuyin-hamagong", 1);

        if (lvl >= 200)    
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";
       
}

string main_skill()
{
        return "jiuyin-hamagong";

}
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-hamagong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}


mapping sub_skills = ([
        "nijiuyin-xinfa" : 250, 
        "hama-gong" : 250,            
        ]);

int valid_learn(object me)
{
        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：這九陰蛤蟆功陰毒異常，估計會傷及自"
                                   "身，還是別練為妙。\n");
                                   
        if( query("gender", me) == "無性" )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的九陰蛤蟆功。\n");
        if ((int)me->query_skill("jiuyin-hamagong", 1) < 240)
                return notify_fail("你對九陽蛤蟆功理解還不夠深。想來想去總想不通!\n"); 

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("你的基本毒技火候不足，難以領會蛤蟆功。\n");        
                
        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jiuyin-hamagong", 1))
                return notify_fail("你的基本拳腳水平有限，難以領會更高深的九陰蛤蟆功。\n"); 

        if( query("max_neili", me)<4300 )
                return notify_fail("你現在的內力修為不足，難以領會九陰蛤蟆功。\n");

        if( query("str", me)<30 )
                return notify_fail("你先天膂力不夠，無法領悟九陰蛤蟆功。\n");
                
        if( query("con", me)<34 )
                return notify_fail("你先天根骨不夠，無法領悟九陽蛤蟆功。\n");

        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("你的基本內功火候還不夠，還不能學習九陽蛤蟆功。\n");

        return ::valid_learn(me);
}

int get_finish(object me)
{
        object ob;

        if( query("gender", me) == "無性" )
        {
                tell_object(me, "你演練完畢，只感氣血上湧，看來自己陰陽不調，無法演練九陰蛤蟆功。\n" NOR);
                return 0;
        }

        if( query("character", me) == "光明磊落" )
        {
                tell_object(me, "你演練完畢，覺得九陰蛤蟆功邪氣縱橫，氣度狡黠，自己怎麼也無法將其合一。\n" NOR);
                return 0;
        }

        if( query("character", me) == "狡黠多變" )
        {
                tell_object(me, "你演練完畢，覺得九陰蛤蟆功邪氣縱橫，氣度狡黠，自己怎麼也無法將其合一。\n" NOR);
                return 0;
        }

        if( query("con", me)<34 )
        {
                tell_object(me, "你演練完畢，發現自己的先天根骨太差，無法將九陰蛤蟆功內的武功合一。\n");
                return 0;
        }

        if( query("str", me)<30 )
        {
                tell_object(me, "你演練完畢，發現自己的先天膂力孱弱，無法將九陰蛤蟆功內的武功合一。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 250)
        {
                tell_object(me, "你覺得九陰蛤蟆功內的武功都極其深奧，看來多研究一下學問可能更有幫助。\n");
                return 0;
        }
        
        if (me->query_skill("jiuyin-shengong", 1) > 1)
        {
                tell_object(me, "你已經學會九陰神功了，怎麼都不能逆轉成功。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 190)
        {
                tell_object(me, "你演練完畢，發現自己的武學修養尚待提高，暫且無法將九陰蛤蟆功內的武功合一。\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "你覺得自己真氣不繼，無法繼續演練九陰蛤蟆功。\n");
                return 0;
        }

        if (random(10) < 6)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通，將二者合一。\n");
                return 0;
        }

        tell_object(me, HIW "一陣凡塵往事湧上心頭，你默唸九陰蛤蟆功，一股莫名的真氣由兩足湧至頭部百匯穴。\n"
                        "不由心意零亂，隨即兩手撐地，雙腳倒立向上，“嘎”一聲長嗚，聲音猶若蛙叫。響徹天地。\n"
                        "蛙嗚數聲後，你但覺全身無比舒暢!似乎功力比以往提升了數倍!\n" NOR);
        CHANNEL_D->do_channel(me,"rumor",sprintf("忽然%s“嘎”一聲長嗚，聲音猶若蛙叫,響徹天地。",query("name", me)));
        CHANNEL_D->do_channel(me,"rumor",sprintf("%s因禍得福經歷萬難，終於逆轉經脈領悟出西毒歐陽峯不傳祕技九陰蛤蟆功了。",query("name", me)));
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int practice_skill(object me)
{
        return notify_fail("九陰蛤蟆功只能用學(learn)的來增加熟練度。\n");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("jiuyin-hamagong", 1);

        if (damage_bonus < 150
           || lvl < 200
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "jiuyin-hamagong"
           || me->query_skill_mapped("unarmed") != "jiuyin-hamagong"
           || me->query_skill_prepared("unarmed") != "jiuyin-hamagong")
                return 0;

        if (damage_bonus / 4 > victim->query_con())
        {
                addn("neili", -40, me);
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                return WHT "只見$N" HIR "“嘎”"NOR"" WHT "一聲長嗚，隨即疾速撲至身前，全力擊出一掌$n始料不及\n"
                       "這一掌如此突然，只能硬接此招，霎時全身一顫，經脈受震，噴出一口鮮血！\n" NOR;
        }
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiuyin-hamagong", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-hamagong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyin-hamagong/exert/" + action;
}


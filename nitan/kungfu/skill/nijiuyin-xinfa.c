#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nijiuyin-xinfa", 1);
        return lvl * lvl * 15 * 14 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N身形一轉，拳頭攜着疾速旋轉的氣流揮出，疾如閃電，勢如雷霆，擊向$n",
        "dodge"  : 50,
        "force"  : 300,
        "attack" : 120,
        "parry"  : 21,
        "damage" : 58,
        "lvl"    : 0,
        "damage_type": "震傷" 
]), 
([      "action" : "$N身形一轉，拳頭攜着疾速旋轉的氣流揮出，疾如閃電，勢如雷霆，擊向$n",
        "dodge"  : 50,
        "force"  : 332,
        "attack" : 112,
        "parry"  : 37,
        "damage" : 61,
        "lvl"    : 180,
        "damage_type": "震傷"
]), 
([      "action" : "$N身體一側，一掌凌空劈出，一股凜冽的氣流頓時澎湃湧至$n的$l處",
        "dodge"  : 67,
        "force"  : 360,
        "attack" : 122,
        "parry"  : 53,
        "damage" : 72,
        "lvl"    : 220,
        "damage_type": "震傷"
]),
([      "action" : "$N攻勢忽緩而不疏，$w變化無常，捉摸不定向$n慢慢捲去",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 143,
        "parry"  : 67,
        "damage" : 81,
        "lvl"    : 240,
        "damage_type": "震傷"
]), 
});

int valid_enable(string usage)
{               
                return usage == "force";
}

int valid_force(string force) { return 1; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("nijiuyin-xinfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        int i,skill,damage,lvl;
        
        skill = me->query_skill("nijiuyin-xinfa",1);
        if( query("jing", me)<60 )
                return notify_fail("你的精力太低了。\n");
                
        if( query("qi", me)<200 )
                return notify_fail("你的體力不夠練逆九陰心法。\n");
         
        if (me->query_condition("jiuyin-except"))
                return notify_fail("你完全無法控制自已，還哪裏有心情去修煉逆九陰心法？\n"); 
        
        if (me->query_skill("jiuyin-shengong", 1) > 1)
        {
                return notify_fail("你已經學會九陰神功了，怎麼還能去修煉逆九陰心法？\n");
        }       
        
        if( query("sleep_room", environment(me)) )
                return notify_fail("竟然在這麼多人休息的地方練這種武功，你是白痴啊？\n");        
        
        if( skill>100 && query("shen", me)>-100 )
                return notify_fail("這種邪惡武功不是俠義道當練的。\n");
        
        if( query("neili", me)<400 && random(10)<3 )
        {      
                message_vision(HIY "突然你但覺一股無明真氣衝至你頭頂。隨即你只感到全身就像被撕裂般痛苦!\n"NOR,me);         
                me->apply_condition("jiuyin-except", skill + (int)me->query_condition("jiuyin-except"));
                return 1;
        }
        if( query("neili", me)<200 )
        
                return notify_fail("你的內力不夠練逆九陰心法。\n");
        
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 20);
        addn("neili", -50, me);
        tell_room(environment(me), 
MAG"只見"+query("name", me)+"雙目緊閉，凝神聚氣、雙手抱圓，頭頂不時地冒出一絲絲白氣，隨之
雙手之間形成一股氣流，忽然只見"+query("name", me)+"臉色痛苦無比，鮮血由嘴角慢慢逸出。\n");

        return 1;
}

void skill_improved(object me)
{
    tell_object(me, HIR "你忽然從心底生出一股惡念：嘿嘿.....我要成為天下第一......誰敢與我為敵！\n" NOR );
    addn("shen", -100, me);
}

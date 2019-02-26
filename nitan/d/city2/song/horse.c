#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW "高頭大馬" NOR, ({"zhan ma", "horse", "ma"}));
        set("race", "野獸");
        set("age", 3);

        set("combat_exp", 500000);
        set("long", 
                "一匹高頭大馬，全身雪白的毛髮，煞是神俊。\n");

        set("limbs", ({ "頭部", "身體", "蹄子", "尾巴" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("str", 20+random(10));
        set("con", 20+random(5));
        set("dex", 20+random(5));
        set("age", 20+random(30));   
        set("ridable", 1); 
 
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("ride_prop/dodge",100);
        set("ride_prop/defense",100);

        set("chat_chance", 5);
        set("chat_msg", ({
                 HIW"戰馬不住地低鳴，蹄子不挺地刨打着地面。\n"NOR,
        }) );

        setup();
}


void die()
{
        destruct(this_object());
        return;
}
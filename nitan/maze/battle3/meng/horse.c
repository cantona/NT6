#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW"蒙古馬"NOR, ({"menggu ma", "horse", "ma"}));
        set("race", "野獸");
        set("age", 3);

        set("combat_exp", 500000);
        set("long", 
                "一匹蒙古高頭大馬，全身毛發黝黑發亮，煞是威風神俊。\n");

        set("limbs", ({ "頭部", "身體", "蹄子", "尾巴" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("str", 20+random(10));
        set("con", 20+random(5));
        set("dex", 20+random(5));
        set("age", 20+random(30));   
 
        set("ridable", 1); 
        set("combat_exp", 300);
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("ride_prop/dodge",100);
        set("ride_prop/defense",100);

        set("no_get",1);
        set("no_drop",1);
        set("no_put",1);

        set("chat_chance", 5);
        set("chat_msg", ({
              CYN"蒙古馬呼哧呼哧，蹄子不停地刨著地。\n"NOR,
        }) );

        setup();
}


void die()
{
        destruct(this_object());
        return;
}
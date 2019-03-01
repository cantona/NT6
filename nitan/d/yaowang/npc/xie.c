#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL"蠍子"NOR, ({ "xie zi", "xie" }) );
        set("race", "野獸");
        set("age", 2);
        set("long", "一只巴掌大的毒蠍，尾巴高高地翹著。\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "頭部", "身體", "尾巴", "鉗子" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 3000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 10);
        set_temp("apply/defence",30);
        set_temp("apply/armor",10);

        set("yaowang_zhuo",1);
        setup();
}

void die()
{
        object ob1;
        message_vision(HIR"$N身體僵硬，動了兩下腿，$N死了。\n"NOR, this_object());
        if(random(10)>8)
        {
        ob1 = new(__DIR__"obj/xiedu");
        ob1->move(environment(this_object()));
        }
        destruct(this_object());
}
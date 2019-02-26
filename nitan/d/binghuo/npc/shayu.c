// shayu.c
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("鯊魚", ({ "sha yu", "sha" }) );
        set("race", "游魚");
        set("age", 20);
        set("long", "一隻生活在冰海的巨大鯨鯊。\n");
        set("attitude", "friendly");
        set("shen_type", 0);

        set("combat_exp", 100000);
        set_temp("apply/attack", 800);
        set_temp("apply/defense", 800);
        set_temp("apply/armor", 100);

        setup();
}


void die()
{
        object ob, corpse;
        message_vision("$N全身一陣劇烈的扭曲，終於安靜了下來，翻白眼死了。\n", this_object());
        if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
                ob = new("/clone/medicine/vegetable/shadan");
        ob->move(corpse);

        corpse->move(environment(this_object()));
        destruct(this_object());
}

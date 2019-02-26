// bear.c

inherit NPC;
#include <ansi.h>;

void create()
{
        set_name(CYN "黑熊" NOR, ({ "hei xiong", "bear","xiong" }) );
        set("race", "野獸");
        set("age", 20);
        set("long", "一隻兇猛的黑熊，形體碩大，人立而行。\n");
        set("attitude", "aggressive");

        set("limbs", ({ "熊頭", "熊身", "前爪", "後爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("unit", "只");

        set("combat_exp", 50000);
        set_temp("apply/attack", 200);
        set_temp("apply/defense", 280);
        set_temp("apply/armor", 120);

        setup();

        set("chat_chance", 10);
        set("chat_msg", ({
                "黑熊衝着你搖頭擺尾地，不知道是什麼意思。\n",
                "黑熊擠了擠鼻子，你覺得它好像在笑，頓時一陣緊張。\n",
        }));
}

void init()
{
        if (sscanf(base_name(environment()), "/d/guanwai/%*s") == 1 &&
            environment(query("outdoors", )) )
                kill_ob(this_player());
        else
        {
                remove_call_out("greeting");
                call_out("greeting", 1, this_player());
        }
}

void greeting(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        message_vision("$N憨憨的看着$n。\n",
                       this_object(), ob);
}

void die()
{
        object ob, corpse;


/*
        if (objectp(corpse = CHAR_D->make_corpse(this_object())))
        {
                corpse->move(environment(this_object()));
                destruct(this_object());
                ob = new("/d/guanwai/npc/xiongdan");
                ob->move(corpse);
        }
*/
        ob = new("/d/guanwai/npc/xiongdan");
        ob->move(this_object());
        ::die();
}

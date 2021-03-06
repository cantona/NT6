// tuying.c
// Last Modified by winder on Aug. 1 2002

// inherit NPC_TRAINEE;
inherit "/inherit/char/trainee";

void create()
{
        set_name("禿鷹", ({ "eagle", "ying", "tuying" }) );
        set("race", "飛禽");
        set("age", 15);
        set("long", "一隻生活在高原上，黑色的禿鷹，一身亂蓬蓬的羽毛，兇悍醜陋。\n");
        set("attitude", "aggressive");
        set("wildness", 9);
        set("msg_fail","$n一驚對着$N就啄，$N忙縮回手");
        set("msg_succ","$N一揮手，$n輕輕撲騰了幾下翅膀");
        set("msg_trained","$n飛了起來輕輕停到$N的肩上");
        set("auto_follow",1);

        set("str", 29);
        set("con", 40);
        set("dex", 45);
        set("int", 10);

        set("combat_exp", 12000);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 10);

        setup();

        set("chat_chance", 7);
        set("chat_msg", ({
                "「嘎~~嘎~~」禿鷹發出幾聲淒厲的哀叫。\n",
                "禿鷹突然從高空盤旋着朝你俯衝下來，停落在你不遠處。\n",
                "禿鷹猶猶豫豫地來回走着，貪婪的眼睛狠狠地盯着你。\n",
                "禿鷹撲騰了幾下翅膀。\n",
        }) );
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                this_object()->query_lord() != ob &&
                random(ob->query_kar() + ob->query_per()) < 5)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}
// yezhu.c

inherit NPC;

void create()
{
        set_name("野豬", ({ "pig", "yezhu" }) );
        set("race", "走畜");
        set("age", 4);
        set("long", 
"這是一只兇猛的野豬，長得極為粗壯，嘴裡還不斷發出可怕的哄聲。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("cor", 30);
        set("combat_exp", 1000);
        set("shen_type", -1);
        set("chat_msg_combat", ({
                (: this_object(), "random_move" :),
                "野豬大口大口地喘著氣：呼哧！呼哧！呼哧！呼哧！\n",
                "野豬突然跳了起來，眼睛惡狠狠地盯著你，看樣子想要撲過來。\n"
        }) );

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);

        setup();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) &&
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob);
        }
}
void die()
{
        object ob;
        message_vision("$N哇呀地慘嚎一聲，死了！\n", this_object());
        ob = new("/d/xiakedao/obj/pigdie");
        ob->move(environment(this_object()));
        destruct(this_object());

}

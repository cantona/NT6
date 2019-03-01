//laoren.c

inherit NPC;

void create()
{
        set_name("說書老人", ({"shuoshu laoren", "laoren"}) );
        set("gender", "男性" );
        set("age", 53);
        set("long","一位慈眉善目的老人，正在說書。\n");
        set("combat_exp", 6000);
        set("str", 30);
        set("attitude","heroism");

        setup();
        carry_object("/d/changan/npc/obj/changpao")->wear();
        add_money("silver", 10);
}

void init()
{
        remove_call_out ("says");
        call_out("says", random(3), this_object());
}

void says(object me)
{
        string *msgs = ({
                "$N繪聲繪色地說著書。\n",
                "$N滔滔不絕地說著書。\n",
                "$N說得眉飛色舞。\n",
                "$N說道：“欲知後事如何，且聽下回分解。”\n",
                "$N端起茶碗喝了幾口茶水，又開始接著說書。\n",
        });
        message_vision (msgs[random(sizeof(msgs))], me);
        remove_call_out("says");
        call_out("says",random(40),me);
}
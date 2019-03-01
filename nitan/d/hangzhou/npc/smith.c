// smith.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("鐵匠", ({ "tiejiang", "smith" }));
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/d/city/obj/changjian",
                "/d/city/obj/hammer",
                "/d/beijing/obj/tudao",
                "/d/xingxiu/obj/tiegun",
                "/d/city/obj/gangdao",
        }));
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
}
void init()
{
        object ob,me;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say("鐵匠說道：歡迎這位"+RANK_D->query_respect(ob)+"光臨，請隨便參觀。\n");
}

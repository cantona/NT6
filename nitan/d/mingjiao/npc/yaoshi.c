// yaoshi.c 藥師
inherit NPC;
inherit F_VENDOR;
void create()
{
        set_name("藥師", ({ "yao shi", "yao", "shi" }) );       
        set("gender", "男性" );
        set("age", 34);
        set("long","這是一位教主親手調教出來的藥師。\n");
        set("combat_exp", 400);
        set("unique", 1); 
        set("attitude", "peaceful");
        set("vendor_goods", ({
        }));
        setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
}

void init()
{       
        object ob;
        ::init();
        if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
       if( !ob || environment(ob) != environment() ) return;
        command("say 這位"+RANK_D->query_respect(ob)+"請了，請問要買什麼藥？");
}

// laoban.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("酒館老板", ({ "lao ban" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "這位酒館老板滿身狗肉香，點頭哈腰著對你笑著。\n");
        set("combat_exp", 500);
        set("attitude", "friendly");
        set("no_get", "1");
        set("vendor_goods", ({
                __DIR__"obj/gourou",
                __DIR__"obj/gouroutang",
                __DIR__"obj/map",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{        
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
/*
                if( (myfam=query("family", ob) )
                && myfam["family_name"] == "丐幫" 
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
*/
                { 
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "酒館老板得意的說道：這麼冷的天，喝碗狗肉湯是最能暖和身子的！\n");
                        break;
                case 1:
                        say( "酒館老板搓了搓手，說道：這位" + RANK_D->query_respect(ob)
                                + "，狗肉大補啊，嘗嘗吧。\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n酒館老板大喝一聲：你這臭要飯的進來幹什麼？ 給我滾出去！\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);
        
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        ob->move("/d/guanwai/nancheng");
        message("vision","只聽“乒”地一聲，"+query("name", ob)+
                "被人從香肉館裡一腳踢了出來，狼狽萬狀的逃開了。\n", environment(ob), ob);
}

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("錢伯", ({ "qian bo", "qian", "bo" }));
        set("nickname", HIM "見利忘義" NOR);
        set("title", "雜貨舖老板");
        set("long", @LONG
一個胖胖的老板，賣一些普通的物品。可使用 list 查看可購買的物品。
LONG);
        set("gender", "男性");
        set("age", 44);
        set("per", 24);
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_temp("apply/damage", 25);
        set("combat_exp", 800000);
        set("no_get", "1");
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/xingxiu/obj/fire",
                "/d/henshan/obj/mujian",
                "/d/city/obj/rrose",
                "/d/city/obj/yrose",
                "/clone/misc/wood",
        }));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{        
        object ob; 

        ob = this_player();

        ::init(); 
        add_action("do_buy", "buy"); 
        add_action("do_list", "list"); 

        if( interactive(ob) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say(CYN "錢伯笑著說道：這位" + RANK_D->query_respect(ob)+ "你需"
            "買些什麼，請隨便看（輸入指令 list 查看）。\n" NOR);

        return;
}












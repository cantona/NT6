#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("黃智強", ({ "huang zhiqiang", "zhiqiang", "huang" }));
        set("nickname", HIM "食人魔" NOR);
        set("title", "雜貨鋪老闆");
        set("long", @LONG

LONG);
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 20);
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
                "/d/henshan/obj/jia",
                "/d/item/obj/chanhs",
                "/d/city/obj/rrose",
                "/d/city/obj/yrose",
                "/clone/misc/wood",
                "/clone/misc/shoeshine",
                "/clone/misc/brush",
                "/clone/misc/youer",

        }));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{        
        object ob; 

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say(CYN "黃智強笑着説道：這位" + RANK_D->query_respect(ob)+ "你需"
            "買些什麼，請隨便看。\n" NOR);

        return;
}












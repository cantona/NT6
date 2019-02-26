#include <ansi.h> 

inherit NPC;

void create()
{
        set_name("迎賓小姐", ({ "yinbing xiaojie", "xiaojie", "yinbing" }) );
        set("long", "這是一位美麗的迎賓小姐，她正對着你甜甜的笑呢。\n");
        set("title", HIR "【地獄雜誌】" HIW "辦公室" NOR); 
        set("gender", "女性");
 
        set("age", 21);
        set("per", 30);
        setup();
        carry_object("/d/city/npc/obj/qunzi")->wear();
}

void init()
{       
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "迎賓小姐笑咪咪地説道：這位" + RANK_D->query_respect(ob)
                                + "，歡迎光臨。\n");
                        break;
                case 1:
                        say( "迎賓小姐甜甜的説道：這位" + RANK_D->query_respect(ob)
                                + "，請進請進。\n");
                        break;
        }
}


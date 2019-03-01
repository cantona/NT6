// haojie.c
#include <ansi.h>;
inherit NPC;

int ask_back();
void create()
{
        set_name("太湖豪傑", ({ "hao jie", "jie" }));
        set("gender", "男性");
        set("age", 25);
        set("long", "這是歸雲莊屬下的在太湖劫富濟貧的太湖豪傑。\n");
        set("combat_exp", 100000);
        set_skill("dodge", 50);
        set_skill("lingxu-bu", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("changquan", 50);
        map_skill("unarmed", "changquan");
        map_skill("parry", "changquan");
        map_skill("dodge", "lingxu-bu");
        set("shen_type", 1);
        set("chat_msg", ({
                "太湖豪傑道：“要返航，就告訴我....\n",
        }));
        set("inquiry", ([
                "返航": (:ask_back:),
        ]));
        setup();

        carry_object("/clone/misc/cloth")->wear();
}
void init()
{        
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        tell_object(ob,"太湖豪傑道：“這位"+RANK_D->query_respect(ob)+"，要返航，就告訴我....”\n");
}

int ask_back()
{
        object ob = this_player();
        delete("exits/out", environment(ob));
        message_vision("船上羣盜齊聲應道：扯帆，回去慶功嘍！\n", ob);
        message_vision("船伕升起帆，船就向歸雲莊航行。\n", ob);
        tell_object(ob, CYN "你率船在湖上破浪前行，威風凜凜.......\n" NOR ) ;
        call_out("rguiyun", 10 , ob );
        return 1 ;
}
void rguiyun( object ob )
{
        object ship, matou;
        if(!( ship = find_object("/d/guiyun/ship")) )
                ship = load_object("/d/guiyun/ship");
        if(!( matou = find_object("/d/guiyun/matou")) )
                matou = load_object("/d/guiyun/matou");
        tell_object(ob , "戰船在一陣陣風浪聲中靠上了碼頭。\n" ) ;
        set("exits/out", "/d/guiyun/matou", ship);
}

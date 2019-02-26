// kid.c

inherit NPC;

void create()
{
        set_name("女孩",({ "girl" }) );
        set("gender", "女性" );
        set("age", 12);
        set("long", 
"這是個農家少女，雖然只有十二、三歲，身材已經開始發育。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
        set("shen", 100);
        set("shen_type", 1);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        say ("小女孩天真地笑着説：去桃花島呀，要從嘉興出海的。\n");
        return;
}

// gongzi.c
inherit NPC;

void create()
{
        set_name("公子哥", ({ "gongzi" }) );
        set("gender", "男性" );
        set("age", 19);
        set("long", "這是個流裡流氣到處揩油揮霍的花花公子。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 21);
        set("int", 23);
        set("con", 22);
        set("dex", 20);
        
        set("max_qi", 400);
        set("max_jing", 200);
        set("neili", 100);
        set("max_neili", 100);
        set("combat_exp", 30000+random(10000));
        set("score", 10000);
        setup();
        add_money("silver", 10);
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
        if( query("gender", ob) == "女性" )
        {
            if(random(2)==1)
                say("公子哥擰了一下"+query("name", ob)+"的臉蛋，一臉壞笑道："+RANK_D->query_respect(ob)+
                     "長得好象還很不賴嘛，陪我玩玩可好？\n");
        else
                say("公子哥一眼看到"+query("name", ob)+"頓時大樂：這位"+RANK_D->query_respect(ob)+
                     "來得正好，走，樂樂去？\n");
          }

}
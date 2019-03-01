inherit NPC;


void create()
{
        set_name("挑菜老頭", ({ "tiaocai laotou","laotou" }) );
        set("gender", "男性" );
        set("age",60);
        set("inquiry", ([
                "路" : "一直沿著石階上到盡頭就是了。\n",
                        ]) );
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set_wugong("unarmed",60,60,1);
	set_xiuwei("unarmed",50);
        setup();
        carry_object(__DIR__"obj/linen")->wear();
}

void init()
{
        object ob;
        ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("greeting");
            call_out("greeting",1,ob);
            }
}

void greeting(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("挑菜老頭對你鄭重其事地說："+RANK_D->query_respect(ob)
            +"，聽說這崆峒山上可有神仙呀。\n");
        }

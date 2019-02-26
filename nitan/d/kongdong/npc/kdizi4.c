inherit NPC;


void create()
{
        set_name("掃地道士", ({ "saodi daoshi","daoshi" }) );
        set("title","崆峒弟子");
        set("gender", "男性" );
        set("class","taoist");
        set("age",40);
	set_wugong("dahong-quan",40,40,1);
	create_family("崆峒派", 2, "弟子");
	set_xiuwei("unarmed",200);
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set("apply_food",15);
        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}

/*void init()
{
        object ob;
       ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("greeting");
            call_out("show_msg",1,ob);
            }
        add_action("do_yao","yao");
}

void show_msg(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("這幾個小道士正手忙腳亂地引火做飯，沒有注意到你。\n");
}

int do_yao(string arg)
{
        object ob;
        ob = this_player();
        if(!arg || (arg!="food" && arg!="食物") )
        {
                tell_object(ob,"小道士轉過身來：你要什麼？\n");
                return 1;
        }

        if(ob->query("family/family_name")!="崆峒派")
        {
               message_vision("小道士對着$N搖了搖頭説：這位施主，實在對不起，\n"
                        "齋飯還沒有做好，煩請多等一會兒。\n");  
               return 1;
        }
        printf("小道士忙説：這位%s，飯還沒好，我先找給你點東西充飢吧。\n",
                (ob->query("gender")=="男性") ? "師兄" : "師姐" );
        message_vision("小道士在食櫥裏翻出一塊素餅和一個葫蘆。\n",ob);
        message_vision("小道士給$N一塊素餅。\n",ob);
        message_vision("小道士給$N一個葫蘆。\n",ob); 
        new(__DIR__"obj/subing")->move(ob);
        new(__DIR__"obj/hulu")->move(ob);
        return 1;
}

int accept_object(object who, object ob)
{
        if(ob->value() >= 1000)
        {
                message_vision("小道士遲疑地接過"+ob->name()+"，嘴裏嘟囔着：\n"
                "這怎麼好意思呢？\n",who);
                message_vision("小道士想了想，從食櫥裏拿給&N一塊素餅和一個葫"
                        "蘆，\n説：要有人問起，你可別説是我拿給你的。\n",who);
                message_vision("小道士轉過身去，繼續引火。\n",who);
                new(__DIR__"obj/subing")->move(who);
                new(__DIR__"obj/hulu")->move(who);
                return 1;
        }
        else 
        {
                message_vision("小道士搖搖頭：師傅説過，不能隨便要別人的東西。\n",who);
                return 0;
        }
}
*/
                

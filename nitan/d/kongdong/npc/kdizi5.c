inherit NPC;


void create()
{
        set_name("燒火小道士", ({ "shaohuo daoshi","daoshi" }) );
        set("title","崆峒弟子");
        set("gender", "男性" );
        set("class","taoist");
        set("age",16);
	create_family("崆峒派", 2, "弟子");
	set_wugong("dahong-quan",60,60,1);
	set_wugong("jiben-qinggong",60,60,1);
	set_xiuwei("unarmed",250);
	set_xiuwei("dodge",100);
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set("food_apply",15);
        setup();
        carry_object(__DIR__"obj/cloth3")->wear();
}

void init()
{
        object ob;
        if(interactive(ob=this_player()) && !is_fighting()){
		remove_call_out("show_msg");
            call_out("show_msg",1,ob);
            }
        add_action("do_yao","yao");
}

void show_msg(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("這幾個小道士正手忙腳亂地引火做飯，沒有注意到你。\n");
}
int do_yao()
{
    object who = this_player();
    object me = this_object();

    if( who->query("family/family_name")!="崆峒派" || query("food_apply") < 0 )
        {
               message_vision("小道士對着$N搖了搖頭説：這位施主，實在對不起，\n"
                        "齋飯還沒有做好，煩請多等一會兒。\n",who);  
               return 1;
        }
    if ( (who->query("water") >= who->max_water_capacity()/2)
        &&(who->query("food") >= who->max_food_capacity()/2) ){
        return notify_fail("你吃得飽飽的，喝得足足來這裏添什麼亂？！\n");
        }

    message_vision("$N揉着肚子可憐兮兮得對$n説：\n"
        "“小師兄，還有剩飯嗎？實在是餓得不行了。”\n\n",who,me);
        printf("小道士忙説：這位%s，飯還沒好，我先找給你點東西充飢吧。\n",
                (who->query("gender")=="男性") ? "師兄" : "師姐" );
    who->set("food" ,who->max_food_capacity());
    who->set("water",who->max_water_capacity());

    return 1;
}

int accept_object(object who, object ob)
{
        if(ob->value() >= 1000)
        {
                message_vision("小道士遲疑地看着"+ob->name()+"，嘴裏嘟囔着：\n"
                "這怎麼好意思呢？\n",who);
                message_vision("小道士想了想，從食櫥裏拿給$N一塊素餅和一個葫"
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

                

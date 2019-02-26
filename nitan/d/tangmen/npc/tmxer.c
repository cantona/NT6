// yizhanxiaoer.c 小二

inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("驛站小二", ({"xiao er"}) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "這位小二正笑咪咪地閒著，還不時拿起茶壺喝上兩口。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("rank_info/respect", "小二哥");
        set("chat_chance", 1 );
        set("chat_msg", ({
                (:command("say "+"有錢的坐坐車，沒錢的跑跑腿。"):),
                ( : command("say "+"有錢你是大爺，沒錢我是大爺。") : ),
                ( : command("say "+"價格公平合理，賣買自由競爭！") : ),
        }) );       
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{      
         object ob; 
        
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) 
        {
           remove_call_out("greeting");
           call_out("greeting", 1, ob);
                
        }
        
        add_action("do_kill", "hit");          
        add_action("do_kill", "fight");          
        add_action("do_kill", "kill");          
}       

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("age", ob)<15)set_temp("paid_for", 1, ob);
                
        switch( random(2) ) 
        {
                case 0:
                        say( "小二笑咪咪地説道：這位" + RANK_D->query_respect(ob)
                                + "，到那兒去啊。\n");
                        break;
                case 1:
                        say( "小二喝了口茶，説道：這位" + RANK_D->query_respect(ob)
                                + "，長途旅行，本店優惠。\n");
                        break;
        }
}


int do_kill(string arg)
{    
            
        if ( arg == "xiao er" || arg == "xiaoer" )
        return 1;    
        return 0;    
}

int accept_object(object who, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                tell_object(who, "小二一哈腰，説道：多謝您老，請您老僱車。\n");

                set_temp("paid_for", 1, who);

                return 1;
        }

        return 0;
}            

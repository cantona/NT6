// xiaoer2.c 酒店小二

inherit KNOWER;
inherit F_DEALER;
#include <ansi.h>;
mixed do_ask(string arg);

void create()
{
        set_name("唐小一", ({ "tang xiaoyi", "tang", "xiaoyi" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "這位唐小一正笑咪咪地忙著，還不時拿起掛在脖子上的抹布擦臉。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("rank_info/respect", "小一哥");
        set("vendor_goods", ({
                "/clone/food/jiudai",
                "/clone/food/meat",
                "/clone/food/peanut",
        }));
        set("inquiry", ([ 
                "tangfei"   : (: do_ask :), 
        ])); 
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

        add_action("do_buy", "buy");
        add_action("do_list", "list");
        add_action("do_ask", "wen");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(3) ) 
        {
                case 0:
                        say( "唐小一笑咪咪地説道：這位" + RANK_D->query_respect(ob)
                                + "，進來喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "唐小一用脖子上的毛巾抹了抹手，説道：這位" + RANK_D->query_respect(ob)
                                + "，請進請進。\n");
                        break;
                case 2:
                        say ("這位客官，有什麼事的話您就問小的一聲，小的馬上就到！\n");
                        break;        
        }
}

mixed do_ask(string arg)
{    
        object me;
        mapping myfam;
        
        me=this_player();
        myfam=query("family", me);
        
        // say(HIC"來啦，有事你儘管問吧！\n"NOR);
                
        if( query_temp("yiwen", me) )
                return "你煩不煩啊，都和你説過了，你還來問我，我現有什麼都不知道了! \n";
         
        if ( !myfam || myfam["family_name"] != "唐門世家")
                return "這位"+RANK_D->query_respect(me)+"，你與本門素無來往，此話從何談起！\n";
        
        if ( myfam["family_name"]=="唐門世家")
        {      
                set_temp("yiwen", 1, me);
                switch( random(2) )
                {
                   case 0:
                        tell_object(me, HIG"原來是自己人啊，請上樓，唐老闆正好回來了！\n"NOR);
                        me->move("/d/tangmen/jiulou2");
                        set_temp("askxiao", 1, me);
                        break;
                   case 1:
                        tell_object(me, HIR"不巧啊，唐老闆正好出門了，你過一陣再來吧！\n"NOR);
                        break;
                 }            
                        
        }
          
        set_temp("yiwen", 1, me);
        return "不知這位"+RANK_D->query_respect(me)+"問我家老闆有什麼事! \n";
}

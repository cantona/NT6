//NPC /npc/shizhe.c

inherit NPC;
#include <ansi.h>
#include <command.h>

void greeting(object);
void init();
int ask_for_xkd();

void create()
{
        set_name("黃衣使者", ( { "shi zhe", "zhe" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "這是個身着黃衣的三十幾歲漢子，手持木漿，面無表情。\n");
        set("attitude", "friendly");
        set("no_get", 1);
        set("shen_type", 1);

        set("str", 30);
        set("int", 39);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 330);
        set("max_jing", 320);
        set("neili", 300);
        set("max_neili", 300);

        set("combat_exp", 16000);
        set("score", 10000);

        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 50);

        create_family("俠客島", 2, "弟子");

        set("inquiry", ([
                "俠客島" : (: ask_for_xkd :),
                "出海"   : "南邊還有幾艘船，你自己看看去吧！\n",
        ]));
        setup();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{

        if( !ob || environment(ob) != environment() ) return;
        say("黃衣使者説道：這位" + RANK_D->query_respect(ob) + "你把我叫過來，有什麼事嗎。\n");
        return;
}

/*int accept_object(object who, object ob)
{
        object ling1;
        object ling2;
        object room, myenv;
 
        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");

        if( query("id", ob) != "shanpai"
                 && query("id", ob) != "epai" )
        {
                return notify_fail("我不需要這件東西。\n");
        }
        
        if ( query_temp("times")==0 )
        {
                return notify_fail("我太累了，不想出海。\n");
        }

        if( !query("xkd/ling", who) )
        {
                tell_object( who, "黃衣使者説道：俠客島只邀請成名武術家上島，這位" + RANK_D->query_respect(who) + "還是請回吧。\n" );
                return 0;
        }
        
        if( query("id", ob) == "shanpai" )
        {
                if( query("own", ob) != query("id", who) )
                {
                        message_vision("這不是你的牌子。你這樣欺騙我，不是想害我家破人亡嗎？\n",who);
                        return 0;
                }
                if (query_temp("ling")==2)
                {
                        message_vision("使者一看是賞善銅牌，滿臉歉意地對$N説：上島的銅牌共兩塊，你還缺一塊罰惡銅牌。\n",who);
                        return 0;
                }
                addn_temp("ling",2);
                if(!( room = find_object("/d/xiakedao/duchuan")) )
                        room = load_object("/d/xiakedao/duchuan");
        
                room = find_object("/d/xiakedao/duchuan");
                addn_temp("pai", 2, room);
        
                if( query_temp("ling")==2 )
                { 
                        message_vision("使者一看是賞善銅牌，滿臉欣喜地對$N説：你還有一塊罰惡銅牌嗎？\n",who);
                        return 1;
                }
        }

        if( query("id", ob) == "epai" )
        {
                if( query("own", ob) != query("id", who) )
                {
                        message_vision("這不是你的牌子。你這樣欺騙我，不是想害我家破人亡嗎？\n",who);
                        return 0;
                }
                if(query_temp("ling")==1)
                {
                        message_vision("使者一看是罰惡銅牌，滿臉遺憾地對$N説：本島銅牌一共兩塊，你還缺賞善銅牌。\n",who);
                        return 0;
                }
                addn_temp("ling",1);
                if(!( room = find_object("/d/xiakedao/duchuan")) )
                        room = load_object("/d/xiakedao/duchuan");
                room = find_object("/d/xiakedao/duchuan");
                addn_temp("pai", 1, room);
        
                if( query_temp("ling")==1 )
                {
                        message_vision("使者一看是罰惡銅牌，滿臉欣喜地對$N説：你還有賞善銅牌嗎？\n",who);
                        destruct( ob );
                        return 1;
                }
        }

        command("smile"+query("id", who));
        tell_object( who, HIG"原來是俠客島的貴賓，這就隨我上島去吧。\n"NOR );
        ling1 = new("/d/xiakedao/obj/tongpai1");
        set_temp("own",query("id",  who), ling1);
        ling1->move(who);
        ling2 = new("/d/xiakedao/obj/tongpai2");
        set_temp("own",query("id",  who), ling2);
        ling2->move(who);
        set_temp("ling",0);
//        addn_temp("times",-1);
        myenv = environment (who) ;
        who->move("/d/xiakedao/duchuan");
        tell_room(myenv,"黃衣使者招了招手，一隻小舟靠岸，"+query("name", who)+"跨步上船。\n");
        call_out("goto_xiake",10,who) ;
        return 1;
}*/

int ask_for_xkd()
{
        object who = this_player();
        object ling1,ling2;
        object myenv;        
        object* inv;
        int i;
        
        if( !who || environment(who) != environment() ) return 0;
        
//        if ( !who->query("xkd/ling") || time() > who->query("xkd/time") )
        if( !query("xkd/ling", who) )
        {
                message_vision("黃衣使者説道：小人在這活了一輩子，還從沒聽説過。\n", who );
                return 1;
        }
                /*
        if ( !objectp( ling1 = present( "shan pai", who ) ) ||
                !objectp( ling2 = present( "e pai", who ) ) )
        {
                message_vision( "黃衣使者説道：上俠客島要有賞善罰惡令，這位" + RANK_D->query_respect(who) + "還是請回吧！\n", who );
                return 1;
        }
        
        if( query("own", ling1) != query("id", who) || 
                query("own", ling2) != query("id", who) )
        {
                message_vision( "黃衣使者説道：" + RANK_D->query_respect(who) + "拿的不是自己的牌子。這樣欺騙我，不是想害我家破人亡嗎？\n", who );
                return 1;
        }
*/        
        inv = all_inventory(who);
        for(i=0; i<sizeof(inv); i++)
                if ( userp(inv[i]) )
                {
                        message_vision( "黃衣使者説道：島主頒下嚴令，只能迎接" + RANK_D->query_respect(who)+ "一人前往。\n若是多載一人，小舟固須傾覆，小人也是首級不保。\n", who );
                        return 1;
                }
                
        command("smile"+query("id", who));
        tell_object( who, HIG"原來是俠客島的貴賓，這就隨我上島去吧。\n"NOR );
        myenv = environment (who) ;        
        who->move("/d/xiakedao/duchuan");
        tell_room(myenv,"黃衣使者招了招手，一隻小舟靠岸，"+query("name", who)+"跨步上船。\n");
        call_out("goto_xiake",10,who) ;        
        return 1;
}

void goto_xiake(object ob)
{
        tell_object(ob, HIB"你在海上航行了三天三夜，大船終於停在了一個小島邊。你走下船來。\n" ) ;
        ob->move ("/d/xiakedao/haitan") ;
}

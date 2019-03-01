inherit NPC;
#include <ansi.h>;

void create()
{       
        string *order = ({"張", "王", "李", "趙", "孫", "徐", "鄭", "周", "吳",
                "蔣", "沈", "楊", "苗", "尹", "金", "魏", "陶", "俞", "柳", "朱"});
        string *orderr = ({"包包", "寶寶", "乖乖", "小小", "磊磊",
                "雞雞", "鴉鴉", "狗狗", "貓貓","清清","明明","飛飛"});
        set_name(order[random(20)]+orderr[random(8)], ({ "boy","nanhai" }) );
        set("title", "無知男孩");
        set("gender", "男性" );
        set("age",5+random(3));
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("max_qi",100);
        set("max_jingli",100);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                // (: random_move :)
        }) );
        */
             

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_dating","xunwen");
}       

int do_dating(string arg)
{
        object me = this_player();
        object ob = this_object();
        string str=query("id", me);
       
        if (!arg || arg != "wenzi")
             return notify_fail("你想打聽什麼，你倒是說啊！\n");
        
        if( query("dname") != query("id", me) )
             return notify_fail("我不想說，你不要問，問了也白問！\n");     
         
        if( !(query_temp("started", me)) )
             return notify_fail("關于你的問題，我要考慮一下，你現在是不是覺得有點熱啊！\n");
        
        if( !(query_temp("asked", me)) )
           {
             command("ah");
             command("say 找我，你算找對了，不瞞你說吧！我剛被蚊子叮過，你說我會不會知道啊！\n");
             
             switch(random(2))
             {
                case 0 : command("joke");break;
                case 1 : set_temp("asked",1,me);tell_object(me,HIC"話音剛落，一個縱身沒有影了！\n"NOR); 
             destruct(ob);delete_temp("started", me);break;
                default: return 1;
             }
            return 1;                       
            }  
        tell_object(me,"話還沒說完，就聽見。。。。。。\n");       
        tell_object(me,HIG"一陣“嗡嗡”聲，一群蚊子從你身邊飛過！\n"NOR);
        tell_object(me,HIR"不要猶豫了，快去追啊！\n"NOR);
        return 1;
                
}

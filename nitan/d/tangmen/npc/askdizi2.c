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
        set("d2name","");
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
        string str,where;
        object me = this_player();
        object ob = this_object();
        
        if ( !arg || arg != "wenzi")
             return notify_fail("你想詢問什麼，你倒是説啊！\n");
        
        if( query("dname") != query("id", me) )
             return notify_fail("我不想説，你不要問，問了也白問！\n");
             
        if( (query_temp("askok", me)) )
             return notify_fail("關於你的問題，我要考慮一下，你現在是不是覺得有點熱啊！\n");
        
        if( !(query_temp("asked", me)) )
             return notify_fail("你這個真奇怪，有問路的，有問要錢的，有問吃的，沒聽有問蚊子的。\n");
        
        switch( random(6))
        {
            case 0 : str = "唐家鋪子";where = "/d/tangmen/tjpuzi";break;
            case 1 : str = "唐門酒樓";where = "/d/tangmen/jiulou";break;
            case 2 : str = "客店";where = "/d/tangmen/kedian";break;
            case 3 : str = "藥鋪";where = "/d/tangmen/hcfdian";break;
            case 4 : str = "兵器鋪";where = "/d/tangmen/tmbingqi";break;
            default : str = "唐氏錢莊";where = "/d/tangmen/tsqianz";break;
        }
        
        tell_object(me,HIC"你去"+str+"找找啊！\n"NOR);    
        
        set_temp("mingchen", str, me);
        set_temp("where", where, me);
            
        set_temp("askok", 1, me);
        delete_temp("asked", me);
                        
        tell_object(me,HIC"話音剛落，一個縱身沒有影了！\n"NOR);
        destruct(ob);
        return 1;   
        
}                  

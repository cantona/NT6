//room: dongkou.c

#include <ansi.h> 
inherit ROOM;

#define REBORND   "/adm/daemons/rebornd"

void create()
{
     set("short","絕壁");
     set("long",@LONG
山道到此突然消失，在你面前是一條絕壁，往下看去雲霧繚繞，你根
本無法看清谷底。絕壁邊有個山洞（hole)，旁邊有一塊石碑(bei)。
LONG
     );
     set("exits", ([ 
                    "up" : "/d/city3/road2", 
             ])); 
     set("outdoors", "chengdu");     
     set("item_desc",([
         "bei" : "『麒麟窟』內有怪獸，無事切勿入內！\n" ,
         "hole" : "這是麒麟窟，你不想活了的話可以進去。(enter dong)\n" ,
     ]));
     setup();
}

void init()
{
     string id;
     object ob;
     object me = this_player();

     add_action("do_enter", "enter");

     if ( me->is_character() && ! userp(me) )
     {
        me->move("/d/city3/road2");
        return;
     }
     if ( ! me->query("reborn_start"))
     {
        tell_object(me, 
           BLINK HIR"麒麟窟哪裡是隨便能進的，莫非你活得不耐煩了!\n\n"NOR);

        message_vision(HIY"一股巨大的力量將$N推出了麒麟洞口。\n\n"NOR, me);
        me->move("/d/city3/road2");
        return;
     }
  
     id = REBORND->query("qilindong");
     
     if ( stringp(id) && id != me->query("id") )
        ob = find_player(id);

     if (objectp(ob) && 
         base_name(environment(ob))[0..20] == "/d/zhuanshi/qilindong")
     {     
         tell_object(me, 
            HIY"現在有人正在洞裡，你遲點再來吧。\n\n"NOR);        
          message_vision(HIY"一股巨大的力量將$N推出了麒麟洞口。\n\n"NOR, me);
          me->move("/d/city3/shudao14");         
         return;
     }         
     REBORND->set("qilindong", me->query("id"));
     
}

int do_enter(string arg)
{
    object me, ob;    

    me = this_player();
 
    if( !arg || arg != "hole" )
       return notify_fail("你要進哪裡去?\n"); 

    foreach (ob in deep_inventory(me)) 
    if (ob->is_character()) 
        return notify_fail("進麒麟窟，生死由天，就不要帶其他人或動物進去了！\n"); 

    message_vision("$N一彎腰往洞裡走了進去。\n\n",me);
    
    me->move(__DIR__"dong1");

    message("vision", me->name() + "從洞裡走了進來。\n",
            environment(me), ({me}) );

    return 1;   
}   

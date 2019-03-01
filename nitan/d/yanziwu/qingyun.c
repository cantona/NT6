// Room: /d/yanziwu/qingyun.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青雲莊");
        set("long", @LONG
這裡是青雲莊。莊上是慕容世家練功之所。自慕容博創下“以彼之
道，還施彼身”的絕學，立下“南慕容、北喬峰”之名後。慕容世家隱
然是江南武林泰鬥了。
    莊外湖面正系著一尾小舟(zhou)。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "east"  : __DIR__"liangong",
        ]));
        set("item_desc", ([
                "zhou" : "這是青雲莊和外界聯系的小舟。舟上一個綠衫少女。島上的客人只要\n登舟(enter)就可以離開了。\n",
        ]));
        set("coor/x", 950);
        set("coor/y", -1500);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_enter", "enter");
}
int do_enter(string arg)
{
        object ob ;
        string dir;
        if( !arg || arg !="zhou" ) 
        {
                tell_object(this_player() , "你要投水？\n");
                 return 1 ;
        }
        ob = this_player();
message_vision("船上一個秀美溫柔的江南少女看到$N登舟，竹篙輕點，舟已
離岸，青雲莊漸漸在視野裡遠去。\n", ob);
        ob ->move(__DIR__"taihu") ;
        tell_object(ob, HIG "你在湖上飄流，四周看不盡的江南美景。\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "小舟終于戀戀不舍地靠岸了。你走下小舟來。少女揮手依依道別。\n" ) ;
        ob->move (__DIR__"muti") ;
}
// suti6.c
// Date: Nov.1997 by Venus
#include <room.h>;
#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", "蘇堤");
        set("long", @LONG
秋月之夜，月下觀湖，唯見滿湖銀波粼粼，陣陣微風，風中桂子飄
香，令人為之心醉。堤邊泊著小舟(zhou)是送遊客去三潭映月的。往西
邊是去花港，東面可見三潭映月遙立湖中，北邊是鎖瀾橋，南面映波橋。
LONG);
        set("exits", ([
            "north"     : __DIR__"suti5",
            "south"     : __DIR__"suti7",
            "west"      : __DIR__"huagang",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="zhou" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("梢公一見有人上船，輕搖木槳，小舟東行。\n", ob);
        ob ->move(__DIR__"xihu") ;
        tell_object(ob, HIG "你在湖面穿行，輕風徐來，滿面生暖。\n" NOR ) ;
        call_out("tostyy", 10 , ob );
        return 1 ;
}
void tostyy(object ob )
{
        tell_object(ob , "小舟輕輕靠上湖中小瀛洲。你走下船來。\n" ) ;
        ob->move (__DIR__"santan") ;
}
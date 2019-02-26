// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
#include <ansi.h>

void create()        
{
        set("short", "港口");
        set("long", @LONG
這裏是一個港口，這裏非常熱鬧，停泊着各種船隻，有貨船，商船
等等。很多旅客從這裏進出港口，有從中原來的，也有從其他地方來的。
許多小販在這裏叫賣。有舟船可以通往日本(chuan) 十分方便。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadi6",
//   "east":"/d/job/killhaidao/gangkou",
                //"south":__DIR__"gangkou",
        ]));
        set("item_desc", ([
                "chuan" : "一條大海船。出遠海沒這樣的船可不行。\n",
        ]));
          set("no_duhe",1);
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
    if( !arg || arg !="chuan" ) 
       {
         tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
         return 1 ;
       }
    ob = this_player () ;
    message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
    message_vision("船伕升起帆，船就向東南方航行。\n", ob);
    ob ->move("/d/quanzhou/dahai") ;
    tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
    call_out("tpenghu", 10 , ob );
    return 1 ;
}
void tpenghu(object ob )
{
    tell_object(ob , "大船終於抵達了倭島。你走下船來。\n" ) ;
    ob->move ("/d/japan/haigang") ;
}


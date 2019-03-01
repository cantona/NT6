#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short","海防碼頭");
  set ("long", @LONG
這裡是安南的碼頭。北方最大港口，第二大城，軍事要地。位于紅河
三角洲東北部，東臨北部灣。靠在岸邊的船密密麻麻，有魚家用的小魚船、
運貨用的商船、還有普通人用不起的官船，船上船下人們忙落異常。旁
邊好象有搭客的商船。有船(chuan) 可以去中國海南。
LONG);

  set("exits", ([ 
  "west":__DIR__"gj3",        
  "south":__DIR__"guandao4",
  "north":__DIR__"shulin3",        
       ]));
        set("item_desc", ([
                "chuan" : "一條大海船。出遠海沒這樣的船可不行。\n",
        ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
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
    message_vision("船夫一見有人上船，忙叫了一聲：開船嘍！\n", ob);
    message_vision("船夫升起帆，船就向東北方航行。\n", ob);
    ob ->move("/d/quanzhou/dahai") ;
    tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
    call_out("tpenghu", 10 , ob );
    return 1 ;
}
void tpenghu(object ob )
{
    tell_object(ob , "大船終于抵達了中國海南。你走下船來。\n" ) ;
    ob->move ("/d/hainan/haibian") ;
}

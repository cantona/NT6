// /d/shenlong/beach.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "海岸");
        set("long", @LONG
這是神龍島的出海口，浪花拍打着礁石，發出陣陣響聲，海面上一
羣羣海鷗『歐歐..』地叫着，不時有魚兒躍出海面，濺起層層的浪花。
邊上有艘大船(chuan)， 船上坐着幾個船伕打扮的人，乘船可渡過大海
到達海的另一端。東面是神龍島的海灘。
LONG
        );
        set("outdoors", "shenlong");

        set("exits", ([
                "east" : __DIR__"haitan",
        ]));
        set("item_desc", ([
                "chuan" : "這是神龍島對外聯繫的大船。島上的客人或弟子只要\n上船(enter)就可以回中原。\n",
        ]));
        set("exits",([
                "east" :__DIR__"haitan",
        ]));
        set("outdoors", "shenlong");
        set("coor/x", 4000);
        set("coor/y", 3000);
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
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("船伕升起帆，船就向西方航行。\n", ob);
        ob ->move(__DIR__"dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "大船終於抵達了中原的一個繁華城市。你走下船來。\n" ) ;
        ob->move ("/d/beijing/haigang") ;
}

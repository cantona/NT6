// haitan.c
#include <ansi.h>

inherit ROOM;

void home( object ob ) ;

void create()
{
    set("short", "海灘");
    set("long", @LONG
這裏就是俠客島了。北邊是一望無際的大海；往南則是一片樹
林。島上的空氣似乎非常新鮮，鹹濕的海風中帶着一股花香，這是
好大的一片沙灘，東首石崖下停着四十多艘大小的船隻(boat)。
LONG );

    set("item_desc", ([
        "boat" : "這是俠客島對外聯繫的大船。島上的客人或弟子只要\n"
                  "上船(enter)就可以回中原。\n",
    ]));
    set("exits",([
        "south" :__DIR__"lin1",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "xiakedao");
        set("coor/x", -3000);
        set("coor/y", -20000);
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
    if( !arg || arg !="boat" )
       {
         tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
         return 1 ;
       }
    ob = this_player () ;
    message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
    message_vision("船伕升起帆，船就向北方航行。\n", ob);
    ob ->move("/d/xiakedao/dahai") ;
    tell_object(ob, BLU "你在海上航行了三天三夜.......\n" NOR ) ;
    call_out("home", 10 , ob );
    return 1 ;
}
void home( object ob )
{
    tell_object(ob , "大船終於抵達了南海岸邊。你走下船來。\n" ) ;
    ob->move (__DIR__"haigang") ;
}
// Room: /d/taiwan/lugang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "鹿港");
        set("long", @LONG
鹿港地瀕海濱，風帆爭飛、萬商畢集，是海峽兩岸貿易的中部要港、
台灣中部的門户。俗諺雲：一府二鹿三笨港，乃指鹿港為全台僅次於台
灣府的第二大城。
    海港內有舟(zhou)船來往澎湖。
LONG );
        set("exits", ([
                "east"       : __DIR__"banxianshe",
        ]));
        set("objects", ([
                __DIR__"npc/shangren": 3,
        ]));
        set("item_desc", ([
                "zhou" : "一條兵舟，往返澎湖的交通兵船。\n",
        ]));

        set("outdoors", "taiwan");
        set("coor/x", 2500);
        set("coor/y", -7000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
        object ob = this_player () ;
        string dir;
        if( !arg || arg !="zhou" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        message_vision("水兵一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("水兵升起帆，船就向西方航行。\n", ob);
        ob ->move(__DIR__"dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("tpenghu", 10 , ob );
        return 1 ;
}
void tpenghu(object ob )
{
        tell_object(ob , "兵舟終於抵達了海峽中一個大島。你走下船來。\n" ) ;
        ob->move (__DIR__"penghu") ;
}
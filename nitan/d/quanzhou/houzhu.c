// Room: /d/quanzhou/houzhu.c
// Last Modified by winder on May. 29 2001
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "後渚港");
        set("long", @LONG
後渚港是泉州三大港口之首。這裏港闊水深，風平浪靜。極目遠眺，
海天一色，蔚藍無暇。岸邊停靠着密密麻麻的各種船隻。由於海外貿易
的廣泛發展，泉州因而成為「海上絲綢之路」的起點。在眾多的船隻中
間，還有一隻大戰船(chuan)。
LONG );
        set("outdoors", "quanzhou");
        set("item_desc", ([
                "chuan" : "一條大海船。出遠海沒這樣的船可不行。\n",
        ]));
        set("exits", ([
                "north"   : __DIR__"portroad2",
        ]));
        set("objects", ([
                __DIR__"npc/boy": 2,
                __DIR__"npc/girl": 1,
                __DIR__"npc/shuishi" : 1,
        ]));
	set("coor/x", -870);
	set("coor/y", -7750);
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
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        message_vision("船伕一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("船伕升起帆，船就向東方航行。\n", ob);
        ob ->move("/d/taiwan/dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("tpenghu", 10 , ob );
        return 1 ;
}
void tpenghu(object ob )
{
        tell_object(ob , "大船終於抵達了大海中一個大島嶼。你走下船來。\n" ) ;
        ob->move ("/d/taiwan/penghu") ;
}
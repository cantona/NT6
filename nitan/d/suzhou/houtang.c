#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後堂");
        set("long", @long
這裡是書場的後堂，裡面有一張桌子和一張矮床，牆上的窗戶半掩
著，牆上掛著一副年畫(picture)。
long);
        set("item_desc", ([
                "picture" : "這一張尋常農家過年時貼的年畫。\n",
        ]));
        set("exits", ([
                "out" : __DIR__"shuchang",
        ]));
        create_door("out", "小門", "enter", DOOR_CLOSED);
	set("coor/x", 1089);
	set("coor/y", -1051);
	set("coor/z", -1);
	setup();
}
void init()
{
        add_action("do_jie","jie");
        add_action("do_jump","jump");
}
        
int do_jie(string arg)
{
        object me=this_player();
        
        if (!arg) return 0;
        if (arg !="picture") return 0;
        if (arg=="picture")
        {
                write("你揭開年畫，發現牆上有個洞，恰好能容納一個人，你忍不住想跳(jump)下去。\n");
                set_temp("marks/揭1", 1, me);
                return 1;
        }
}
int do_jump(string arg)
{
        object me;
        me=this_player();
        if( query_temp("marks/揭1", me) )
        {
                message("vision", me->name() + "鑽進了牆上的洞，跳了下去，只聽的“乒”的一聲響。\n", environment(me), ({me}) );
                me->move(__DIR__"szyunhe");
                message("vision", me->name() + "突然間從上面摔了下來。\n", environment(me), ({me}) );
                delete_temp("marks/揭1", me);
                return 1;
        }
}
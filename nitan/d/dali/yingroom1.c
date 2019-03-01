// Code of ShenZhou
inherit ROOM;

void create()
{
        set("short", "泥潭");
        set("long", @LONG
這裡是一個片大泥潭，向前望去，眼前一團茫茫白霧裹著一方一
圓兩間茅屋，隱隱約約有燈光從方屋中射出。此茅屋無門無戶，連窗
戶都沒有一個，不知道土牆(wall)那邊有些什麼。
LONG );
        set("item_desc",([
                "wall" : "一堵看起來不是很高的土牆。\n",
                ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        set("outdoors", "dalic" );
        set("exits", ([
                "north" : "/d/dali/maze1",
                ]));
        set("cost", 4);
        set("coor/x", -38000);
        set("coor/y", -72000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if ( !arg || arg != "wall")
                return notify_fail( "什麼？\n");

        message_vision("$N縱身往土牆上跳去。\n", me);
        if ( me->query_skill("dodge",1) <= 50) {
                message_vision("$N通的一聲摔進了泥潭，滿身臭氣。\n", me);
                me->receive_wound("qi", 100);
        }
        if ( me->query_skill("dodge",1) > 50 ) {
                me->move("/d/dali/yingroom2");
                message("vision", me->name() + "縱身由牆上跳了過來。\n",environment(me), 
                        ({me}) );
        }
        return 1;
} 
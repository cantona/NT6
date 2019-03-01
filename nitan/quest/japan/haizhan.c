// /job/japan/haizhan.c
// by akuma 10:52 AM 11/30/2003
// source from hanghai_room.c

#include <ansi.h>
inherit ROOM;
#define MST        __DIR__"haizhan_master"                // 經緯儀，遊戲指令主支持

void create()
{
        set("short", "大海中");
        set("long", @LONG
茫茫大海之中，左右艦隊跟隨浩浩盪盪沖向日本艦隊。
LONG);
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("cost", 0);
        setup();
}

void init()
{
        add_action("do_game", "haizhan");
        add_action("do_quit", "quit");
}

int do_game(string arg)
{
        object me = this_player(), mst_obj;

        if ( !arg || arg != "開始" ) return 0;        // "game over" 等操作，由 MST 物件進行。

        if( !query_temp("job/fleet", me))return notify_fail("你正在使入黃海海戰區。\n");

        if ( file_size( MST + ".c" ) < 1 ) return notify_fail("海戰暫停，老佛爺叫歇了。\n");

        write("\n你帶這艦隊慢慢地駛入黃海戰區……\n\n");
        mst_obj = new( MST );
        mst_obj->new_game(me);
        mst_obj->move(me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("job/haizhan", me))return notify_fail("戰事已經開始，不能臨陣脫逃。\n");

        return ::valid_leave(me, dir);
}

int do_quit()
{
        write("這裡不能退出遊戲。\n");
        return 1;
}
// Room: /d/kunlun/jiuqulang8.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "九曲廊");
        set("long",@long
九曲廊前後共有九進，曲曲折折地盤旋在水面。一路穿花度柳，撫
石依泉，落花浮盪，水色溶溶。兩邊垂柳雜著桃杏，籐蔓繞柱。白石為
欄，飛樓插空，轉折處皆由小亭相接。
long);
        set("exits",([
                "north" : __DIR__"jiuqulang7",
                "east" : __DIR__"jiuqulang1",
                "southwest" : __DIR__"nanwoshi",
        ]));
        set("outdoors", "kunlun");
        set("no_clean_up", 0);
        set("coor/x", -120000);
        set("coor/y", 40090);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "southwest" && query("gender", me) != "男性" )
                return notify_fail("你低著頭走了進去。卻發現裡面是男臥室，不由得臉上發燒，一扭頭跑了出來。\n");
        return ::valid_leave(me, dir);
}
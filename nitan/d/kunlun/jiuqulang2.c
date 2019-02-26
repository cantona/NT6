// Room: /d/kunlun/jiuqulang2.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "九曲廊");
        set("long",@long
九曲廊前後共有九進，曲曲折折地盤旋在水面。一路穿花度柳，撫
石依泉，落花浮蕩，水色溶溶。兩邊垂柳雜着桃杏，藤蔓繞柱。白石為
欄，飛樓插空，轉折處皆由小亭相接。
long);
        set("exits",([
                "north"     : __DIR__"jiuqulang3",
                "west"      : __DIR__"jiuqulang1",
                "southeast" : __DIR__"nvwoshi",
        ]));
        set("outdoors", "kunlun");
        set("no_clean_up", 0);
        set("coor/x", -119980);
        set("coor/y", 40090);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "southeast" && query("gender", me) != "女性" )
                return notify_fail("你正要往裏闖，卻發現兩把利劍已經架在你的頸項，你只好悻悻的退了出來。\n");
        return ::valid_leave(me, dir);
}
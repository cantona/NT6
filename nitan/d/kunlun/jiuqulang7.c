// Room: /d/kunlun/jiuqulang7.c
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
                "west"   : __DIR__"chufang",
                "east"   : __DIR__"sanshengtang",
                "north"  : __DIR__"jiuqulang6",
                "south"  : __DIR__"jiuqulang8",
        ]));
        set("outdoors", "kunlun");
        set("no_clean_up", 0);
        set("coor/x", -120000);
        set("coor/y", 40100);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
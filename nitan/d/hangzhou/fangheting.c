// fangheting.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "放鶴亭");
        set("long", @LONG
亭四周種滿了梅花。一到冬末春初，梅花盛放，蔚然可觀。此亭
是為了紀念北宋隱逸詩人林和靖而建。他酷愛梅花。“疏影橫斜水清
淺，暗香浮動月黃昏”就是他的詠梅名句。據傳説，詩人還養鶴一隻，
取名：“鳴苯”每逢自己外出散步而恰有客人來訪時，童子就開籠放
鶴，詩人見鶴，便回家接客，故流傳有“梅妻鶴子”的故事。朝東南
走便是平湖秋月。西南邊則是孤山。
LONG);
        set("exits", ([
            "southwest" : __DIR__"gushan",
            "southeast" : __DIR__"pinghuqiuyue",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xihu");
	set("coor/x", 820);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
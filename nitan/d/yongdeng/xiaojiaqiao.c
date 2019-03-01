// Room: /huanghe/xiaojiaqiao.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "蕭家橋");
        set("long", @LONG
在蘭州和古浪中間，紀永河水咆哮而過，河水湍激，河床最寬處九
丈四尺，窄處七丈余，度船難過。相傳漢年間，本地一位蕭姓大財主，
窮六年之功，遍集巧匠，費盡家私，方建成橋，欲到蘭州，必先度本橋。
LONG );
        set("exits", ([
                "east"    : __DIR__"gulang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yongdeng");
        set("coor/x", -16120);
	set("coor/y", 4210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
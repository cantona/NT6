// shishi4.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "地下石室");
        set("long", @LONG
這是一個地下的祕密石室，四面可以感覺得到的只有強烈的殺氣，
以及處身地底的一些難聞的氣味。在微弱的燈光下，你竟然看到有個人
站着那裏。繼續往下好像還有路。
LONG );
        set("exits", ([
                "up" : __DIR__"fangjian2",
                "down" : __DIR__"shishi5",
        ]));
        set("objects",([
//                __DIR__"npc/qingyun" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21030);
        set("coor/z", -50);
        setup();
}

/*int valid_leave(object me,string dir)
{
        if( dir == "down" && (!query("family", me) || (query("family/master_id", me) != "xiaoyaozi")) && present("qingyun",environment(me)) )
             return notify_fail("青雲一個閃身，擋住了你的去路！\n");
        return ::valid_leave(me,dir);
}*/
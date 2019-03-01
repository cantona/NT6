// Room: /d/nanyang/ruzhou.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "汝州城");
        set("long", @LONG
汝州城是本府的大城，歷來是兵家必爭之地。故州治在此駐
紮重兵，盤查南來北往的行人，並負責翦滅附近山上的草寇。城
內一隊隊官兵來來去去，一派森嚴氣象。再折向西，就是五岳之
一的嵩山。
LONG );
        set("exits", ([
                "southwest" : __DIR__"yidao3",
                "west"  : "/d/songshan/taishique",
                //"north" : "/d/beijing/road10",
                "north" : "/d/huanghe/huanghe3",
                "northwest" : "/d/kaifeng/tonanyang",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));
        set("outdoors", "nanyang");
        set("coor/x", 10);
        set("coor/y", 700);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
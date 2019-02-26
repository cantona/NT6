// Room: /d/huangshan/qingluan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "青鸞橋");
        set("long", @LONG
説是青鸞橋，確切的應該是倚山勢看上去是橋，實際上卻是一座石
樑，遠望去好似青鸞騰空，背上可以行人，石樑左側刻有“青鸞”二字，
北去便是黃山三名瀑之“百丈泉”，西行便是半山寺了。
LONG
        );
        set("exits", ([ 
                "east"      : __DIR__"baizhang",
                "west"      : __DIR__"renzi",
                "southup"   : __DIR__"ciguang",
                "northup"   : __DIR__"banshan",
                "northwest" : __DIR__"zuishi",
        ]));
        set("objects", ([
                __DIR__"obj/stone" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1080);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}
// Room: /d/qilian/tanglangling.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "螳螂嶺");
        set("long", @LONG
這裡是祈連山區邊緣。出了螳螂嶺往西就是西北平原，北望玉門，
西北到嘉峪關。螳螂嶺山形漫長，山勢低矮，再加上通山翠綠，四季不
變，故而得名。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "eastup"    : __DIR__"qitianfeng",
                "northdown" : "/d/xingxiu/jiayuguan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -18000);
        set("coor/y", 3000);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
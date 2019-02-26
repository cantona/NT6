// Room: /d/kunlun/xianjing.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "崑崙仙境");
        set("long", @LONG
放開腳步向前急奔，直奔了兩裏有餘，才遇一座高峯阻路。放眼四
望，旦見翠谷四周高山環繞，似乎亙古以來從未有人跡到過。四面雪峯
插雲，險峻陡絕計無法攀援而入。
LONG );
        set("outdoors", "hongmei");
        set("exits", ([
                "north" : __DIR__"cuigu",
        ]));
        set("objects", ([
                __DIR__"npc/monkey" : 2,
                __DIR__"npc/bigmonkey" : random(2),
        ]));
        setup();
        set("coor/x", -100000);
        set("coor/y", 20030);
        set("coor/z", 40);
        replace_program(ROOM);
}
// Room: /d/mingjiao/gudi4.c

inherit ROOM;

void create()
{
        set("short", "昆侖仙境");
        set("long", @LONG
放開腳步向前急奔，直奔了兩裡有餘，才遇一座高峰阻路。放眼
四望，旦見翠谷四周高山環繞，似乎亙古以來從未有人跡到過。四面
雪峰插雲，險峻陡絕計無法攀援而入。
LONG );
        set("outdoors", "mingjiao");
        set("exits", ([
                "north" : __DIR__"gudi3",
        ]));
        set("objects", ([
                __DIR__"npc/monkey" : 2,
                __DIR__"npc/bigmonkey" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
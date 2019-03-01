//zhandao2.c
inherit ROOM;

void create()
{
        set("short", "棧道");
        set("long", @LONG
這裡是通往明教的棧道，腳下茂林生雲，極其艱險。遠遠看到上
頭就是明教內三堂美侖美奐的飛檐畫棟了。
LONG );
        set("exits", ([
                "northup"   : __DIR__"tianweitang",
                "southdown" : __DIR__"zhandao1",
        ]));
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
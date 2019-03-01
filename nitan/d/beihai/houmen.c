// /d/beihai/houmen.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "後門");
        set("long", @LONG
這裡是北海花園的後門，門是虛掩著的。門前面站著兩個衛士。門
兩邊長著茂盛的植物。一些苦力背著東西進進出出，甚是忙碌。由門向
北是一條官道。
LONG
        );
        set("exits", ([
                "west"  : __DIR__"jingqing",
                "south" : __DIR__"huafang",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -160);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
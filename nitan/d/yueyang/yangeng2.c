// Room: /d/yueyang/yangeng2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "巖梗");
        set("long", @LONG
這是香爐山通往酒香山上酒香亭的巖梗小道。香爐山與君山本是一
脈相通，不可分割，冬春水枯季節，一條數十丈的巖埂由君山直通香爐
山。這條巖埂原是一條小山脊，橫跨於兩山之間，後經千百年湖水沖洗
盪滌，山脊泥土逐漸被浪濤洗盡，以至巖埂裸露，非水枯不可往來。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "north"   : __DIR__"yangeng1",
                "southup" : __DIR__"xianglushan",
        ]));
        set("coor/x", -1800);
        set("coor/y", 2270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
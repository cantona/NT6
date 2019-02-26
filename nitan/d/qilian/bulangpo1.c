// Room: /d/qilian/bulangpo1.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "不狼坡");
        set("long", @LONG
這裏是祁連山脈的開始，地勢複雜。山中多為人跡罕至之處，礦藏
頗豐，且山中有眾多野生動物，是巡獵、訪寶的好去處。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "northup" : __DIR__"bulangpo2",
                "south"   : __DIR__"bonanshan",
        ]));
        set("objects", ([
                __DIR__"npc/mulang": 1,
        ]));
        set("coor/x", -9900);
        set("coor/y", 2800);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}
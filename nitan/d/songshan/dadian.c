// Room: /d/songshan/dadian.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "中嶽大殿");
        set("long", @LONG
大殿面闊九間，進深五間，重檐廡殿式屋頂，座落在七尺高的台基
上，氣勢雄偉。大殿中供奉嶽神天中王。
LONG );
        set("exits", ([
                "northup" : __DIR__"shandao1",
                "south"   : __DIR__"chongsheng",
        ]));
        set("objects", ([
                __DIR__"npc/lu": 1,
        ]));
        set("coor/x", 0);
        set("coor/y", 730);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
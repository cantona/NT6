// shenheyuan.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "神禾原");
        set("long", @LONG
此處位於終南山中部的翠華山附近。放眼望去，只見一片坦蕩無
垠的大平原，夾在羣山之間。傳説商朝末年，姜子牙率兵伐紂攻打長
安時，糧草短缺，在此獲神禾老漢之助，得米萬斛，因此命名為神禾
原。往東南和北上各是一片樹林。往南是一處遺蹟。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "west"      : __DIR__"foyezhang",
                "north"     : __DIR__"shulin3",
                "southeast" : __DIR__"shulin2",
        ]));
        set("objects", ([
                "/d/hanzhong/npc/seller": 1,
        ]));

        set("coor/x", -3170);
        set("coor/y", 70);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
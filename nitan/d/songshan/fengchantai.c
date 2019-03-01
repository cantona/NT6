// Room: /d/songshan/fengchangtai.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "封禪台");
        set("long", @LONG
峻極封禪台由大麻石所建，每塊大石都鑿得極是平整。地勢甚為寬
闊。這裡獨立天心，萬峰在下，雲開日朗，纖翳不生。極目北望，可遙
見成皋玉門，黃河有如一線，西向隱隱見到洛陽伊闕，東南都是疊疊重
山。
LONG );
        set("exits", ([
                "eastdown" : __DIR__"shandao8",
                "up" : "/d/reborn/jitan5",
        ]));
        set("objects", ([
                __DIR__"npc/bo": 1,
                __DIR__"npc/sha": 1,
        ]));
        set("outdoors", "songshan");
        set("coor/x", -30);
        set("coor/y", 850);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}

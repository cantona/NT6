// Room: /d/yanping/road2.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "卵石道");
        set("long", @LONG
一條鵝卵石道延伸東西，馬車在道上踢蹋穿行。北邊便是延平府衙
了，東邊通往延福門。延平府依山而建，城中街道只比城牆稍矮，而城
牆外臨江一側，城牆高厚，真算是金城湯池了。
LONG );
        set("exits", ([
                "west"      : __DIR__"road3",
                "east"      : __DIR__"yanfumen",
                "south"     : __DIR__"yanshoumen",
                "north"     : __DIR__"yamen",
                "northeast" : __DIR__"road1",
        ]));
        set("objects", ([
                "/d/village/npc/girl" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1480);
        set("coor/y", -6190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
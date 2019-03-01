// Room: /d/yanping/road1.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "青石道");
        set("long", @LONG
一條青石道延伸南北，西邊便是府衙的圍牆，東邊是青磚砌就的城
牆。延平府依山而建，城中街道只比城牆稍矮，而城牆外臨江一側，城
牆高厚，真算是金城湯池了。
LONG );
        set("exits", ([
                "north"     : __DIR__"dongmen",
                "south"     : __DIR__"yanfumen",
                "southwest" : __DIR__"road2",
        ]));
        set("objects", ([
                "/d/village/npc/boy" : 1,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1520);
        set("coor/y", -6180);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
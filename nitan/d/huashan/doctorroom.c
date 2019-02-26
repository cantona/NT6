// Room: /d/huashan/doctorroom.c

inherit ROOM;

void create()
{
        set("short", "郎中家");
        set("long", @LONG
這間屋子裏住着一位郎中，號稱仙醫，據説無論遇到什麼疑難雜
症，只要到了他手裏，都能手到病除。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "east" : __DIR__"road1",
        ]));
        set("objects", ([
            __DIR__"npc/doctor" : 1,
        ]) );
        set("no_clean_up", 0);
        set("no_fight",1);
        set("no_magic",1);
        set("outdoors", "huashan");

        setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
這是一條青石大道。東面隱約可以看到襄陽城的城牆。向西看去，
只見群山起伏，青翠碧綠，不知通向哪裡。
LONG );
        set("exits", ([
                "northeast" : __DIR__"road1",
                "southwest" : __DIR__"road3",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "city");

        set("coor/x", -310);
        set("coor/y", -170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

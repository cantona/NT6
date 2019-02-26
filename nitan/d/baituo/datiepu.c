inherit ROOM;

void create()
{
        set("short", "鐵鋪");
        set("long", @LONG
這裏是白駝山莊下面的一家打鐵鋪，不時從裏面傳來叮叮咚咚的
響聲。鐵匠忙着打製鐵製兵器，賣給江湖俠客。
LONG );
        set("exits", ([
                "north" : __DIR__"dongjie",
        ]));
        set("objects", ([
                __DIR__"npc/smith" : 1,
        ]));
        set("coor/x", -49980);
        set("coor/y", 19970);
        set("coor/z", 0);
        set("coor/x", -49980);
        set("coor/y", 19970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
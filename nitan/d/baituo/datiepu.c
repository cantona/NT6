inherit ROOM;

void create()
{
        set("short", "鐵舖");
        set("long", @LONG
這裡是白駝山莊下面的一家打鐵舖，不時從裡面傳來叮叮咚咚的
響聲。鐵匠忙著打制鐵制兵器，賣給江湖俠客。
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
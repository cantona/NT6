inherit ROOM;

void create()
{
        set("short", "村間小路");
        set("long", @LONG
這是一條向東的青石大道，兩邊是一排排的鄉間小屋。
LONG);

        set("exits", ([
                "west" : __DIR__"road1",
                "east" : __DIR__"shijiezhishu",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        setup();

        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long", @LONG
這是一條向東的青石大道，兩邊是一排排的鄉間小屋。
LONG);

        set("exits", ([
                "east" : __DIR__"lianwuchang",
                "west" : __DIR__"shijiezhishu",
                "north": __DIR__"cunzhangjia",
                "south": __DIR__"zahuopu",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        setup();

        replace_program(ROOM);
}
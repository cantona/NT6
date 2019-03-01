inherit ROOM;

void create()
{
        set("short", "文定南街");
        set("long", @LONG
這是中州城文定南街，寬敞的街道讓人不竟心情一暢。就
快到中州的南城門了。路邊有一家驛站。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "south" : __DIR__"nanmeng",
                "west" : __DIR__ "shuyuan",
                "north" : __DIR__"wendingnan3",
                "east" : __DIR__"yizhan",
        ]));

        set("coor/x", -9040);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
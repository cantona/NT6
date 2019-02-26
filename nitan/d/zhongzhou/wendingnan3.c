inherit ROOM;

void create()
{
        set("short", "文定南街");
        set("long", @LONG
這是中州城文定南街，寬敞的街道讓人不竟心情一暢。西
面有一家不小的房子，兩個女子綻放出迷人的微笑，肯定是個
放鬆的好地方。東北角有條黑胡胡的小衚衕。
LONG);
        set("outdoors", "zhongzhou");
        set("objects", ([
                  __DIR__"npc/man" : 2,
        ]));

        set("exits", ([
                  "south" : __DIR__"wendingnan4",
                  "northeast" : __DIR__"hutong",
                  "north" : __DIR__"wendingnan2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -9040);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
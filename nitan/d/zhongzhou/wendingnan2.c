inherit ROOM;

void create()
{
        set("short", "文定南街");
        set("long", @LONG
這是中州文定南街，寬敞的街道看的人不竟心情一暢。街
對面好象有一家茶樓。可進出的人你看著總覺得有點不對勁。
LONG);
        set("no_clean_up", 0);
        set("objects", ([
                  __DIR__"npc/qiying" : 1,
        ]));
        set("exits", ([
                  "east" : __DIR__"maodun",
                  "north" : __DIR__"wendingnan1",
                  "west" : __DIR__"chalou",
                  "south" : __DIR__"wendingnan3",
        ]));

        set("outdoors", "zhongzhou");

        set("coor/x", -9040);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
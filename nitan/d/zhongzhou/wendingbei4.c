inherit ROOM;

void create()
{
        set("short", "文定北街");
        set("long", @LONG
這是中州城文定北街，這裡離中州北城門已不遠。街上冷
冷清清沒幾個人影。街道的東面有一座深宅大院。門口掛著的
匾上赫然刻著苗家莊三個大字。西面是一長條的平房。
LONG);
        set("exits", ([
                  "south" : __DIR__"wendingbei3",
                  "east"  : __DIR__"miaojia_men",
                  "west"  : __DIR__"congwu",
                  "north" : __DIR__"beimen",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "zhongzhou");
        set("objects", ([
                  __DIR__"npc/tangzi" : 1,
        ]));

        set("coor/x", -9040);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
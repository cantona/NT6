inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這是條連接開封府與中州府的官道，由於這條路治安較好
行人也不少。東面通向開封，西面是中州府。
LONG);
        set("exits", ([
                "west" : __DIR__"dongmeng",
                "east" : __DIR__"eroad2",
        ]));
        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -8990);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
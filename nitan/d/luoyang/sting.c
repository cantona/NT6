inherit ROOM;

void create()
{
        set("short", "南廳");
        set("long", @LONG
這裏是衙門東廳，是知府招待客人的所在。廳中擺着一張杉木圓桌和
幾張椅子，桌上是一套精緻的宜興瓷器。牆上掛着一幅中堂，畫的是猛虎
下山，乃是知府的手筆。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"yamen",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
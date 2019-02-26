inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
你走在一條狹窄的山谷之中，兩旁山峯壁立，直插雲霄。鳥鳴猿啼之聲
迴盪在寂靜的空谷之中。
LONG    );
        set("exits", ([
                "northeast" : __DIR__"juebi-1",
                "southwest" : __DIR__"shangu-1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}
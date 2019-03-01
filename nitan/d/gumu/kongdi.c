// kongdi.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "空地");
        set("long", @LONG
這是終南山山腰處的一塊空地，地勢平坦。北面一條小路直攀山璧
而上，通往是終南山主峰。南邊和西邊一大片密林，只聞陣陣琴聲自林
中傳出。往北是一條山路。往南和西各有一條小徑。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "west"    : __DIR__"shulin5",
                "south"   : __DIR__"shulin4",
                "northup" : __DIR__"shanlu1",
        ]));
        set("coor/x", -3200);
        set("coor/y", 90);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
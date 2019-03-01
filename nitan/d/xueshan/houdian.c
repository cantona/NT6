inherit ROOM;

void create()
{
        set("short", "後殿");
        set("long", @LONG
 這裡是雪山寺的後殿，也是雪山弟子閉門練功的地方。殿內是一
些練功的蒲團和木人，還有一些吊掛著的沙袋和直豎的木樁。
LONG );

        set("exits", ([
                "north" : __DIR__"chanshi",
                "south" : __DIR__"neidian",
                "east" : __DIR__"tower",
        ]));

        setup();
        replace_program(ROOM);
}
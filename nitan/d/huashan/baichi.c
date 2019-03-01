// baichi.c

inherit ROOM;

void create()
{
        set("short", "百尺峽");
        set("long", @LONG
走過千尺幢，前面又見另一要命的百尺峽，百尺峽不似千尺幢般
險峻，但亦十分陡峭，巖壁兩側設有鐵索以作扶攔。百尺峽又稱百丈
崖，是一座壁立千仞的懸崖。崖底到上面的最低的埡口處約百尺，故
有是名。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "northdown" : __DIR__"qianchi",
            "eastup"    : __DIR__"pingxinshi",
        ]));

        set("outdoors", "huashan" );
        set("objects", ([ 
            "/clone/npc/walker" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
 
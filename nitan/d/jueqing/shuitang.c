inherit ROOM;

void create()
{
        set("short", "水塘");
        set("long", @LONG
行至此處，突然一陣清香湧至，眼前無邊無際的全是水仙
花。原來地下是淺淺的一片水塘，深不逾尺，種滿了水仙。由
于這絕情谷下生有溫泉，以致地氣奇暖這花雖是南方之物，也
會在這裡的出現。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "east"   : __DIR__"shanlu1",
               "southdown" : __DIR__"shulin1",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
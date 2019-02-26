inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裏是禪室下面的一條狹窄的暗道。陰森可怕，到處積滿了灰塵，
結滿了蛛網，也不知道通往何處。
LONG );
        set("exits", ([
                "north" : __DIR__"mishi",
                "up"    : __DIR__"chanshi",
        ]));
        setup();
        replace_program(ROOM);
}
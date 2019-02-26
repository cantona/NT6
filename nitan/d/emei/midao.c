inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裏是峨嵋華藏庵下面的一條狹窄的暗道。陰森可怕，到處積滿
了灰塵，結滿了蛛網，也不知道通往何處。
LONG );
        set("exits", ([
                "up"    : __DIR__"hcadadian",
                "north" : __DIR__"midao2",
        ]));
        setup();
        replace_program(ROOM);
}
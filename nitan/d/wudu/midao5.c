inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裡是五毒教花園下面的一條狹窄的暗道。陰森可怕，到
處積滿了灰塵，結滿了蛛網，也不知道通往何處。
LONG);
        set("exits", ([
                "south" : __DIR__"midao4",
                "up"    : "/d/city/ma_chufang",
        ]));
        setup();
        replace_program(ROOM);
}

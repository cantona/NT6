inherit ROOM;

void create()
{
        set("short", "純陽殿");
        set("long", @LONG
純陽殿海拔一千余米，四面古木蒼翠，幽靜宜人。殿前有一石，
叫普賢石，據說普賢菩薩登山時曾坐在這裡休息過。在此可縱觀峨嵋
諸峰，仰望金頂，懸崖峭壁，離天咫尺。這裡西上至神水庵，東下是
歸雲閣。
LONG );
        set("exits", ([
                "eastdown" : __DIR__"guiyunge",
                "westup"   : __DIR__"shenshuian",
        ]));
        set("outdoors", "emei");
        set("no_clean_up", 0);
        set("coor/x", -430);
        set("coor/y", -230);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}
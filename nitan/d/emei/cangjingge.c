inherit ROOM;

void create()
{
        set("short", "藏經閣");
        set("long", @LONG
小閣樓上便是峨嵋派的藏經閣了。這裏都是密密麻麻，高及頂棚
的書架。窗口下有張大桌子，桌上放了幾本佛經。有個小師太正在向
靜道師太借書。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/dao" : 1,
                __DIR__"obj/fojing1" + random(2) : 1,
                __DIR__"obj/fojing2" + random(2) : 1,
        ]));

        set("exits", ([
                "down"  : __DIR__"chuwujian", 
        ]));
        setup();
        replace_program(ROOM);
}
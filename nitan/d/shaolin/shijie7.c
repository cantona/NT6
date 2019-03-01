// Room: /d/shaolin/shijie7.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
石級繼續向上延伸，瀑布在腳下越來越小，水聲也漸行遠去幾位
身著灰黃色僧衣的僧人擦肩而過，看他們下山的時後腳步沉穩，好象
是個會家子。往上遠眺，似乎可以看到石檐一角。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie6",
                "east" : __DIR__"shanmen",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}

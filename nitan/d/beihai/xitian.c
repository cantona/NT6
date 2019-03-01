// /d/beihai/xitian.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "西天梵境");
        set("long", @LONG
清朝時建的宗教建築，主要是喇嘛教廟的樣式。附近還有小西天、
闡福寺、大西天、極樂世界等。由這裡向南就是去瓊華島的渡口。
LONG
        );
        set("exits", ([
                "west"      : __DIR__"jiulongbi",
                "southwest" : __DIR__"dukou1",
                "northeast" : __DIR__"jingqing",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4090);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
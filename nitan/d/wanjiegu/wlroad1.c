// Room: /d/wanjiegu/wlroad1.c

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這裏長滿了雜草，到處都是灌木。樹木遮天蔽日，偶然有一些小
動物突然串出，有飛快的跑開。地處偏僻，十分幽靜。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
                "west"      : __DIR__"wlroad2",
                "southeast" : __DIR__"wlshan",
        ]));

        setup();
        replace_program(ROOM);
}
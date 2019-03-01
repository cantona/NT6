//ROOM: /d/yanziwu/zhulin1.c

inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
鳳尾森森，龍吟細細，竿竿青竹縱橫交錯，遮蔽天日。這裏人跡
罕至，微風拂過竹林，發出沙沙之聲，你心中不免惴惴不安起來。林
中一道道石子鋪成的羊腸小道向前延伸。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "west" : __DIR__"cuixia",
            "east" : __DIR__"zhulin2",
            "north": __DIR__"zhulin4",
            "south": __DIR__"zhulin4",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
        set("short", "白河");
        set("long", @LONG
這裏是長白山下的一個小村，只有四，五間粗陋的小木屋。這裏並沒有
固定的居民，木屋都是進山採參的參客所蓋，為的是在進山前能在這裏好好
的休息一下。東面就是巍峨聳立的長白大山。
LONG );
        set("exits", ([
                "west"  : __DIR__"caoguduo",
                "east"  : __DIR__"milin1",
                "north" : __DIR__"xiaoyuan",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}
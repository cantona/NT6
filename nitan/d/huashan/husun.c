inherit ROOM;

void create()
{
        set("short", "猢猻愁");
        set("long", @LONG
前面又是一處十分陡峭的山嶺，上面有四隻鐵猿，盤踞台畔，據
説以前從華山水簾洞出來的猿猴，每到這裏就要返回去，連它們也感
到難於超越，此嶺因而得名。
LONG );
        set("exits", ([
                "northdown" : __DIR__"laojun",
                "southup"   : __DIR__"shangtianti",
        ]));
        set("objects", ([
                "/clone/quarry/hou" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan" );

        setup();
        replace_program(ROOM);
}
 
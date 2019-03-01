inherit ROOM;

void create()
{
        set("short", "茅屋");
        set("long", @LONG
這是一件不大的茅屋，殘破不全。向上望去可以看到點點陽光洒
降下來，難以想象這裡下雨的日子會是怎樣一番情景。
LONG );

        set("exits", ([
                "west" : "/d/kaifeng/shanlu2",
        ]));

        setup();
        replace_program(ROOM);
}
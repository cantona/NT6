inherit __DIR__"zhuang";

void create()
{
        set("short", "梅花樁一");
        set("long", @LONG
一人多高的梅花樁，向下望去真讓人心驚膽顫。
LONG
        );

        set("exits", ([
        "down" : __DIR__"lianwu",
        "east" : __DIR__"zhuang2",
        "southwest" : __DIR__"zhuang4",
]));
        setup();
}

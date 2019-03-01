// /guanwai/caoguduo.c

inherit ROOM;

void create()
{
        set("short", "穀草垛");
        set("long", @LONG
經過一番艱苦的跋涉，你的眼前出現了一片低矮的丘陵。遠遠看去象秋
收後堆成的穀草垛，密密麻麻，數不清有多少個。翻過這片丘陵再向東行，
就可進入長白大山了。東面的天邊有一縷炊煙，看來似乎有人。
LONG );
        set("exits", ([
                "northwest" : __DIR__"mantianxing",
                "east"      : __DIR__"baihe",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}
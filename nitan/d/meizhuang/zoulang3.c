inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條長長的走廊，走廊兩邊是四位莊主中的其他三位平時休
息和練功的地方，左邊就是梅莊的廚房。走廊到了這裏似乎就到了盡
頭，再往前便是梅莊的後廳了。
LONG );
        set("exits", ([
            "north" : __DIR__"houting",
            "south" : __DIR__"zoulang2",
            "west"  : __DIR__"chufang",  
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

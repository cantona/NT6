//ROOM: /d/yanziwu/zuijing2.c

inherit ROOM;

void create()
{
        set("short", "綴錦樓二層");
        set("long", @LONG
這是包不同愛女包不靚的臥室，小床，小桌上堆滿了小孩子的玩
藝兒，透過南北兩扇窗戶可以看見太湖上煙波浩渺，白帆點點。
LONG );
        set("exits", ([
             "down"   : __DIR__"zuijing",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
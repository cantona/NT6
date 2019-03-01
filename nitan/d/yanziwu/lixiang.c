//ROOM: /d/yanziwu/lixiang.c

inherit ROOM;

void create()
{
        set("short", "梨香苑");
        set("long", @LONG
慕容家的後院也與眾不同，圓形院門上刻有「梨香苑」三字，院
中雪白的梨花開滿了枝頭。西側就是接待貴賓的龍鳳廳了，東側有一
條精美的長廊。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "north" : __DIR__"chuantang",
            "west"  : __DIR__"longfeng",
            "east"  : __DIR__"changlang"
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
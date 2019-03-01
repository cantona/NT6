// /guanwai/tianchi2.c

inherit ROOM;

void create()
{
        set("short", "白頭山天池");
        set("long", @LONG
天池十天九霧，雲蒸霧繞，變幻無窮。瞬息萬變的霧靄風雨，使天池時
而清亮如藍天明鏡，時而縹緲如輕瑩薄紗，時而騰躍如大海波濤，景色大觀
令人神往。
LONG );
        set("exits", ([
                "north"    : __DIR__"tianchi1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}
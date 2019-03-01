// /d/xiakedao/shihole5.c 俠客島 石洞5

inherit ROOM;

int do_learn(string arg);
void create()
{
        set("short", "石洞");
        set("long", @LONG
進洞便覺腳下有些不同，原來特意墊了半尺厚的黃土，不知有什
麼妙用。正面也是刻着這四句的總綱：「落花殘陽」，卻是筆致圓潤，
似出女子之手。周圍簾幕低垂，一色淡黃。
LONG );
        set("exits", ([
                "out"   : __DIR__"shihole4",
                "enter" : __DIR__"shihole6",
                "north" : __DIR__"shiroom17",
                "south" : __DIR__"shiroom18",
                "east"  : __DIR__"shiroom19",
                "west"  : __DIR__"shiroom20",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
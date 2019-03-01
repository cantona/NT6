// Room: /d/shaolin/woshi.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "臥室");
        set("long", @LONG
臥房裡只有一張竹制的矮床上面舖了半破爛的篾席。席子上的一
角耷拉到地上。席腿邊有一把斷了的單刀。地上斑斑點點似乎是好多
天前留下的血跡。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaowu",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

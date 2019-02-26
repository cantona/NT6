// Room: /d/shaolin/rukou.c
// Date: YZC 96/02/06

inherit ROOM;

void create()
{
        set("short", "五行洞入口");
        set("long", @LONG
這裏是五行洞的入口。四面黑沉沉的，巨石削鑿成的牆壁上鑲嵌
了幾顆鵝蛋大小的珠子，放出濛濛的黃光。就是這樣，也只能照射到
幾丈遠的地方。地上濕漉漉的，腳邊不時會踢到斷裂的枯骨，發出的
脆響聲在甬道內迴響，使你從心底裏冒出一股凌凌的寒意。四周歧路
重重，迷茫難辨。你不知道該往哪裏邁步。
LONG );
        set("exits", ([
                "south" : __DIR__"wuxing"+random(5),
                "north" : __DIR__"andao1",
        ]));
        set("no_clean_up", 0);
        set("objects",([
                "/d/shaolin/npc/ad-laoshu" : 4,
        ]));
        setup();
        replace_program(ROOM);
}

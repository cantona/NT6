inherit ROOM;

void create()
{
        set("short", "舍利塔");
        set("long", @LONG
這是天龍三塔之一，建于唐初，年代久遠。傳說月圓之夜，在此
塔之下默許心願，塔頂會出現聖光指點迷津，助你達成心願。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "west" : __DIR__"talin",
        ]));
        set("objects",([
                "/d/wudang/npc/guest" : 2,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
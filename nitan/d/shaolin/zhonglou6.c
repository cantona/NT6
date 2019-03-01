// Room: /d/shaolin/zhonglou6.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鐘樓六層");
        set("long", @LONG
沿窗洞吹進一陣陣凌厲的山風，寒意浸人。北望可見鬆林的盡頭，
少室山的頂峰處，有一片小小的平地，正中植著三棵巨鬆；又似乎有
什麼東西正閃閃發光。頭頂上的樓板開了個大洞，掛下一口大鐘。從
這裡只能看到巨鐘的下邊緣，內裡黑洞洞的，什麼也看不見。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou7",
                "down" : __DIR__"zhonglou5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

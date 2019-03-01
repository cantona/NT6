// Room: /d/shaolin/gulou6.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鼓樓六層");
        set("long", @LONG
沿窗洞吹進一陣陣凌厲的山風，寒意浸人。北望可見鬆林的盡頭，
少室山的頂峰處，有一片小小的平地，正中植著三棵巨鬆；中間又似
乎有什麼東西正閃閃發光。樓上傳來一陣陣沉悶的鼓聲。
LONG );
        set("exits", ([
                "up" : __DIR__"gulou7",
                "down" : __DIR__"gulou5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

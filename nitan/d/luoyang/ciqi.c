inherit ROOM;

void create()
{
        set("short", "瓷器店");
        set("long", @LONG
在這裡你能夠買到各種你所需要的瓷器，價格昂貴的有，價格低廉的
也有，平時，當地居民到這裡來買一些盆啊碟啊碗啊之類的最方便不過了。
當然象景德鎮的陶瓷藝術品和洛陽的唐三彩這裡也有的賣。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad3",
        ]));
        set("objects", ([
                __DIR__"npc/han" : 1,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
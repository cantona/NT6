inherit ROOM;

void create()
{
        set("short", "黑森林");
        set("long", @LONG
這裡就是有名的黑森林，四周均是茂密的叢林，巨大的古木遮天
蔽日，頭頂看不到一片天空。腳下不時傳來輕微的聲響，似乎有什麼
東西從草叢中遊過，遠處偶爾傳來一陣野獸的嚎叫聲。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "enter" : __DIR__"langwo",
                "south" : __DIR__"milin5",
                "west" : __DIR__"milin3",
                "north" : __DIR__"milin3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
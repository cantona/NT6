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
                "east" : __DIR__"milin4",
                "south" : __DIR__"milin3",
                "west" : __DIR__"milin6",
                "north" : __DIR__"milin4",
        ]));

        setup();
        replace_program(ROOM);
}
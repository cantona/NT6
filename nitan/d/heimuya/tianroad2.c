inherit ROOM;

void create()
{
        set("short", "亂石小徑");
        set("long", @LONG
這是一處亂石怪異的小徑，向西再迂迴轉東北可以通往平安州。
據説前方經常有野獸出沒，不可久留。南方不遠有一座建築，頗為氣
派。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                    "south" : __DIR__"tiangate",
                    "west" : __DIR__"tianroad1",
        ]));
        setup();
        replace_program(ROOM);
}
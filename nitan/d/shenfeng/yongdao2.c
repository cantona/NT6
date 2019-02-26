inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
走過了長長一條甬道，白玉壁上映出人的影子，此時深入
峯腹，吉凶禍福，殊難逆料，生平遭遇之奇，實以此時為最了。
LONG);
        set("exits", ([
                "north" : __DIR__"yongdao3",
        ]));

        setup();
        replace_program(ROOM);
}
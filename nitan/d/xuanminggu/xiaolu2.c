inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是陡坡上的一條雜草叢生的羊腸小路，看起來平時沒什
麼人跡，路邊開着不知名野花，兩邊松樹依然高大挺拔。陽光
透下來照的你身上是斑斑駁駁的影子。
LONG );
        set("exits", ([
                 "southeast" : __DIR__"shanlu1",
                "westup"    : __DIR__"xiaolu3",
        ]));

        set("outdoors", "xuanming");
        setup();
        replace_program(ROOM);
}

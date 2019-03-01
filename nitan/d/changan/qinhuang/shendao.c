// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "神道");
        set("long", @LONG
神道兩側，自東向西依次排列著獅、獬、駱駝、象、麒麟和馬六
種石雕巨獸，各有兩對四座，共十二對二十四座，造型生動，栩栩如
生，使你像來到了傳說的仙界。在淡淡的月照下，眾石獸或蹲或立，
不畏風霜雨雪。
LONG );
    set("exits", ([
       "north" :__DIR__"shidao",
       "west" :__DIR__"mumen",
]));
    setup();
    replace_program(ROOM);
}
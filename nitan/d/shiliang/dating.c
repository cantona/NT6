// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "大廳");
        set("long", @LONG
你來到温家大宅會客的大廳裏，這裏燈火通明，屋內陳設很
是精巧，兩個製作精美的有一人般高的大瓷瓶放在廳的兩側，四
周的牆上掛着許多文人墨客的字畫，大廳上面有塊匾，上書“正
義堂”三個大字。有個中年人正坐在八仙桌旁悠閒地喝着茶，好
象在沉思着什麼。
LONG
        );
        set("exits", ([ 
                "south" : __DIR__"yuanzi",
                "northwest" : __DIR__"zoulang1",
                "northeast" : __DIR__"zoulang5",
        ]));
        set("objects", ([
                __DIR__"npc/wenfangda" : 1,
                __DIR__"npc/yahuan" : 2,
        ]));
        set("coor/x", 1610);
        set("coor/y", -1950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
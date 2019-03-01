// Room: /yangzhou/changtichunliu.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short", "春柳亭");
        set("long", @LONG
長堤中段臨湖築一個半岸半水、置美人靠的木構件方亭。亭內懸“
長堤春柳”匾，仍為清光緒道員陳重慶手筆。外懸“中流自在”匾，兩
柱懸掛王板哉手書楹聯(lian)，乃集趙孟兆頁、元好問句而成。
LONG );
        set("outdoors", "shouxihu");
        set("no_clean_up", 0);
        set("item_desc", ([
                "lian" : "
        佳        宿
        氣        雲
        溢        澹
        芳        野
        甸        川\n",
        ]));

        set("exits", ([
                "south" : __DIR__"changdi1",
                "north" : __DIR__"changdi2",
        ]));
        set("coor/x", 0);
        set("coor/y", 32);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
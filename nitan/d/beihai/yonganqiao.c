// /d/beihai/yonganqiao.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "永安石橋");
        set("long", @LONG
永安橋在永安寺南，又名“堆雲積翠橋”。三孔券洞，曲尺形，橋
面舖條石，坡度平緩。橋身兩側有雕刻精美的欄板和望柱。橋南北分別
置立四柱三樓式木牌坊一座，綠筒瓦頂，朱紅色圓柱，色彩鮮艷奪目。
LONG
        );
        set("exits", ([
                "north" : __DIR__"yongansi",
                "south" : __DIR__"zhaojing",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
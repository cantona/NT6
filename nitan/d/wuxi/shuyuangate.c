// Room: /d/wuxi/shuyuangate.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "書院門樓");
        set("long", @LONG
東林書院環境幽雅，兩面臨河，小橋流水，垂柳依依，書聲琅琅。
一座高大的石牌坊(fang)矗立在前，兩棵古柏直沖雲霄。再向裡走就是
書院的學堂，學堂門口掛著一幅對聯(lian)。兩側是碧碧池水，看了後
頓覺賞心悅目。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"shuyuan",
                "south" : __DIR__"eastroad2",
        ]));
        set("item_desc", ([
                "lian" : "
  風聲雨聲讀書聲 聲聲入耳
  家事國事天下事 事事關心\n",
                "fang" : "
 前刻後學津樑後鐫後學津樑\n",
        ]));
        set("coor/x", 1060);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
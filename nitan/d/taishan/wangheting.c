// Room: /d/taishan/wangheting.c
// Last Modified by Winder on Aug. 25 2001

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "望河亭");
        set("long", @LONG
玉皇廟西廂就是望河亭。黃河金帶為泰山六大奇觀之一。若新霽無
塵、夕陽西下時，舉目北眺，在泰山西北層層峯巒的盡頭，可看到黃河
象一條金色的帶子閃閃發光，或河水反射到天空，形成蜃景，波光粼粼，
黃白相間，如同金銀鋪就一般，從西南至東北，一直伸向天地交界處。
恰如袁枚在《登泰山詩》中所描繪的：“一條黃水似衣帶，穿破世間通
銀河。” 
LONG );
        set("exits", ([
                "east" : __DIR__"yuhuang",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 20);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}
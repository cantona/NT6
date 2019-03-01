// Room: /d/taishan/bixia.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "碧霞祠");
        set("long", @LONG
這是一座歷史悠久而宏偉壯麗的祠院。相傳它建于唐代以前，宋、
元、明、清各代均曾增建。祠院設有東西兩殿，分別稱為東西寶庫，儲
存著進香客的捐施，兩殿的屋瓦都是由鐵鑄成。從四方八面來泰山上香
的男女，都是先到碧霞祠，然後才到其他的廟宇。從這裡往東南走便可
到達寶藏嶺。
LONG );
        set("exits", ([
                "west"      : __DIR__"yunuchi",
                "westup"    : __DIR__"weiping",
                "southeast" : __DIR__"baozang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 60);
	set("coor/y", 300);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}
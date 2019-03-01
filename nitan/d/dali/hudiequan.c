//Room: /d/dali/hudiequan.c
//Date: June. 29 1998 by Java

inherit BUILD_ROOM;
void create()
{
        set("short","蝴蝶泉");
        set("long", @LONG
蝴蝶泉就顯得更加清涼濕潤，大量的蝴蝶，從四面八方，匯集在
樹蔭下，花叢中，翩翩起舞，成千上萬只彩蝶，歡聚一處，使這裡變
得花團錦簇。特別是在蝴蝶泉上，順著那倒垂的揚柳，無數蝴蝶，一
只咬著一只的尾部，形成千百個蝶串，人來不驚，投石不散，構成令
人驚嘆的奇觀。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/yuxuguanqian",
            "east"   : "/d/dali/xiaodao1",
        ]));
        set("max_room",4);
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
}
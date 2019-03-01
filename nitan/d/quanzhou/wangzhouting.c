// Room: /d/quanzhou/wangzhouting.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "望州亭");
        set("long", @LONG
這裡的地勢豁然開朗，有三塊巨石如三條大蟒伸頭出洞，故稱「蟒
石」。蟒首向前探望，似乎也在鑒賞下界的美景。石上一亭突兀，如飛
來神筆，又稱「飛來亭」。憑欄遠望，泉州全景，盡收眼底。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"shanlu4",
                "northdown" : __DIR__"ruixiangyan",
        ]));
	set("coor/x", -900);
	set("coor/y", -7580);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
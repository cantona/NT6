// Room: /wuliang/shanlu9.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
青石山路還砌得蠻整齊的。因為山上就是無量劍派的地頭了。無
量劍派在無量山中自己做大已久，所以少有資財，把這路也修得有模
有樣。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"   : __DIR__"jianhugate",
                "northdown" : __DIR__"shanlu8",
        ]));
        set("coor/x", -71000);
        set("coor/y", -79970);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
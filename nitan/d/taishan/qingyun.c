// Room: /d/taishan/qingyun.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "青雲洞");
        set("long", @LONG
這裡是青雲洞。傳陰雨天洞內生青煙，與白雲洞之雲相遇即雨遍天
下。俗稱《春秋公羊傳》所載“觸石而出，膚寸而合，不崇朝而遍雨乎
天下者，唯泰山爾”，即指此地。 
LONG );
        set("exits", ([
                "westup" : __DIR__"xiangshan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 50);
	set("coor/y", 290);
	set("coor/z", 200);
	setup();
        replace_program(ROOM);
}
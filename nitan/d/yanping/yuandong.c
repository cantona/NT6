// Room: /d/yanping/yuandong.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "白猿洞");
        set("long", @LONG
白猿洞位于九峰深處，洞深百丈，入洞不辨五指。周圍古樹繁密，
遮天閉日，唯洞口凸出山崖處，老遠就能看見。相傳此洞附近曾有白猿
出沒，風吹林響，便是與山下劍潭“龍津春浪”齊名的八景之一的“猿
洞秋風”了。
LONG );
        set("exits", ([
                "northwest" : __DIR__"shuyuan",
                "northeast" : __DIR__"xita",
        ]));
        set("objects", ([
                __DIR__"npc/yuan" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
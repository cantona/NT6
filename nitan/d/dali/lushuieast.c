//Room: /d/dali/lushuieast.c
//Date: June. 29 1998 by Java

inherit BUILD_ROOM;
void create()
{
        set("short","東瀘水河谷");
        set("long",@LONG
西面這一大片河谷處在碧羅雪山和高黎山之間，由東瀘水沖刷而
成，地勢低窪，因而氣候較溫暖，聚居了大量烏夷族人。烏夷先民沿
河谷開發了一些梯田。四周山高林密，男子多從事狩獵。沿著腳下的
向西直抵一個大鎮子。
LONG);
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "westdown"   : __DIR__"badidian",
            "eastup"     : __DIR__"biluoxueshan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19200);
	set("coor/y", -6870);
	set("coor/z", 30);
	setup();
}

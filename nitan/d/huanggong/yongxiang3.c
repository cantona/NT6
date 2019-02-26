// Room: /d/huanggong/yongxiang3.c

inherit ROOM;

void create()
{
        set("short", "永巷");
        set("long", @LONG
這裏是三大殿周圍的通道。宮禁森嚴，天威莫測，來來往往的宮女
太監雖然很多，可是誰也不敢帶出一點聲來。
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 3 */
                "north" : __DIR__"yongxiang4",
                "west"  : __DIR__"taihedian",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2800);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
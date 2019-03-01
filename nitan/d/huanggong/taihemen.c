// Room: /d/huanggong/taihemen.c

inherit ROOM;

void create()
{
        set("short", "太和門");
        set("long", @LONG
這是三大殿的前門. 門前立著一對銅鑄獅子, 東邊是只雄獅前足踏
繡球, 象征權力和統一寰宇. 西邊是只雌獅, 前肢撫弄一小乳獅, 象征
子嗣昌盛.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 4 */
                "south" : __DIR__"wumen",
                "north" : __DIR__"guangchang",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2800);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
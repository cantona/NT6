// Room: /d/huanggong/yihexuan.c

inherit ROOM;

void create()
{
        set("short", "頤和軒");
        set("long", @LONG
這兒是乾隆帝閲覽書籍和遊玩的地方, 也是一座珍寶館, 其中多是
從全國各地搜刮來的珠寶珍奇.
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "west"  : __DIR__"yuhuayuan2",
                "south" : __DIR__"leshou",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2810);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
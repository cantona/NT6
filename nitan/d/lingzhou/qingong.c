// Room: /d/lingzhou/qingong.c

inherit ROOM;

void create()
{
        set("short", "寢宮");
        set("long", @LONG
這裏就是西夏皇帝的寢宮，一色的白玉地板，白色的紗帳，居中是
皇帝的龍榻，榻邊是一張白老虎皮做的踏腳, 牆上掛着把新月彎刀，據
説是土蕃的貢品。東西兩邊侍衞們值夜守更的偏殿。北面牆上有幅老鷹
撲翅的巨畫。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"piandian2",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6295);
        set("coor/y", 2985);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
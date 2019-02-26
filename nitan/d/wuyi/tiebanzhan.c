// Room: /d/wuyi/tiebanzhang.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "鐵板嶂");
        set("long", @LONG
鐵板嶂因石崖峻峭、色如鐵板而得名。所有三十六峯，惟獨此峯因
身處大王峯和玉女峯之間，由大王和玉女傳説而身背罵名。人們都把它
看做是破壞大王玉女婚姻的罪人。此峯崖峭層疊、曲水倒映、溝壑縱橫、
石徑曲折、修竹繁茂、意境幽雅。其下有儒巾石和“千崖萬壑”題刻。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"2qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}

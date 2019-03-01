// Room: liupeng.c

inherit ROOM;

void create()
{
        set("short", "牛棚");
        set("long", @LONG
這是一個小小的茅屋，茅屋前是一片黃澄澄的耕地，一個
牧童正站在茅屋前傻傻的發愣，一面愁容，還喃喃道：“完了，
，完了.....!”
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "southwest" : __DIR__"maowu",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

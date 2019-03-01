// Room: /d/village/shack.c

inherit ROOM;

void create()
{
        set("short", "草棚");
        set("long", @LONG
這是一個簡單的草棚，地上擺著一堆堆的貨物，上山的遊客可以
在這買些上山用品。草棚的牆上貼着個牌子，是個價目表(sign)。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "north" : __DIR__"eroad1",
        ]));
        set("objects", ([
                __DIR__"npc/seller": 1 ]) );
        set("item_desc", ([ /* sizeof() == 1 */
        "sign" : "牌子上寫道：
        手杖(stick)        一百文
        麻鞋(shoes)        一百五十文
        水壺(bottle)        一百文

                兼售 皮蛋(egg) 五十文，茶水(not yet) xx。 \n"
        ]));

        setup();
        replace_program(ROOM);
}
 
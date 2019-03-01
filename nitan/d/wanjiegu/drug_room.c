// Room: /t/wanjiegu/drug_room.c

inherit ROOM;

void create()
{
        set("short", "藥房");
        set("long", @LONG
剛進這間屋子，就有一股濃重的藥味撲面而來。房子中間有一個
練藥用的石臼，還有幾只藥匙放在一邊。靠牆一排架子，架子上擺滿
了藥瓶，數百個瓶子上都寫著藥物的名字。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"right_room",
        ]));
        set("item_desc", ([ /* sizeof() == 1 */
            "架子" : "架子上擺滿了藥瓶。\n",
        ]));
        set("objects", ([
            __DIR__"obj/mortar" : 1,
        ]));
//        set("no_clean_up", 0);

        setup();
}

void reset()
{
        object          *inv;
        object          container, item;
        int             i;

        ::reset();
        container = present("mortar", this_object());
        inv = all_inventory(container);
        if( sizeof(inv) != 1) {
                for(i=sizeof(inv)-1; i>=0; i--) destruct(inv[i]);
                item = new(__DIR__"obj/x-drug");
                if(random(2)==1 )
                    item->move(container);
        }
}

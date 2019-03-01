// huixinshi.c

inherit ROOM;

void create()
{
        set("short", "回心石");
        set("long", @LONG
從青柯坪沿石階上山，山路到此而盡，前面山勢險惡，石崖間僅
有窄窄的石階猶如天梯聳立，兩邊鐵鏈斜懸，令人不寒而栗，不敢前
行。北壁下大石當路，此石因此叫做回心石，再上去山道奇險，遊客
至此，就該回頭了。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "westdown" : __DIR__"qingke",
                "eastup"   : __DIR__"qianchi",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan" );
        /*
        set("search_objects", ([
                "/clone/book/mingyu-book" : 1000,
        ]));
        set("no_search", 1000000);
        */

        setup();
        replace_program(ROOM);
}
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "山門");
        set("long", @LONG
這裡就是江湖上聞風喪膽的“鐵掌幫”。自從“鐵掌殲衡山”一役將衡
山派打得一蹶不振之後，幫主鐵掌水上漂的名頭威震江湖。這裡是進山的必
經之路，曲的小路通向山裡。路的一側立著一塊牌子(paizi) 。兩旁的樹林
內不時傳出一些響聲，似乎有人在暗中監視。
LONG        );
    set("outdoors", "tiezhang");
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"shanlu-1",
  "southdown" : __DIR__"shanjiao",
]));
    set("objects", ([ /* sizeof() == 2 */
    __DIR__"npc/heiyi" : 2,
                CLASS_D("tiezhang") + "/first" : 1,
]));
        set("item_desc", ([ /* sizeof() == 1 */
  "paizi" : "[31m“擅入者--死” 
[0;37;0m",
]));
        set("no_clean_up", 0);

        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if( (!myfam || myfam["family_name"] != "鐵掌幫") && dir == "northup" && query("combat_exp", me) >= 10000 && 
                objectp(present("heiyi bangzhong", environment(me))))
        return notify_fail(CYN "黑衣幫眾抽刀攔住你的去路，說道：“你不是鐵掌幫弟子，不能上山！\n" NOR);

        return ::valid_leave(me, dir);
}

// Room: /d/huijiang/xiepo.c
// Last Modified by winder on Sep. 12 2001
inherit ROOM;

void create()
{
        set ("short", "斜坡");
        set ("long", @LONG
兩邊的樹林稀稀落落的，在西北邊塞的寒風吹動中發出沙沙的響聲。
北面的草原上牛羊在吃草，放羊的姑娘輕輕的揮着鞭子，南面的樹林中
有幾個帳篷，透出一股殺氣。
LONG);
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "northdown" : __DIR__"caoyuan",
                "southup"   : __DIR__"buluo2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50050);
        set("coor/y", 9070);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
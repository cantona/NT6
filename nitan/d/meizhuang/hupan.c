// hupan.c
inherit ROOM;

void create()
{
        set("short", "南湖湖畔");
        set("long", @LONG
順着南湖一直走過去，你欣賞着湖邊的楊柳，不知不覺地已經走
到南湖的盡頭，這裏有一條蜿蜒的小路向前延伸着，隱隱約約可以看
到一座莊園，你不禁想走過去看看那裏是什麼地方．
LONG );
        set("exits", ([ /* sizeof() == 2 */
  "west" : "/d/quanzhou/nanhu1",
  "north" : __DIR__"xiaolu.c",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}

// yunu.c

inherit ROOM;

void create()
{
        set("short", "玉女峯");
        set("long", @LONG
這裏是華山的中峯，玉女峯。傳説春秋時隱士蕭史善吹洞簫，簫
聲引動了秦穆公女兒弄玉的愛慕，拋棄了宮廷生活，跟蕭史來此隱居，
故稱玉女峯。這裏地勢略為平緩，不似其它四峯般險峻，江湖上赫赫
有名的華山劍派就在此處。東邊有所小小的廟宇，那就是玉女祠了。
北面稀稀落落有十幾間房子，是華山派的地方，閒雜遊客最好別往那
裏去。
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "westdown"  : __DIR__"zhenyue",
            "west"      : __DIR__"yunuci",
            "north"     : __DIR__"square",
            "southdown" : __DIR__"yunupath1",
            "northeast" : __DIR__"xiaolu1",
        ]));
        set("objects", ([
            __DIR__"npc/yue-lingshan" : 1,
        ]));

        // set("no_clean_up", 0);
        set("outdoors", "huashan" );

        setup();
        replace_program(ROOM);
}
 
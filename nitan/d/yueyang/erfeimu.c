// Room: /d/yueyang/erfeimu.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "二妃墓");
        set("long", @LONG
二妃墓在君山島的東麓，與岳陽古城隔湖相望。墓兩邊的石刻對聯
是：“君妃二魄芳千古，山竹諸斑淚一人。”這“淚一人”典出：虞舜
南巡，崩于蒼梧，他的兩個愛妃娥皇和女尋夫來到洞府山，忽聞噩耗，
悲痛萬分，遂攀竹痛哭，淚血滴在竹子上，竟成斑竹。二妃因悲慟而死
于君山並葬此。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"banzhu2",
                "west"      : __DIR__"banzhu3",
                "south"     : __DIR__"banzhu1",
                "northup"   : __DIR__"shanliang",
                "southwest" : __DIR__"shijie2",
                "northeast" : __DIR__"xiaolu6",
        ]));
        set("coor/x", -1670);
        set("coor/y", 2300);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}
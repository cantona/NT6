// Room: /d/mingjiao/shanlu3.c
// Date: Java 97/04/9

inherit ROOM;

void create()
{
        set("short", "懸天崖");
        set("long", @LONG
這裏山路陡峭，僅有一人多寬，路左是峭壁高聳，路右緊臨萬丈
深淵，實在是一夫當關、萬夫莫開的險要之處。繼續上攀，就要到達
明教五行旗了。緊挨路右，天然生有一塊巨石，高近三丈，名為『懸
天石』，常有俠客於上遠觀雲海。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shanlu2",
                "northup"   : __DIR__"shanlu4",
                "up"        : __DIR__"xuantianshi",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if ((random((int)me->query_skill("dodge")) <= 20) && dir=="up")
        {
                return notify_fail("你使勁兒一蹦，離石頂還有數丈遠就掉了下來，摔的鼻青臉腫。\n");
        }
        if ((random((int)me->query_skill("dodge")) <= 35) && dir=="up")
        {
                return notify_fail("你奮力一躍，卻離石頂還有一丈多遠，看來是白費力氣。\n");
        }
        if ((random((int)me->query_skill("dodge")) <= 60) && dir=="up")
        {
                return notify_fail("你縱身而起，離石頂只差一點點了，再加把勁。\n");
        }

        return ::valid_leave(me, dir);
}

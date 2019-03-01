inherit ROOM;

void create()
{
        set("short", "仙愁門");
        set("long", @LONG
這裡就快到縹緲峰絕頂了，越往上走，山勢越高，繚繞在你身邊
的白霧癒來癒濃，往南則是下山的路。沿著山道沒走幾步，在你眼前
出現一個石坊，上書「仙愁門」三個大字，蓋因上山之艱辛吧。
LONG );
        set("outdoors", "lingjiu");
        set("objects", ([
                CLASS_D("lingjiu") + "/first" : 1,
        ]));
        set("exits",([
                "eastup" : __DIR__"dadao1",
                "southdown" : __DIR__"jian",
        ]));
        setup();
        replace_program(ROOM);
}

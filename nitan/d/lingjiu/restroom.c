inherit ROOM;

void create()
{
        set("short", "憩鳳閣");
        set("long", @LONG
這裡是靈鷲宮弟子睡覺的地方，一進門就聞到一陣悠悠的香氣，
只見房中點了一支大紅燭，照的滿室生春，床上珠羅紗的帳子，白色
緞被上繡著一只黃色的鳳凰，壁上掛著一幅工筆仕女圖。西首一張幾
上供著一盆蘭花，架上停著只白鸚鵡。
LONG );
        set("exits",([
                "west" : __DIR__"changl3",
        ]));
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
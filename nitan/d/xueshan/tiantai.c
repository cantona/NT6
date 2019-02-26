inherit ROOM;

void create()
{
        set("short", "天台");
        set("long", @LONG
 這裏是雪山寺的高處。北邊可見雄偉的大雪山，南邊可以俯瞰美
麗如鏡的聖湖。
LONG );
        set("exits", ([
                "west" : __DIR__"chanshi",
        ]));

        set("objects", ([
                CLASS_D("xueshan") + "/huodu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
// yuquan.c

inherit ROOM;

void create()
{
        set("short", "玉泉院");
        set("long", @LONG
這裏因屋後的玉泉而得名，是宋代陳希夷隱居的地方。周圍生着
十二株大龍藤，夭矯多姿，枝幹中空，就如飛龍相似，相傳是希夷先
生陳摶老祖所植。院內綠廕庇日，泉石如畫，流水縈迴，迴廊曲折。
院中有清泉一股，泉水甘冽，傳與山頂鎮嶽宮玉井相通，故名玉泉，
玉泉院因此得名。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"path1",
        ]));
        // set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/teller": 1
        ]));

        setup();
        replace_program(ROOM);
}
 
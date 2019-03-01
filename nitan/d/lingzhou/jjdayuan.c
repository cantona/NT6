// Room: /d/lingzhou/jjdayuan.c

inherit ROOM;

void create()
{
        set("short", "將軍府大院");
        set("long", @LONG
這裡是將軍府的大院，當面一堵寬闊的白玉照壁，上書“忠心報國”
四個大字，落款是當今西夏皇帝李元昊。一色的青磚舖地，有幾個僕役正
在院中洒掃，南面是內宅，西面是帳房，東面是個小院。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                "/d/city/npc/jiading" : 2,
        ]));
        set("cost", 2);
        set("outdoors", "xixia");
        set("exits", ([ /* sizeof() == 4 */
                "east"  : __DIR__"zhaiyuan",
                "north" : __DIR__"jiangjungate",
                "enter" : __DIR__"xiaolou",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2905);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
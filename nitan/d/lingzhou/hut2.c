// Room: /d/lingzhou/hut2.c

inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
這是一間不大的竹屋，頂上還有好幾個大大小小的破洞，藉着透下
的些許光亮。你發現裏面空空蕩蕩，徒有四壁，屋頂和角落裏掛着些積
滿塵土的蜘蛛網。地板也是紫竹製成，同樣積滿了灰塵。西北角顯得特
別暗。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "out" : __DIR__"hut",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6295);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
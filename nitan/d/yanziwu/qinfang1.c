//ROOM: /d/yanziwu/qinfang1.c

inherit ROOM;

void create()
{
        set("short", "沁芳閣");
        set("long", @LONG
這裡是供慕容世家的僕人小憩的地方，三面臨水。微風拂過，送
來縷縷的荷花葉香，沁人心脾，沁芳閣因此而名。一架墨綠色的竹梯
通向樓上的休息室。
LONG );
        set("exits", ([
            "east"  : __DIR__"yimen",
            "up"    : __DIR__"qinfang2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
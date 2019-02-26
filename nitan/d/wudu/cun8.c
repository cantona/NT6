inherit ROOM;

void create()
{
        set("short", "村東口");
        set("long", @LONG
這裏是小村的東頭。因為暴雨剛過，地上一片泥濘，路非常不好
走。順着這條路一直向東走一兩個時辰就可到青石坪了，那裏是這附
近最大的鎮子。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "northwest" : __DIR__"cun7",
                "east" : "/d/dali/zhulin2",
        ]));

        setup();
        replace_program(ROOM);
}
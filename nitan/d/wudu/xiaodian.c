inherit ROOM;

void create()
{
        set("short", "路邊小店");
        set("long", @LONG
這裏是一家山野小店，僅僅供應一些食物和時鮮山貨。這裏行人
稀少，大概一天也沒幾個人路過這裏，老闆娘把店開在這裏恐怕是要
賠了。店內進是一間客房，行人累了可以進去休息。
LONG);

        set("exits", ([
                "east" : __DIR__"shanlu1",
                "west" : __DIR__"neijin",
        ]));

        set("objects", ([
                __DIR__"npc/sun": 1,
        ]));

        setup();
        replace_program(ROOM);
}

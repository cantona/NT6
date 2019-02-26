inherit ROOM;

void create()
{
        set("short", "客房");
        set("long", @LONG
這裏是一間客房，靠牆布着一溜通鋪，行人累可以在這裏隨意休
息。窗邊擺着一個破破爛爛的木桌，一個遊方道人正坐在這裏的桌邊
上喝茶。
LONG);

        set("exits", ([
                "east" : __DIR__"xiaodian",
        ]));
        set("objects", ([
               CLASS_D("wudu") + "/daoshi" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
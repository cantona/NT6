inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路越走越窄，能隱隱望見前方又分出了幾條叉路。這裏是靠近
川西的崇山峻嶺，怪石嶙峋。再往東就是川西邊緣。往西有一座雪山
高聳入雲。
LONG );
        set("exits", ([
                "south" : __DIR__"sroad3",
                "north" : __DIR__"nroad0",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}

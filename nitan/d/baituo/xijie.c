inherit ROOM;

void create()
{
        set("short", "西街");
        set("long", @LONG
這裏是小鎮的西街。北邊有個酒店，門前樹立着高高的旗杆，一
塊青布幌子迎風飄揚，上面印着硃紅色的酒字。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "west"  : __DIR__"bridge",
                "east"  : __DIR__"dongjie",
                "south" : __DIR__"jiudian",
        ]));
        set("objects", ([
                __DIR__"npc/man" : 1,
                __DIR__"npc/snaker"  :1,
        ]));
        set("coor/x", -49970);
        set("coor/y", 19980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
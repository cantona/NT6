inherit ROOM;

void create()
{
        set("short", "林中小路");
        set("long", @LONG
你走在一條僻靜的林中小路上，兩旁是陰森森的樹林。只見左右
前後，到處都是鋪天蓋地的松樹林。幾十丈高的大松樹簇在一塊，密
實的枝葉象一蓬蓬巨傘恆伸向天空，把陽光遮得絲毫也無。據説這裏
經常有土匪出沒，不可久留。
LONG );
        set("outdoors", "sanbuguan");
        set("no_sleep_room", 1);
        set("exits", ([
                "west" : __DIR__"tufeiwo2",
        ]));
        set("objects", ([
                __DIR__"npc/tufei1" : 2 ,
                __DIR__"npc/tufeitou" : 1, 
        ]));
        set("coor/x", -310);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}

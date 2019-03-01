// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
        set("short", "二台");
        set("long", @LONG
四季的景色，都在這一山之中。山頂上，白雪皚皚，尚在嚴冬；
山腰裡，蒼鬆翠柏，秋色濃重；山坡上，山花爛漫，如值仲夏；而從
那雪峰直垂下來的溪澗裡，冰雪消融，春意盎然。二台以北，有一石
洞，人稱仙人洞。
LONG );
        set("exits", ([
                "west" : "/d/xingxiu/guozi",
                "eastdown" : "/d/xingxiu/wuchang3",
                "north" : "/d/xingxiu/xrdong",
        ]));
        set("cost", 2);
     set("fjing", 1);
        set("outdoors", "tianshan");
        set("objects", ([
                "/d/xingxiu/obj/xuesang" : 1,
        ]) );

        setup();
        replace_program(ROOM);
}
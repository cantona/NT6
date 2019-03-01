inherit ROOM;

void create()
{
          set ("short", "城樓二層");
          set ("long", @LONG
一登上城樓，城外西面的一大片的開闊地盡收眼底，要是
在這裡布上弩兵，要是有誰想攻進城來簡直比登天還難。
LONG);

        set("outdoors", "zhongzhou");

          set("exits", ([  
                    "down" : __DIR__"chenglou",
 
        ]));

        set("coor/x", -9080);
	set("coor/y", -1000);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
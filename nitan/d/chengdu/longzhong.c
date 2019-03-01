//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "古隆中");
        set ("long", @LONG
這是一個小村莊，但見四周群山環抱，鬆柏參天，溪流縈繞，景色
秀麗。相傳諸葛亮幼年失去雙親，十七歲上隨叔父諸葛玄來到這裡隱居，
躬耕苦讀。
LONG);
        set("outdoors", "jiangling");
        set("exits", ([
                "west" : __DIR__"shennongjia",
        ]));
  
        set("coor/x", -15060);
	set("coor/y", -1810);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}
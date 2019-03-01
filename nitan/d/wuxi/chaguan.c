// Room: /d/wuxi/chaguan.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "二泉茶室");
        set("long", @LONG
一進來，正中是一幅丹青中堂，上繪一長袖飄飄之中年人，正乃茶
聖陸羽之像。以示這裡所賣茶葉之正宗。滿室飄著一股沁入心脾的茶香。
室內坐滿了客人，或高聲談笑，或交頭接耳。你要想打聽江湖掌故和謠
言，這裡是個好所在。從側面的窗戶(window)可以俯視屋後的河水。
LONG );
        set("resource/water", 1);
        set("item_desc", ([
                "window" : 
"從窗戶看去，清清的河水歡快地流淌，對面幾個
女子正在河邊浣洗衣服，不時傳來陣陣嘻笑之聲。\n",
        ]));
        set("exits", ([
                "north" : __DIR__"westroad2",
        ]));
        set("objects", ([
                __DIR__"npc/chaboshi" : 1,
        ]));
        set("coor/x", 1020);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
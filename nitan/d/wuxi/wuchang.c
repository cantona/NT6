// Room: /d/wuxi/wuguan.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
走進來是一個很大的練武場，四下裏鋪着細沙、黃土、煤渣的混合
土，踩在上面顯得十分地踏實。幾個新進來的弟子正在秦教頭的指點下
一招一式地練習。兩邊的兵器架上放着各種木製的兵器。向裏去就是秦
教頭的卧室了。雖然秦教頭為人比較隨和，但是你要是非得進去亂看的
話也是很不禮貌的。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "west" : __DIR__"wuguan",
                "east" : __DIR__"wuguanwoshi",
        ]));
        set("objects", ([
                __DIR__"npc/qin" : 1,
        ]));
        set("coor/x", 1060);
	set("coor/y", -700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
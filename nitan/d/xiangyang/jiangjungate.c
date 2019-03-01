// Room: /d/xiangyang/jiangjungate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "將軍府大門");
        set("long", @LONG
這是將軍府的大門，門板不知是以什麼材料制成，看上去黝黑一
片，似乎極為沉重，上面有兩個擦得晶亮的銅環；在大門的正上面有
個夾著一個高大的木牌坊，上書「將軍府」三個大字，字跡娟秀飄逸，
只是有些模糊了，想必是歲月留下的痕跡。門內有一株老柏，生得蒼
勁挺拔，枝葉茂密。門前東西兩邊各肅立著兩個腰配大刀的宋兵。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "south" : __DIR__"eastjie1",
                "north" : __DIR__"jiangjunyuan",
        ]));
        set("objects", ([
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7810);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" &&
                objectp(present("song bing", environment(me))))
           return notify_fail("宋兵向你喝道：什麼人膽敢擅闖守備府衙門！\n");

        return ::valid_leave(me, dir);
}
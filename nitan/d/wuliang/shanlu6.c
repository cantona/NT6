// Room: /wuliang/shanlu6.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山坳");
        set("long", @LONG
轉過山坳，只見一大堆亂石之中團團坐着二十餘人。你小心翼翼地
走近前去，見人叢中一個瘦小的老者坐在一塊高巖之上，高出旁人，頦
下一把山羊鬍子，神態甚是倨傲，料來便是神農幫主司空玄了。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "eastup"  : __DIR__"shanlu5",
                "northup" : __DIR__"shanlu7",
        ]));
        set("objects", ([
                __DIR__"npc/shennongdizi" : 3,
                __DIR__"npc/hong" : 1,
                __DIR__"npc/sheng" : 1,
                __DIR__"npc/sikongxuan" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -71000);
        set("coor/y", -79980);
        set("coor/z", 50);
        setup();
}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if (objectp(present("sikong xuan", environment(me))))
                return notify_fail("司空玄攔住你説：既來此處，必與無量派有關，奉童姥之命，殺無\n赦，你還想走？\n");
        return ::valid_leave(me, dir);
}